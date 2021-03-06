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
bool test_func()
{
	return true;
}
bool test_fail()
{
	return false;
}
struct test_functor
{
	bool operator()() const noexcept
	{
		return true;
	}
};
auto test_lambda = []()
{
	return true;
};
int main()
{
	TestSuite::TestSuites::new_test_suite("test");
	TestSuite::TestSuites::add_test(test_func);
	TestSuite::TestSuites::add_test(test_functor());
	TestSuite::TestSuites::add_test(test_lambda);
	TestSuite::TestSuites::add_test(test_fail);
	TestSuite::TestSuites::run_tests();
	return 0;
}
