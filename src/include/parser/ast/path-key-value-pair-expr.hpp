#ifndef H_ESNWX_HTTP_PATH_KEY_VALUE_PAIR_EXPR
#define H_ESNWX_HTTP_PATH_KEY_VALUE_PAIR_EXPR

#include <variant>
#include <vector>

#include "path-segment-expr.hpp"
#include "path-segment-name-expr.hpp"
#include "path-variable-expr.hpp"

namespace esnwx::http::detail{
	struct path_key_value_pair_expr{
		path_segment_expr key_segment_parts;
		path_segment_expr value_segment_parts;
	};
}
#endif
