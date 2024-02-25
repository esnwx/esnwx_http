#ifndef H_ESNWX_HTTP_STATUS_CODE
#define H_ESNWX_HTTP_STATUS_CODE

#include <iostream>
#include <cstdint>
#include <utility>

namespace esnwx::http{
	enum class status_code : std::uint16_t{
		success_100_continue = 100,
		success_101_switching_protocols = 101,
		success_102_processing = 102,
		success_103_early_hints = 103,

		success_200_ok = 200,
		success_201_created = 201,
		success_202_accepted = 202,
		success_203_non_authoritative_information = 203,
		success_204_no_content = 204,
		success_205_reset_content = 205,
		success_206_partial_content = 206,
		success_207_multi_status = 207,
		success_208_already_reported = 208,
		success_218_this_is_fine = 218,
		success_226_im_used = 226,

		redirect_300_multiple_choices = 300,
		redirect_301_moved_permanently = 301,
		redirect_302_found = 302,
		redirect_303_see_other = 303,
		redirect_304_not_modified = 304,
		redirect_305_use_proxy = 305,
		redirect_307_temporary_redirect = 307,
		redirect_308_permanent_redirect = 308,

		client_error_400_bad_request = 400,
		client_error_401_unauthorized = 401,
		client_error_402_payment_required = 402,
		client_error_403_forbidden = 403,
		client_error_404_not_found = 404,
		client_error_405_method_not_allowed = 405,
		client_error_406_not_acceptable = 406,
		client_error_407_proxy_authentication_required = 407,
		client_error_408_request_timeout = 408,
		client_error_409_conflict = 409,
		client_error_410_gone = 410,
		client_error_411_length_required = 411,
		client_error_412_precondition_failed = 412,
		client_error_413_payload_too_large = 413,
		client_error_414_uri_too_long = 414,
		client_error_415_unsupported_media_type = 415,
		client_error_416_range_not_satisfiable = 416,
		client_error_417_expectation_failed = 417,
		client_error_418_im_a_teapot = 418,
		client_error_419_page_expired = 419,
		client_error_420_enhance_your_calm = 420,
		client_error_421_misdirected_request = 421,
		client_error_422_unprocessable_content = 422,
		client_error_423_locked = 423,
		client_error_424_failed_dependency = 424,
		client_error_425_too_early = 425,
		client_error_426_upgrade_required = 426,
		client_error_428_precondition_required = 428,
		client_error_429_too_many_requests = 429,
		client_error_431_request_header_fields_too_large = 431,
		client_error_440_login_time_out = 440,
		client_error_444_no_response = 444,
		client_error_451_unavailable_for_legal_reasons = 451,
		client_error_495_ssl_certificate_error = 495,
		client_error_496_ssl_certificate_required = 496,
		client_error_497_http_request_sent_to_https_port = 497,
		client_error_499_client_closed_request = 499,

		server_error_500_internal_server_error = 500,
		server_error_501_not_implemented = 501,
		server_error_502_bad_gateway = 502,
		server_error_503_service_unavailable = 503,
		server_error_504_gateway_timeout = 504,
		server_error_505_http_version_not_supported = 505,
		server_error_506_variant_also_negotiates = 506,
		server_error_507_insufficient_storage = 507,
		server_error_508_loop_detected = 508,
		server_error_511_network_authentication_required = 511,
		server_error_529_site_is_overloaded = 529,
		server_error_530_site_is_frozen = 530,
		server_error_540_temporarily_disabled = 540
	};

	enum class information_code : std::uint16_t{
		continue_100 = 100,
		switching_protocols_101 = 101,
		processing_102 = 102,
		early_hints_103 = 103
	};

	enum class success_code : std::uint16_t{
		ok_200 = 200,
		created_201 = 201,
		accepted_202 = 202,
		non_authoritative_information_203 = 203,
		no_content_204 = 204,
		reset_content_205 = 205,
		partial_content_206 = 206,
		multi_status_207 = 207,
		already_reported_208 = 208,
		this_is_fine_218 = 218,
		im_used_226 = 226
	};

	enum class redirect_code : std::uint16_t{
		multiple_choices_300 = 300,
		moved_permanently_301 = 301,
		found_302 = 302,
		see_other_303 = 303,
		not_modified_304 = 304,
		use_proxy_305 = 305,
		temporary_redirect_307 = 307,
		permanent_redirect_308 = 308
	};

	enum class client_error_code : std::uint16_t{
		bad_request_400 = 400,
		unauthorized_401 = 401,
		payment_required_402 = 402,
		forbidden_403 = 403,
		not_found_404 = 404,
		method_not_allowed_405 = 405,
		not_acceptable_406 = 406,
		proxy_authentication_required_407 = 407,
		request_timeout_408 = 408,
		conflict_409 = 409,
		gone_410 = 410,
		length_required_411 = 411,
		precondition_failed_412 = 412,
		payload_too_large_413 = 413,
		uri_too_long_414 = 414,
		unsupported_media_type_415 = 415,
		range_not_satisfiable_416 = 416,
		expectation_failed_417 = 417,
		im_a_teapot_418 = 418,
		page_expired_419 = 419,
		enhance_you_calm = 420,
		misdirected_request_421 = 421,
		unprocessable_content_422 = 422,
		locked_423 = 423,
		failed_dependency_424 = 424,
		too_early_425 = 425,
		upgrade_required_426 = 426,
		precondition_required_428 = 428,
		too_many_requests_429 = 429,
		request_header_fields_too_large_431 = 431,
		login_time_out_440 = 440,
		no_response_444 = 444,
		unavailable_for_legal_reasons_451 = 451,
		ssl_certificate_error_495 = 495,
		ssl_certificate_required_496 = 496,
		http_request_sent_to_https_port_497 = 497,
		client_closed_request_499 = 499
	};

	enum class server_error_code : std::uint16_t{
		internal_server_error_500 = 500,
		not_implemented_501 = 501,
		bad_gateway_502 = 502,
		service_unavailable_503 = 503,
		gateway_timeout_504 = 504,
		http_version_not_supported_505 = 505,
		variant_also_negotiates_506 = 506,
		insufficient_storage_507 = 507,
		loop_detected_508 = 508,
		network_authentication_required_511 = 511,
		site_is_overloaded_529 = 529,
		site_is_frozen_530 = 530,
		temporarily_disabled_540 = 540
	};

	static constexpr std::string_view name_to_string(status_code status){
		switch(status){
		case status_code::success_100_continue:
			return "Continue";
		case status_code::success_101_switching_protocols:
			return "Switching Protocols";
		case status_code::success_102_processing:
			return "Processing";
		case status_code::success_103_early_hints:
			return "Early Hints";
		case status_code::success_200_ok:
			return "OK";
		case status_code::success_201_created:
			return "Created";
		case status_code::success_202_accepted:
			return "Accepted";
		case status_code::success_203_non_authoritative_information:
			return "Non-Authoritative Information";
		case status_code::success_204_no_content:
			return "No Content";
		case status_code::success_205_reset_content:
			return "Reset Content";
		case status_code::success_206_partial_content:
			return "Partial Content";
		case status_code::success_207_multi_status:
			return "Multi-Status";
		case status_code::success_208_already_reported:
			return "Already Reported";
		case status_code::success_218_this_is_fine:
			return "This Is Fine";
		case status_code::success_226_im_used:
			return "IM Used";
		case status_code::redirect_300_multiple_choices:
			return "Multiple Choices";
		case status_code::redirect_301_moved_permanently:
			return "Moved Permanently";
		case status_code::redirect_302_found:
			return "Found";
		case status_code::redirect_303_see_other:
			return "See Other";
		case status_code::redirect_304_not_modified:
			return "Not Modified";
		case status_code::redirect_305_use_proxy:
			return "Use Proxy";
		case status_code::redirect_307_temporary_redirect:
			return "Temporary Redirect";
		case status_code::redirect_308_permanent_redirect:
			return "Permanent Redirect";
		case status_code::client_error_400_bad_request:
			return "Bad Request";
		case status_code::client_error_401_unauthorized:
			return "Unauthorized";
		case status_code::client_error_402_payment_required:
			return "Payment Required";
		case status_code::client_error_403_forbidden:
			return "Forbidden";
		case status_code::client_error_404_not_found:
			return "Not Found";
		case status_code::client_error_405_method_not_allowed:
			return "Method Not Allowed";
		case status_code::client_error_406_not_acceptable:
			return "Not Acceptable";
		case status_code::client_error_407_proxy_authentication_required:
			return "Proxy Authentication Required";
		case status_code::client_error_408_request_timeout:
			return "Request Timeout";
		case status_code::client_error_409_conflict:
			return "Conflict";
		case status_code::client_error_410_gone:
			return "Gone";
		case status_code::client_error_411_length_required:
			return "Length Required";
		case status_code::client_error_412_precondition_failed:
			return "Precondition Failed";
		case status_code::client_error_413_payload_too_large:
			return "Payload Too Large";
		case status_code::client_error_414_uri_too_long:
			return "URI Too Long";
		case status_code::client_error_415_unsupported_media_type:
			return "Unsupported Media Type";
		case status_code::client_error_416_range_not_satisfiable:
			return "Range Not Satisfiable";
		case status_code::client_error_417_expectation_failed:
			return "Expectation Failed";
		case status_code::client_error_418_im_a_teapot:
			return "I'm a teapot";
		case status_code::client_error_419_page_expired:
			return "Page Expired";
		case status_code::client_error_420_enhance_your_calm:
			return "Enhance Your Calm";
		case status_code::client_error_421_misdirected_request:
			return "Misdirected Request";
		case status_code::client_error_422_unprocessable_content:
			return "Unprocessable Content";
		case status_code::client_error_423_locked:
			return "Locked";
		case status_code::client_error_424_failed_dependency:
			return "Failed Dependency";
		case status_code::client_error_425_too_early:
			return "Too Early";
		case status_code::client_error_426_upgrade_required:
			return "Upgrade Required";
		case status_code::client_error_428_precondition_required:
			return "Precondition Required";
		case status_code::client_error_429_too_many_requests:
			return "Too Many Requests";
		case status_code::client_error_431_request_header_fields_too_large:
			return "Request Header Fields Too Large";
		case status_code::client_error_440_login_time_out:
			return "Login Time Out";
		case status_code::client_error_444_no_response:
			return "No Response";
		case status_code::client_error_451_unavailable_for_legal_reasons:
			return "Unavailable For Legal Reasons";
		case status_code::client_error_495_ssl_certificate_error:
			return "SSL Certificate Error";
		case status_code::client_error_496_ssl_certificate_required:
			return "SSL Certificate Required";
		case status_code::client_error_497_http_request_sent_to_https_port:
			return "HTTP Request Sent To HTTPS Port";
		case status_code::client_error_499_client_closed_request:
			return "Client Closed Request";
		case status_code::server_error_500_internal_server_error:
			return "Internal Server Error";
		case status_code::server_error_501_not_implemented:
			return "Not Implemented";
		case status_code::server_error_502_bad_gateway:
			return "Bad Gateway";
		case status_code::server_error_503_service_unavailable:
			return "Service Unavailable";
		case status_code::server_error_504_gateway_timeout:
			return "Gateway Timeout";
		case status_code::server_error_505_http_version_not_supported:
			return "HTTP Version Not Supported";
		case status_code::server_error_506_variant_also_negotiates:
			return "Variant Also Negotiates";
		case status_code::server_error_507_insufficient_storage:
			return "Insufficient Storage";
		case status_code::server_error_508_loop_detected:
			return "Loop Detected";
		case status_code::server_error_511_network_authentication_required:
			return "Network Authentication Required";
		case status_code::server_error_529_site_is_overloaded:
			return "Site Is Overloaded";
		case status_code::server_error_530_site_is_frozen:
			return "Site Is Frozen";
		case status_code::server_error_540_temporarily_disabled:
			return "Temporarily Disabled";
		}
		std::unreachable();
	}

	static std::string to_string(status_code status){
		return std::to_string(static_cast<std::uint16_t>(status)) + " " + std::string(name_to_string(status));
	}

	static std::ostream& operator<<(std::ostream& stream, status_code status){
		stream << to_string(status);
		return stream;
	}
}
#endif
