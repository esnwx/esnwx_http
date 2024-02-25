#ifndef H_ESNWX_HTTP_PATH_TOKEN
#define H_ESNWX_HTTP_PATH_TOKEN

#include <string>
#include <cstddef>
#include <optional>
#include <string_view>
#include <utility>

namespace esnwx::http::detail{
	enum class path_token_type{
		variable,
		identifier,
		question_mark,
		ampersand,
		equals,
		slash,
		less_than,
		greater_than,
		space,
		eof
	};

	static constexpr std::string_view token_type_to_string(path_token_type type){
		switch(type){
		case path_token_type::variable:
			return "variable";
		case path_token_type::identifier:
			return "identifier";
		case path_token_type::question_mark:
			return "question_mark";
		case path_token_type::ampersand:
			return "ampersand";
		case path_token_type::equals:
			return "equals";
		case path_token_type::slash:
			return "slash";
		case path_token_type::less_than:
			return "less_than";
		case path_token_type::greater_than:
			return "greater_than";
		case path_token_type::space:
			return "space";
		case path_token_type::eof:
			return "eof";
		}
		std::unreachable();
	}

	enum class variable_type{
		boolean,
		int8,
		uint8,
		int16,
		uint16,
		int32,
		uint32,
		int64,
		uint64,
		character,
		string
	};

	static constexpr std::string_view variable_type_to_string(variable_type type){
		switch(type){
			case variable_type::boolean:
				return "bool";
			case variable_type::int8:
				return "int8";
			case variable_type::uint8:
				return "uint8";
			case variable_type::int16:
				return "int16";
			case variable_type::uint16:
				return "uint16";
			case variable_type::int32:
				return "int32";
			case variable_type::uint32:
				return "uint32";
			case variable_type::int64:
				return "int64";
			case variable_type::uint64:
				return "uint64";
			case variable_type::character:
				return "char";
			case variable_type::string:
				return "string";
		}
		std::unreachable();
	}

	struct path_token{
		path_token_type type;
		std::size_t location;
		std::size_t length;
		std::string_view input_string;
		std::optional<esnwx::http::detail::variable_type> variable_type;
		std::optional<std::size_t> variable_name_split;

		constexpr std::string_view lexeme() const{
			return input_string.substr(location, length);
		}

		constexpr std::string_view variable_name() const{
			if(type != path_token_type::variable || !variable_name_split.has_value())
				return "";
			return input_string.substr(location + variable_name_split.value(), length - variable_name_split.value());
		}

		constexpr path_token(
			path_token_type type,
			std::size_t location,
			std::size_t length,
			std::string_view input_string,
			std::optional<esnwx::http::detail::variable_type> variable_type = std::nullopt,
			std::optional<std::size_t> variable_name_split = std::nullopt
		)
			: type(type),
			location(location),
			length(length),
			input_string(input_string),
			variable_type(variable_type),
			variable_name_split(variable_name_split){

		}

		std::string to_string() const{
			std::string str{};
			str += token_type_to_string(type);
			if(type == path_token_type::variable){
				str += "(";
				str += variable_type_to_string(variable_type.value());
				str += " ";
				str += variable_name();
				str += ")";
			}
			return str;
		}
	};
}
#endif
