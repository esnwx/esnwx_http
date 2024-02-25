#ifndef H_ESNWX_HTTP_PATH_QUERY_EXPR
#define H_ESNWX_HTTP_PATH_QUERY_EXPR

#include <vector>
#include "path-key-value-pair-expr.hpp"

namespace esnwx::http::detail{
	struct path_query_expr{
		std::vector<path_key_value_pair_expr> key_value_pairs;
	};
}
#endif
