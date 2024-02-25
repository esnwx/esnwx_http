#ifndef H_ESNWX_HTTP_PATH_PARSER
#define H_ESNWX_HTTP_PATH_PARSER

#include <initializer_list>
#include <variant>
#include <vector>
#include <optional>
#include <expected>
#include "../string_literal.hpp"
#include "ast/path-expr.hpp"
#include "ast/path-key-value-pair-expr.hpp"
#include "ast/path-segment-expr.hpp"
#include "ast/path-segment-name-expr.hpp"
#include "ast/path-variable-expr.hpp"
#include "path-lexer.hpp"
#include "path-token.hpp"

namespace esnwx::http::detail{
	struct parse_error{
		std::string_view message;
		std::size_t location;
	};

	template<esnwx::http::string_literal TPath>
	class path_parser{
	public:
		constexpr path_parser() : m_tokens(path_lexer<TPath>::scan_all().value()){}

		static constexpr std::expected<path_expr, parse_error> parse(){
			path_parser<TPath> parser{};
			
			if(auto path = parser.parse_path(); path.has_value()){
				if(parser.match_any({path_token_type::eof}))
					return path.value();
				else
					return std::unexpected{parse_error{"expected eof", parser.m_current_token}};
			}
			else{
				return std::unexpected{path.error()};
			}
		}

		static constexpr std::expected<std::size_t, parse_error> param_count(){
			if(auto types = param_types(); !types.has_value()){
				return std::unexpected{types.error()};
			} else{
				return types.value().size();
			}
		}

		template<std::size_t N>
		static constexpr std::expected<variable_type, parse_error> param_type_n(){
			if(auto types = param_types(); !types.has_value()){
				return std::unexpected{types.error()};
			} else{
				return types.value()[N];
			}
		}

		static constexpr std::expected<std::vector<variable_type>, parse_error> param_types(){
			if(auto path = path_parser<TPath>::parse(); !path.has_value()){
				return std::unexpected{path.error()};
			} else{
				std::vector<variable_type> vars{};
				for(const auto& segment : path.value().segments){
					for(const auto& segmentPart : segment.segment_parts){
						if(std::holds_alternative<path_variable_expr>(segmentPart))
							vars.push_back(std::get<path_variable_expr>(segmentPart).type);
					}
				}

				if(path.value().query.has_value()){
					for(const auto& kvp : path.value().query.value().key_value_pairs){
						for(const auto& k : kvp.key_segment_parts.segment_parts){
							if(std::holds_alternative<path_variable_expr>(k))
								vars.push_back(std::get<path_variable_expr>(k).type);
						}
						for(const auto& v : kvp.value_segment_parts.segment_parts){
							if(std::holds_alternative<path_variable_expr>(v))
								vars.push_back(std::get<path_variable_expr>(v).type);
						}
					}
				}

				return vars;
			}
		}

		constexpr std::expected<path_expr, parse_error> parse_path(){
			std::vector<path_segment_expr> segments{};

			do{
				if(!match_any({path_token_type::slash}))
					return std::unexpected{parse_error{"expected '/'", m_current_token}};

				if(auto segment = parse_segment(); segment.has_value())
					segments.push_back(segment.value());
			}while(peek().type == path_token_type::slash);

			std::optional<path_query_expr> q = std::nullopt;

			if(peek().type == path_token_type::question_mark){
				if(auto query = parse_query(); query.has_value())
					q = query.value();
				else
					return std::unexpected{query.error()};
			}

			return path_expr{segments, q};
		}
		constexpr std::expected<path_query_expr, parse_error> parse_query(){
			if(!match_any({path_token_type::question_mark}))
				return std::unexpected{parse_error{"expected '?'", m_current_token}};

			std::vector<path_key_value_pair_expr> kvps{};
			do{
				if(auto kvp = parse_key_value_pair(); kvp.has_value())
					kvps.push_back(kvp.value());
				else
					return std::unexpected{kvp.error()};
			}while(match_any({path_token_type::ampersand}));

			return path_query_expr{kvps};
		}
		constexpr std::expected<path_key_value_pair_expr, parse_error> parse_key_value_pair(){
			std::size_t tokenBefore = m_current_token;

			auto key = parse_segment();
			if(!key.has_value()){
				m_current_token = tokenBefore;
				return std::unexpected{key.error()};
			}

			if(auto eq = match_all({ path_token_type::equals }); !eq.has_value()){
				m_current_token = tokenBefore;
				return std::unexpected{parse_error{ "expected '='", m_current_token }};
			}

			auto value = parse_segment();
			if(!value.has_value()){
				m_current_token = tokenBefore;
				return std::unexpected{value.error()};
			}

			return path_key_value_pair_expr{ key.value(), value.value() };
		}
		constexpr std::expected<path_segment_expr, parse_error> parse_segment(){
			if(auto segmentPart = parse_segment_part(); segmentPart.has_value()){
				std::vector<path_segment_expr::segment_part> parts{};
				do{
					parts.push_back(segmentPart.value());
					segmentPart = parse_segment_part();
				} while(segmentPart.has_value());

				return path_segment_expr{parts};
			}

			return std::unexpected{parse_error{"expected segment part", m_current_token}};
		}
		constexpr std::expected<path_segment_expr::segment_part, parse_error> parse_segment_part(){
			if(auto segmentName = parse_segment_name(); segmentName.has_value())
				return segmentName.value();
			if(auto variable = parse_variable(); variable.has_value())
				return variable.value();

			return std::unexpected{parse_error{"expected segment part", m_current_token}};
		}
		constexpr std::expected<path_segment_name_expr, parse_error> parse_segment_name(){
			if(auto matchRes = match_all({ path_token_type::identifier }); matchRes.has_value())
				return path_segment_name_expr{matchRes.value()[0].lexeme()};
			else
				return std::unexpected{parse_error{"expected segment name", m_current_token}};
		}
		constexpr std::expected<path_variable_expr, parse_error> parse_variable(){
			if(auto matchRes = match_all({ path_token_type::variable }); matchRes.has_value())
				return path_variable_expr{ matchRes.value()[0].variable_type.value(), matchRes.value()[0].variable_name() };
			else
				return std::unexpected{parse_error{"expected variable", m_current_token}};
		}
	private:
		constexpr bool does_match_any(std::initializer_list<path_token_type> types) const{
			for(path_token_type type : types){
				if(check(type))
					return true;
			}

			return false;
		}

		constexpr bool match_any(std::initializer_list<path_token_type> types){
			if(does_match_any(types)){
				advance();
				return true;
			}
			return false;
		}

		constexpr bool does_match_all(std::initializer_list<path_token_type> types) const{
			std::size_t i = 0;
			for(path_token_type type : types){
				if(!check(type, i++))
					return false;
			}

			return true;
		}

		constexpr std::optional<std::vector<path_token>> match_all(std::initializer_list<path_token_type> types){
			std::vector<path_token> tokens{};
			if(does_match_all(types)){
				for(std::size_t i = 0; i < types.size(); ++i){
					tokens.push_back(advance());
				}
				return tokens;
			}

			return std::nullopt;
		}

		constexpr bool check(path_token_type type, std::size_t ahead = 0) const{
			if(is_at_end(ahead))
				return type == path_token_type::eof;

			return peek(ahead).type == type;
		}

		constexpr path_token advance(){
			if(!is_at_end())
				m_current_token++;

			return previous();
		}

		constexpr bool is_at_end(std::size_t ahead = 0) const{
			return peek(ahead).type == path_token_type::eof;
		}

		constexpr path_token peek(std::size_t ahead = 0) const{
			if(m_tokens.size() < (m_current_token + ahead))
				return m_tokens[m_tokens.size() - 1];
			return m_tokens[m_current_token + ahead];
		}

		constexpr path_token previous() const{
			return m_tokens[m_current_token - 1];
		}

		template<string_literal TErrorMessage>
		constexpr std::expected<path_token, parse_error> consume(path_token_type type){
			if(check(type))
				return advance();

			return std::unexpected{parse_error{TErrorMessage.value}};
		}

		std::size_t m_current_token = 0;
		std::vector<esnwx::http::detail::path_token> m_tokens;
	};
}
#endif
