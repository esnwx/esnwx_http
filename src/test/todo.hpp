#ifndef H_ESNWX_HTTP_TEST_TODO
#define H_ESNWX_HTTP_TEST_TODO

#include <vector>
#include <span>
#include <ranges>
#include <algorithm>
#include <cstdint>
#include "../include/handler.hpp"

namespace esnwx::http::test::todo{
	struct todo{
		std::uint64_t id;
		std::string name;
		bool finished;
	};

	class todo_handler{
	public:
		http::lambda_handler<http::method::get, "/api/todo", std::span<const todo>> get_all{
			[&](http::request<> req)->http::response<std::span<const todo>>{
				return { m_todos, http::success_code::ok_200 };
			}
		};

		http::lambda_handler<http::method::get, "/api/todo/<uint64 id>", todo> get{
			[&](http::request<> req, std::uint64_t id)->http::response<todo>{
				auto matchingTodos = m_todos
					| std::views::filter([id](const todo& todo){ return todo.id == id; })
					| std::ranges::to<std::vector>();

				if(matchingTodos.size() == 0)
					return { http::client_error_code::not_found_404 };
				else if(matchingTodos.size() > 0)
					return { http::server_error_code::internal_server_error_500 };
				else
					return { matchingTodos[0], http::success_code::ok_200 };
			}
		};

		http::lambda_handler<http::method::post, "/api/todo", todo, todo> post{
			[&](http::request<todo> req)->http::response<todo>{
				m_todos.push_back(req.data);
				return { req.data, http::success_code::ok_200 };
			}
		};

		http::lambda_handler<http::method::put, "/api/todo/<uint64 id>", todo, todo> put{
			[&](http::request<todo> req, std::uint64_t id)->http::response<todo>{
				for(todo& t : m_todos){
					if(t.id != id)
						continue;

					t = req.data;
					return { req.data, http::success_code::ok_200 };
				}

				return { http::client_error_code::not_found_404 };
			}
		};

		http::lambda_handler<http::method::del, "/api/todo/<uint64 id>"> del{
			[&](http::request<> req, std::uint64_t id)->http::response<>{
				if(std::erase_if(m_todos, [id](const todo& todo){ return todo.id == id; }) > 0)
					return { http::success_code::ok_200 };
				else
					return { http::client_error_code::not_found_404 };
			}
		};

		http::lambda_handler<http::method::get, "/api/todo/search?name=<string name>", todo> search_by_name{
			[&](http::request<> req, std::string_view name)->http::response<todo>{
				auto matchingTodos = m_todos
					| std::views::filter([name](const todo& todo){ return todo.name == name; })
					| std::ranges::to<std::vector>();

				if(matchingTodos.size() == 0)
					return { http::client_error_code::not_found_404 };
				else if(matchingTodos.size() > 1)
					return { http::server_error_code::internal_server_error_500 };
				else
					return { matchingTodos[0], http::success_code::ok_200 };
			}
		};

		http::lambda_handler<http::method::patch, "/api/todo/<uint64 id>/finished", todo, bool> patch_finished{
			[&](http::request<bool> req, std::uint64_t id)->http::response<todo>{
				for(todo& t : m_todos){
					if(t.id != id)
						continue;

					t.finished = req.data;
					return { t, http::success_code::ok_200 };
				}

				return { http::client_error_code::not_found_404 };
			}
		};

	private:
		std::vector<todo> m_todos;
	};

	static void print_todo(const todo& t){
		std::cout << "\ttodo #" << t.id << ": (name = " << t.name << ", finished = " << (t.finished ? "true" : "false") << ")\n";
	}

	static void print_todos(std::span<const todo> todos){
		std::cout << "todos: [\n";
		std::size_t i = 0;
		for(const todo& t : todos){
			std::cout << "(" << (i++) << "): ";
			print_todo(t);
		}
		std::cout << "]\n";
	}
}
#endif
