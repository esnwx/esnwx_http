#ifndef H_ESNWX_HTTP_STRING_LITERAL
#define H_ESNWX_HTTP_STRING_LITERAL

#include <algorithm>
#include <cstddef>

namespace esnwx::http{
	template<std::size_t N>
	struct string_literal{
		static constexpr std::size_t size = N;

		constexpr string_literal(const char (&str)[N]){
			std::copy_n(str, N, value);
		}

		constexpr string_literal(const string_literal<N>& str){
			std::copy_n(str.value, N, value);
		}

		char value[N];
	};
}
#endif
