#ifndef H_ESNWX_HTTP_HANDLER
#define H_ESNWX_HTTP_HANDLER

#include "method.hpp"
#include "path.hpp"
#include "request.hpp"
#include "response.hpp"
#include "string_literal.hpp"
#include <utility>

namespace esnwx::http{
	template<
		esnwx::http::method TMethod,
		esnwx::http::string_literal UPath,
		typename VReturnType,
		typename WRequestType,
		typename Indices
	>
	struct handler_base;

	template<
		esnwx::http::method TMethod,
		esnwx::http::string_literal UPath,
		typename VReturnType,
		typename WRequestType,
		std::size_t... Is
	>
	struct handler_base<
		TMethod,
		UPath,
		VReturnType,
		WRequestType, std::index_sequence<Is...>
	>{
		template<std::size_t N>
		using param_type = param_type_n_t<UPath, N>;

		virtual response<VReturnType> operator()(request<WRequestType> req, param_type<Is>...) = 0;
	};

	template<
		esnwx::http::method TMethod,
		esnwx::http::string_literal UPath,
		typename VReturnType = void,
		typename WRequestType = void
	>
	struct handler : public handler_base<
		TMethod,
		UPath,
		VReturnType,
		WRequestType,
		std::make_index_sequence<param_count_v<UPath>>
	>{};

	template<
		esnwx::http::method TMethod,
		esnwx::http::string_literal UPath,
		typename VReturnType,
		typename WRequestType,
		typename IndexSequence
	>
	struct lambda_handler_base;

	template<
		esnwx::http::method TMethod,
		esnwx::http::string_literal UPath,
		typename VReturnType,
		typename WRequestType,
		std::size_t... Is
	>
	struct lambda_handler_base<
		TMethod,
		UPath,
		VReturnType,
		WRequestType,
		std::index_sequence<Is...>
	> : public handler_base<
		TMethod,
		UPath,
		VReturnType,
		WRequestType,
		std::index_sequence<Is...>
	>{
		template<std::size_t N>
		using param_type = param_type_n_t<UPath, N>;

		using handler_function_type = std::function<response<VReturnType>(request<WRequestType>, param_type<Is>...)>;
		constexpr lambda_handler_base(handler_function_type fn) : call(fn){}

		response<VReturnType> operator()(request<WRequestType> req, param_type<Is>... params) override{
			return call(req, params...);
		}

		handler_function_type call;
	};

	template<
		esnwx::http::method TMethod,
		esnwx::http::string_literal UPath,
		typename VReturnType = void,
		typename WRequestType = void
	>
	struct lambda_handler : public lambda_handler_base<
		TMethod,
		UPath,
		VReturnType,
		WRequestType,
		std::make_index_sequence<param_count_v<UPath>>
	>{
		using base = lambda_handler_base<TMethod, UPath, VReturnType, WRequestType, std::make_index_sequence<param_count_v<UPath>>>;
		using handler_function_type = base::handler_function_type;

		constexpr lambda_handler(handler_function_type fn) : base(fn){}
	};
}
#endif
