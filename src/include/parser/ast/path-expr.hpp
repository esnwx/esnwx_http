#ifndef H_ESNWX_HTTP_PATH_EXPR
#define H_ESNWX_HTTP_PATH_EXPR

#include <vector>
#include <optional>
#include "path-query-expr.hpp"
#include "path-segment-expr.hpp"

namespace esnwx::http::detail{
	struct path_expr{
		std::vector<path_segment_expr> segments;
		std::optional<path_query_expr> query;
	};
}
#endif
