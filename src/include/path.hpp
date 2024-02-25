#ifndef H_ESNWX_HTTP_PATH
#define H_ESNWX_HTTP_PATH

#include "parser/path-parser.hpp"
#include "parser/path-token.hpp"
#include "string_literal.hpp"

namespace esnwx::http{
	template<detail::variable_type Type>
	struct variable_type;

	template<> struct variable_type<detail::variable_type::boolean>{
		using type = bool;
	};
	template<> struct variable_type<detail::variable_type::int8>{
		using type = std::int8_t;
	};
	template<> struct variable_type<detail::variable_type::uint8>{
		using type = std::uint8_t;
	};
	template<> struct variable_type<detail::variable_type::int16>{
		using type = std::int16_t;
	};
	template<> struct variable_type<detail::variable_type::uint16>{
		using type = std::uint16_t;
	};
	template<> struct variable_type<detail::variable_type::int32>{
		using type = std::int32_t;
	};
	template<> struct variable_type<detail::variable_type::uint32>{
		using type = std::uint32_t;
	};
	template<> struct variable_type<detail::variable_type::int64>{
		using type = std::int64_t;
	};
	template<> struct variable_type<detail::variable_type::uint64>{
		using type = std::uint64_t;
	};
	template<> struct variable_type<detail::variable_type::character>{
		using type = char;
	};
	template<> struct variable_type<detail::variable_type::string>{
		using type = std::string_view;
	};

	template<detail::variable_type Type>
	using variable_type_t = variable_type<Type>::type;

	template<esnwx::http::string_literal TPath>
	static constexpr std::size_t count_params(){
		return detail::path_parser<TPath>::param_count().value();
	}

	template<esnwx::http::string_literal TPath>
	struct param_count{
		static constexpr std::size_t value = count_params<TPath>();
	};

	template<esnwx::http::string_literal TPath>
	static constexpr std::size_t param_count_v = param_count<TPath>::value;

	template<std::size_t N, esnwx::http::string_literal TPath>
	concept ParamIndex = N < param_count_v<TPath>;

	template<esnwx::http::string_literal TPath, std::size_t N> requires ParamIndex<N, TPath>
	struct param_type_n{
		using type = variable_type_t<detail::path_parser<TPath>::template param_type_n<N>().value()>;
	};

	template<esnwx::http::string_literal TPath, std::size_t N> requires ParamIndex<N, TPath>
	using param_type_n_t = param_type_n<TPath, N>::type;
}
#endif
