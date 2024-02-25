#ifndef H_ESNWX_HTTP_PATH_VARIABLE_EXPR
#define H_ESNWX_HTTP_PATH_VARIABLE_EXPR

#include <string_view>
#include "../path-token.hpp"

namespace esnwx::http::detail{
	struct path_variable_expr{
		variable_type type;
		std::string_view name;
	};
}
#endif
