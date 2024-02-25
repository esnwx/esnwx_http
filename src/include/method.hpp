#ifndef H_ESNWX_HTTP_METHOD
#define H_ESNWX_HTTP_METHOD

namespace esnwx::http{
	enum class method{
		get,
		post,
		put,
		del,
		patch,
		head,
		connect,
		options,
		trace
	};
}
#endif
