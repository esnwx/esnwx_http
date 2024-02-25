#ifndef H_ESNWX_HTTP_REQUEST
#define H_ESNWX_HTTP_REQUEST
namespace esnwx::http{
	template<typename T = void>
	struct request{
		constexpr request(const T& data) : data(data){}
		T data;
	};

	template<>
	struct request<void>{
		constexpr request(){}
	};
}
#endif
