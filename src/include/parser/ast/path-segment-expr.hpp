#ifndef H_ESNWX_HTTP_PATH_SEGMENT_EXPR
#define H_ESNWX_HTTP_PATH_SEGMENT_EXPR

#include <variant>
#include <vector>

#include "path-segment-name-expr.hpp"
#include "path-variable-expr.hpp"

namespace esnwx::http::detail{
	struct path_segment_expr{
		using segment_part = std::variant<path_segment_name_expr, path_variable_expr>;
		std::vector<segment_part> segment_parts;
	};
}
#endif
