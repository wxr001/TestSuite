// Simple Test Suite Library -*- C++ -*-

// Copyright (C) 2017  Scott Brown

// This file is part of the STSL library.
// This library is free software: you can redistribute it and/or modify
// it under the terms of the GNU Lesser General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.

// This library is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU Lesser General Public License for more details.

// You should have received a copy of the GNU Lesser General Public License
// along with this library.  If not, see <http://www.gnu.org/licenses/>.

#ifndef SIMPLE_TEST_SUITE_LIBRARY_TEST_SUITE
#define SIMPLE_TEST_SUITE_LIBRARY_TEST_SUITE
#include <functional>// function
#include <string>// string, to_string, operator""s
#include <type_traits>// enable_if_t, is_invocable_r_v
#include <unordered_map>// unordered_map
#include <utility>// forward
#include <vector>// vector

namespace TestSuite
{
	using namespace std::string_literals;
	#define T_ASSERT_OP(lhs, rhs, op) if(!((lhs) op (rhs))) return false;
	#define T_ASSERT_EQ(lhs, rhs) T_ASSERT_OP(lhs, rhs, ==)
	#define T_ASSERT_NE(lhs, rhs) T_ASSERT_OP(lhs, rhs, !=)
	#define T_ASSERT_LT(lhs, rhs) T_ASSERT_OP(lhs, rhs, <)
	#define T_ASSERT_GT(lhs, rhs) T_ASSERT_OP(lhs, rhs, >)
	#define T_ASSERT_LE(lhs, rhs) T_ASSERT_OP(lhs, rhs, <=)
	#define T_ASSERT_GE(lhs, rhs) T_ASSERT_OP(lhs, rhs, >=)
	#define T_ASSERT(lhs) if(!(lhs)) return false;
	class SingleTestSuite
	{
	public:
		template <typename T, 
				 typename = std::enable_if_t<std::is_invocable_r_v<bool, T>>>
		void resiger_test(T&& func)
		{
			_test_functions.emplace_back(std::forward<T>(func));
		}
		bool run_test() const;
	private:
		std::vector<std::function<bool()>> _test_functions{};
	};
	class TestSuites
	{
	public:
		static void new_test_suite(const std::string& str)
		{
			static std::size_t id = 0;
			std::string name = "Test Suite"s + std::to_string(++id) + " : "s + str;
			_suites_index.emplace_back(name);
			_suites.emplace(name, SingleTestSuite());
			_current_suites = name;
		}
		template <typename T, 
				 typename = std::enable_if_t<std::is_invocable_r_v<bool, T>>>
		static bool add_test(T&& func)
		{
			if(_current_suites.empty())
			{
				// test suite can not be found.
				return false;
			}
			_suites[_current_suites].resiger_test(std::forward<T>(func));
			return true;
		}
		template <typename T, 
				 typename = std::enable_if_t<std::is_invocable_r_v<bool, T>>>
		static bool add_test(const std::string& name, T&& func)
		{
			if(_suites.find(name) == _suites.end())
			{
				// test suite can not be found.
				return false;
			}
			_suites[name].resiger_test(std::forward<T>(func));
			return true;
		}
		static bool run_tests();
	private:
		static std::vector<std::string> _suites_index;
		static std::unordered_map<std::string, SingleTestSuite> _suites;
		static std::string _current_suites;
	};
}
#endif
