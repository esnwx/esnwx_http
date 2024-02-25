#ifndef H_ESNWX_HTTP_RESPONSE
#define H_ESNWX_HTTP_RESPONSE

#include <optional>
#include <expected>
#include <exception>
#include "status_code.hpp"

namespace esnwx::http{
	template<typename T = void>
	struct response{
	public:
		static constexpr response<T> information(information_code status){
			return response<T>{static_cast<status_code>(static_cast<std::uint16_t>(status)), std::nullopt};
		}

		constexpr response(information_code status)
			: status(static_cast<status_code>(static_cast<std::uint16_t>(status))),
			data(std::nullopt){

		}

		static constexpr response<T> success(const T& data, success_code status){
			return response<T>{static_cast<status_code>(static_cast<std::uint16_t>(status)), data};
		}

		constexpr response(const T& data, success_code status)
			: status(static_cast<status_code>(static_cast<std::uint16_t>(status))),
			data(data){

		}

		static constexpr response<T> server_error(server_error_code status){
			return response<T>{static_cast<status_code>(static_cast<std::uint16_t>(status)), std::nullopt};
		}

		constexpr response(server_error_code status)
			: status(static_cast<status_code>(static_cast<std::uint16_t>(status))),
			data(std::nullopt){

		}

		static constexpr response<T> client_error(client_error_code status){
			return response<T>{static_cast<status_code>(static_cast<std::uint16_t>(status)), std::nullopt};
		}

		constexpr response(client_error_code status)
			: status(static_cast<status_code>(static_cast<std::uint16_t>(status))),
			data(std::nullopt){

		}

		static constexpr response<T> redirect(redirect_code status){
			return response<T>{static_cast<status_code>(static_cast<std::uint16_t>(status)), std::nullopt};
		}

		constexpr response(redirect_code status)
			: status(static_cast<status_code>(static_cast<std::uint16_t>(status))),
			data(std::nullopt){

		}

		status_code status;
		std::optional<T> data;

		constexpr bool has_value() const{
			return data.has_value();
		}

		operator T() const{
			if(!has_value())
				throw std::bad_optional_access{};

			return data.value();
		}

		operator std::expected<T, std::bad_optional_access>() const noexcept{
			if(!has_value())
				return std::unexpected{std::bad_optional_access{}};

			return data.value();
		}
	private:
		constexpr response(status_code status, const std::optional<T>& data = std::nullopt)
			: data(data), status(status){}
	};



	template<>
	struct response<void>{
	public:
		static constexpr response<void> information(information_code status){
			return response<void>{static_cast<status_code>(static_cast<std::uint16_t>(status))};
		}

		constexpr response(information_code status)
			: status(static_cast<status_code>(static_cast<std::uint16_t>(status))){

		}

		static constexpr response<void> success(success_code status){
			return response<void>{static_cast<status_code>(static_cast<std::uint16_t>(status))};
		}

		constexpr response(success_code status)
			: status(static_cast<status_code>(static_cast<std::uint16_t>(status))){

		}

		static constexpr response<void> server_error(server_error_code status){
			return response<void>{static_cast<status_code>(static_cast<std::uint16_t>(status))};
		}

		constexpr response(server_error_code status)
			: status(static_cast<status_code>(static_cast<std::uint16_t>(status))){

		}

		static constexpr response<void> client_error(client_error_code status){
			return response<void>{static_cast<status_code>(static_cast<std::uint16_t>(status))};
		}

		constexpr response(client_error_code status)
			: status(static_cast<status_code>(static_cast<std::uint16_t>(status))){

		}

		static constexpr response<void> redirect(redirect_code status){
			return response<void>{static_cast<status_code>(static_cast<std::uint16_t>(status))};
		}

		constexpr response(redirect_code status)
			: status(static_cast<status_code>(static_cast<std::uint16_t>(status))){

		}

		status_code status;
	private:
		constexpr response(status_code status)
			: status(status){}
	};
}
#endif
