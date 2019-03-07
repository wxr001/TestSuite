CXXFLAGS = -Wall -Wextra -Weffc++ -Wold-style-cast  -Wnoexcept -Woverloaded-virtual -Wunused -Wformat -Wuninitialized -Wunknown-pragmas -Wuseless-cast -O3 -std=c++17
.PHONY : all
.PHONY : clean
.PHONY : check
all : TestSuite.o STSL
	ar crv libSTSL.a TestSuite.o
clean :
	rm -rf *.o
	rm -rf src/*.o
	rm -rf tests/*.o
	rm libSTSL.a
check : all test_single test_assert
	tests/run_tests.sh
test_single : test_single.o
	g++ test_single.o $(CXXFLAGS) -L. -lSTSL -o tests/$@
test_assert : test_assert.o
	g++ test_assert.o $(CXXFLAGS) -L. -lSTSL -o tests/$@
TestSuite.o : src/TestSuite.cpp STSL
	g++ src/TestSuite.cpp $(CXXFLAGS) -c -o $@
test_single.o : tests/test_single.cpp STSL
	g++ tests/test_single.cpp $(CXXFLAGS) -c -o $@
test_assert.o : tests/test_assert.cpp STSL
	g++ tests/test_assert.cpp $(CXXFLAGS) -c -o $@
STSL : include/TestSuite.hpp
