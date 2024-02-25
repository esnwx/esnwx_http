#include <iostream>
#include "include/request.hpp"
#include "test/user.hpp"
#include "test/todo.hpp"

void test_user(){
	using namespace esnwx::http::test::user;
	namespace http = esnwx::http;

	user_handler h{};

	auto getAll = [&](){
		std::cout << ">>> [get users()]";
		auto resGetAll = h.get_all(http::request<>{});
		std::cout << ": " << resGetAll.status << "\n";
		if(resGetAll.has_value())
			print_users(resGetAll);
		std::cout << "\n";
	};

	auto get = [&](std::uint64_t id){
		std::cout << ">>> [get user(id=" << id << ")]";
		auto resGet = h.get(http::request<>{}, id);
		std::cout << ": "  << resGet.status << "\n";
		if(resGet.has_value())
			print_user(resGet);
		std::cout << "\n";
	};

	auto post = [&](user newUser){
		std::cout << ">>> [post user()]";
		auto resPost = h.post(http::request<user>{newUser});
		std::cout << ": "  << resPost.status << "\n";
		if(resPost.has_value())
			print_user(resPost);
		std::cout << "\n";
	};

	auto put = [&](std::uint64_t id, user newUser){
		std::cout << ">>> [put user(id=" << id << ")]";
		auto resPut = h.put(http::request<user>{newUser}, id);
		std::cout << ": "  << resPut.status << "\n";
		if(resPut.has_value())
			print_user(resPut);
		std::cout << "\n";
	};

	auto del = [&](std::uint64_t id){
		std::cout << ">>> [delete user(id=" << id << ")]";
		auto resDel = h.del(http::request<>{}, id);
		std::cout << ": "  << resDel.status << "\n";
		std::cout << "\n";
	};

	auto search = [&](std::string_view name){
		std::cout << ">>> [get user(username=" << name << ")]";
		auto resSearch = h.search_by_name(http::request<>{}, name);
		std::cout << ": "  << resSearch.status << "\n";
		if(resSearch.has_value())
			print_user(resSearch);
		std::cout << "\n";
	};

	getAll();
	get(1);
	post(user{1, "abc"});
	get(1);
	getAll();
	post(user{2, "def"});
	post(user{3, "ghi"});
	getAll();
	put(2, user{2, "jkl"});
	put(3, user{4, "ghi"});
	getAll();
	del(2);
	getAll();
	search("ghi");
}

void test_todo(){
	using namespace esnwx::http::test::todo;
	namespace http = esnwx::http;

	todo_handler t{};

	auto getAll = [&](){
		std::cout << ">>> [get todos()]";
		auto resGetAll = t.get_all(http::request<>{});
		std::cout << ": " << resGetAll.status << "\n";
		if(resGetAll.has_value())
			print_todos(resGetAll);
		std::cout << "\n";
	};

	auto get = [&](std::uint64_t id){
		std::cout << ">>> [get todo(id=" << id << ")]";
		auto resGet = t.get(http::request<>{}, id);
		std::cout << ": "  << resGet.status << "\n";
		if(resGet.has_value())
			print_todo(resGet);
		std::cout << "\n";
	};

	auto post = [&](todo newTodo){
		std::cout << ">>> [post todo()]";
		auto resPost = t.post(http::request<todo>{newTodo});
		std::cout << ": "  << resPost.status << "\n";
		if(resPost.has_value())
			print_todo(resPost);
		std::cout << "\n";
	};

	auto put = [&](std::uint64_t id, todo newTodo){
		std::cout << ">>> [put todo(id=" << id << ")]";
		auto resPut = t.put(http::request<todo>{newTodo}, id);
		std::cout << ": "  << resPut.status << "\n";
		if(resPut.has_value())
			print_todo(resPut);
		std::cout << "\n";
	};

	auto del = [&](std::uint64_t id){
		std::cout << ">>> [delete todo(id=" << id << ")]";
		auto resDel = t.del(http::request<>{}, id);
		std::cout << ": "  << resDel.status << "\n";
		std::cout << "\n";
	};

	auto search = [&](std::string_view name){
		std::cout << ">>> [get todo(name=" << name << ")]";
		auto resSearch = t.search_by_name(http::request<>{}, name);
		std::cout << ": "  << resSearch.status << "\n";
		if(resSearch.has_value())
			print_todo(resSearch);
		std::cout << "\n";
	};

	auto patch = [&](std::uint64_t id, bool finished){
		std::cout << ">>> [patch todo.finished(id=" << id << ", finished=" << (finished ? "true" : "false") << ")]";
		auto resPatch = t.patch_finished(http::request<bool>{finished}, id);
		std::cout << ": " << resPatch.status << "\n";
		if(resPatch.has_value())
			print_todo(resPatch);
		std::cout << "\n";
	};

	getAll();
	get(1);
	post(todo{1, "abc"});
	get(1);
	getAll();
	post(todo{2, "def", false});
	post(todo{3, "ghi", true});
	getAll();
	put(2, todo{2, "def", true});
	put(3, todo{4, "ghi", true});
	getAll();
	patch(4, false);
	getAll();
	del(2);
	getAll();
	search("ghi");
}

int main(int argc, char* argv[]){
	test_user();
	std::cout << "-----------------------------\n";
	test_todo();
	return 0;
}
