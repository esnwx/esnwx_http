#ifndef H_ESNWX_HTTP_PATH_LEXER
#define H_ESNWX_HTTP_PATH_LEXER

#include <string>
#include <expected>
#include <sstream>
#include <cstdint>
#include <functional>
#include <string_view>
#include <utility>
#include "../string_literal.hpp"
#include "path-token.hpp"

namespace esnwx::http::detail{
	struct lexer_error{
		std::string_view input_string;
		std::string_view message;
		std::size_t location;

		constexpr std::string_view error_location_string() const{
			return input_string.substr(location, 1);
		}
	};

	template<esnwx::http::string_literal TPath>
	class path_lexer{
	public:
		static constexpr std::pair<std::string_view, esnwx::http::detail::variable_type> variable_types[] = {
			{"bool", esnwx::http::detail::variable_type::boolean},
			{"int", esnwx::http::detail::variable_type::int32},
			{"uint", esnwx::http::detail::variable_type::uint32},
			{"int8", esnwx::http::detail::variable_type::int8},
			{"uint8", esnwx::http::detail::variable_type::uint8},
			{"int16", esnwx::http::detail::variable_type::int16},
			{"uint16", esnwx::http::detail::variable_type::uint16},
			{"int32", esnwx::http::detail::variable_type::int32},
			{"uint32", esnwx::http::detail::variable_type::uint32},
			{"int64", esnwx::http::detail::variable_type::int64},
			{"uint64", esnwx::http::detail::variable_type::uint64},
			{"char", esnwx::http::detail::variable_type::character},
			{"string", esnwx::http::detail::variable_type::string},
		};

		static constexpr std::expected<std::vector<path_token>, lexer_error> scan_all(){
			path_lexer<TPath> lexer{};
			auto token = lexer.next_token();
			std::vector<path_token> tokens{};
			while(token.has_value() && token.value().type != path_token_type::eof){
				tokens.push_back(token.value());
				token = lexer.next_token();
			}

			if(token.has_value())
				tokens.push_back(token.value());
			else
				return std::unexpected{token.error()};

			return tokens;
		}

		constexpr std::expected<path_token, lexer_error> next_token(){
			m_current_token_start = m_current;

			if(is_at_end())
				return create_token(esnwx::http::detail::path_token_type::eof);

			char c = advance();
			switch(c){
			case '\0':
				return create_token(esnwx::http::detail::path_token_type::eof);
			case '?':
				return create_token(esnwx::http::detail::path_token_type::question_mark);
			case '&':
				return create_token(esnwx::http::detail::path_token_type::ampersand);
			case '=':
				return create_token(esnwx::http::detail::path_token_type::equals);
			case '/':
				return create_token(esnwx::http::detail::path_token_type::slash);
			case ' ':
				return create_token(esnwx::http::detail::path_token_type::space);
			case '<':
				return try_scan_variable();
			default:
				if(is_segment_char(c)){
					while(is_segment_char(peek())){
						advance();
					}

					return create_token(esnwx::http::detail::path_token_type::identifier);
				}

				return create_error("unexpected character");
			}
		}

	private:
		constexpr std::expected<path_token, lexer_error> try_scan_variable(){
			std::optional<std::size_t> variable_name_split = std::nullopt;
			while(!is_at_end() && peek() != '>'){

				if(peek() == ' '){
					if(variable_name_split.has_value())
						return create_error("can't have multiple ' ' in a variable definition");
					else
						variable_name_split = (m_current - m_current_token_start);
				} else if(!is_segment_char(peek())){
					return create_error("unexpected character in variable");
				}
				advance();
			}

			if(is_at_end())
				return create_error("unterminated variable");

			if(!variable_name_split.has_value())
				return create_error("missing variable name");

			advance();

			std::string_view variable_type_name = std::string_view(TPath.value).substr(
				m_current_token_start + 1,
				variable_name_split.value() - 1
			);
			for(const auto& [key, value] : variable_types){
				if(variable_type_name == key)
					return create_variable_type_token(value, variable_name_split.value());
			}
			return create_error("unknown variable type");
		}

		constexpr std::optional<char> try_scan_hex_esacpe_char(){
			if(peek(0) != '%')
				return std::nullopt;
			if(!is_digit(peek(1)))
				return std::nullopt;
			if(!is_digit(peek(2)))
				return std::nullopt;

			m_current += 3;
			return (16 * peek(1)) + (1 * peek(2));
		}

		static constexpr bool is_unreserved_char(char c){
			return is_alnum(c)
				|| (c == '-')
				|| (c == '.')
				|| (c == '_')
				|| (c == '~')
				|| (c == ':')
				|| (c == '@');
		}

		static constexpr bool is_sub_delim_char(char c){
			return (c == '!')
				|| (c == '$')
				//|| (c == '&')
				//|| (c == '=')
				|| (c == '\'')
				|| (c == '(')
				|| (c == ')')
				|| (c == '*')
				|| (c == '+')
				|| (c == ',')
				|| (c == ';');
		}

		static constexpr bool is_segment_char(char c){
			return is_unreserved_char(c) || is_sub_delim_char(c);
		}

		static constexpr bool is_alnum(char c){
			return is_digit(c) || is_alpha(c);
		}

		static constexpr bool is_alpha(char c){
			return is_upper_alpha(c) || is_lower_alpha(c);
		}

		static constexpr bool is_upper_alpha(char c){
			return c >= 'A' && c <= 'Z';
		}

		static constexpr bool is_lower_alpha(char c){
			return c >= 'a' && c <= 'z';
		}

		static constexpr bool is_digit(char c){
			return c >= '0' && c <= '9';
		}

		constexpr bool match(char expected){
			if(is_at_end())
				return false;
			if(peek() != expected)
				return false;

			m_current++;
			return true;
		}

		constexpr char previous(std::size_t amount = 1) const{
			if(m_current < amount)
				return '\0';

			return TPath.value[m_current - amount];
		}

		constexpr char peek(std::size_t ahead = 0) const{
			if(is_at_end())
				return '\0';
			return TPath.value[m_current + ahead];
		}

		constexpr char advance(){
			return TPath.value[m_current++];
		}

		constexpr bool is_at_end() const{
			return m_current >= TPath.size;
		}

		template<std::size_t N>
		constexpr std::expected<esnwx::http::detail::path_token, lexer_error> create_error(
			const char (&error_text)[N]
		) const {
			return std::unexpected{lexer_error{TPath.value, error_text, m_current}};
		}

		constexpr esnwx::http::detail::path_token create_token(
			esnwx::http::detail::path_token_type token_type,
			std::optional<esnwx::http::detail::variable_type> variable_type = std::nullopt
		) const {
			return esnwx::http::detail::path_token{
				token_type,
				m_current_token_start,
				m_current - m_current_token_start,
				TPath.value,
				std::nullopt
			};
		}

		constexpr esnwx::http::detail::path_token create_variable_type_token(
			esnwx::http::detail::variable_type variable_type,
			std::size_t variable_name_split
		) const{
			return esnwx::http::detail::path_token{
				esnwx::http::detail::path_token_type::variable,
				m_current_token_start + 1,
				m_current - m_current_token_start - 2,
				TPath.value,
				variable_type,
				variable_name_split
			};
		}

		std::size_t m_current = 0;
		std::size_t m_current_token_start = 0;
	};
}
#endif
