#ifndef H_ESNWX_HTTP_PATH_SGEMENT_NAME_EXPR
#define H_ESNWX_HTTP_PATH_SGEMENT_NAME_EXPR

#include <string_view>

namespace esnwx::http::detail{
	struct path_segment_name_expr{
		std::string_view name;
	};
}
#endif
