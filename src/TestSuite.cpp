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
#include <iostream>

namespace TestSuite
{
	std::vector<std::string> TestSuites::_suites_index;
	std::unordered_map<std::string, SingleTestSuite> TestSuites::_suites;
	std::string TestSuites::_current_suites;
	bool SingleTestSuite::run_test() const
	{
		std::size_t total = _test_functions.size();
		std::size_t success = 0;
		std::size_t idx = 0;
		for(auto& test: _test_functions)
		{
			try
			{
				if(test())
				{
					++success;
				}
				else
				{
					std::cout<<"\tTest "<<idx + 1<<" failed."<<std::endl;
				}
			}
			catch(...)
			{
				std::cout<<"\tTest "<<idx + 1<<" failed with exceptions."<<std::endl;
			}
			++idx;
		}
		std::cout<<"\tTotal: "<<total
			<<", Success: "<<success
			<<", Failed: "<<total - success<<std::endl;
		return success == total;
	}
	bool TestSuites::run_tests()
	{
		std::size_t total = _suites_index.size();
		std::size_t success = 0;
		for(const auto& name: _suites_index)
		{
			std::cout<<name<<" ..."<<std::endl;
			if(_suites[name].run_test())
			{
				++success;
			}
		}
		std::cout<<std::endl<<"Total : "<<total
			<<", Success: "<<success
			<<", Failed: "<<total - success<<std::endl;
		return success == total;
	}
}
