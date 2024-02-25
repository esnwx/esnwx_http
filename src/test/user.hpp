#ifndef H_ESNWX_HTTP_TEST_USER
#define H_ESNWX_HTTP_TEST_USER

#include <span>
#include <vector>
#include <string>
#include <cstdint>
#include <algorithm>
#include <ranges>
#include "../include/handler.hpp"

namespace esnwx::http::test::user{
	struct user{
		std::uint64_t id;
		std::string name;
	};

	class user_handler{
	public:
		http::lambda_handler<http::method::get, "/api/user", std::span<const user>> get_all{
			[&](http::request<> req)->http::response<std::span<const user>>{
				return { m_users, http::success_code::ok_200 };
			}
		};

		http::lambda_handler<http::method::get, "/api/user/<uint64 id>", user> get{
			[&](http::request<> req, std::uint64_t id)->http::response<user>{
				auto matchingUsers = m_users
					| std::views::filter([id](const user& user){ return user.id == id; })
					| std::ranges::to<std::vector>();

				if(matchingUsers.size() == 0)
					return { http::client_error_code::not_found_404 };
				else if(matchingUsers.size() > 1)
					return { http::server_error_code::internal_server_error_500 };
				else
					return { matchingUsers[0], http::success_code::ok_200 };
			}
		};

		http::lambda_handler<http::method::post, "/api/user", user, user> post{
			[&](http::request<user> req)->http::response<user>{
				m_users.push_back(req.data);
				return { req.data, http::success_code::ok_200 };
			}
		};

		http::lambda_handler<http::method::put, "/api/user/<uint64 id>", user, user> put{
			[&](http::request<user> req, std::uint64_t id)->http::response<user>{
				for(user& u : m_users){
					if(u.id != id)
						continue;

					u = req.data;
					return { req.data, http::success_code::ok_200 };
				}

				return { http::client_error_code::not_found_404 };
			}
		};

		http::lambda_handler<http::method::del, "/api/user/<uint64 id>"> del{
			[&](http::request<> req, std::uint64_t id)->http::response<>{
				if(std::erase_if(m_users, [id](const user& user){ return user.id == id; }) > 0)
					return { http::success_code::ok_200 };
				else
					return { http::client_error_code::not_found_404 };
			}
		};

		http::lambda_handler<http::method::get, "/api/user/search?name=<string username>", user> search_by_name{
			[&](http::request<> req, std::string_view username)->http::response<user>{
				auto matchingUsers = m_users
					| std::views::filter([username](const user& user){ return user.name == username; })
					| std::ranges::to<std::vector>();

				if(matchingUsers.size() == 0)
					return { http::client_error_code::not_found_404 };
				else if(matchingUsers.size() > 1)
					return { http::server_error_code::internal_server_error_500 };
				else
					return { matchingUsers[0], http::success_code::ok_200 };
			}
		};
	private:
		std::vector<user> m_users{};
	};

	static void print_user(const user& u){
		std::cout << "\tuser #" << u.id << ": (name = " << u.name << ")\n";
	}

	static void print_users(std::span<const user> users){
		std::cout << "users: [\n";
		std::size_t i = 0;
		for(const user& u : users){
			std::cout << "(" << (i++) << "): ";
			print_user(u);
		}
		std::cout << "]\n";
	}
}
#endif
