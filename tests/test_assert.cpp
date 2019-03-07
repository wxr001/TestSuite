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

#include "../include/TestSuite.hpp"
using namespace TestSuite;
bool test_assert()
{
	auto false_ret = []()
	{
		T_ASSERT(false);
		return true;
	};
	T_ASSERT_EQ(false_ret(), false);
	T_ASSERT(!false_ret());
	return true;
}
bool test_eq()
{
	auto false_ret = []()
	{
		T_ASSERT_EQ(false, true);
		return true;
	};
	T_ASSERT_EQ(500, 500);
//  -Waddress
//  Comparison with string literal results in unspecified behavior.
//  T_ASSERT_EQ("Abcd", "Abcd");
	std::string compare_str = "a1 !]";
	std::string expect_str = compare_str;
	T_ASSERT_EQ(compare_str, expect_str);
	T_ASSERT_EQ(false_ret(), false);
	T_ASSERT(!false_ret());
	return true;
}
// Because implementations of macros like eq, ne, lt ... are the same, we only test eq here.
// More tests may be added later.
int main()
{
	TestSuite::TestSuites::new_test_suite("test");
	TestSuite::TestSuites::add_test(test_assert);
	TestSuite::TestSuites::add_test(test_eq);
	TestSuite::TestSuites::run_tests();
	return 0;
}
