#include <utility>
#include <iostream>
#include <cassert>
#include <functional>
#include <algorithm>
#include <array>

using namespace std;

/**
 @file
 @brief C++11
 @defgroup CPP11 C++11 examples

 https://en.wikipedia.org/wiki/C++11

 https://github.com/AnthonyCalandra/modern-cpp-features/blob/master/CPP11.md

 @{

 @defgroup lang11 Language
 @{
	https://en.cppreference.com/w/cpp/language/move_constructor

	https://en.cppreference.com/w/cpp/language/move_assignment

	https://en.cppreference.com/w/cpp/language/data_members#Member_initialization

	https://en.cppreference.com/w/cpp/language/override

	https://en.cppreference.com/w/cpp/language/final

	https://en.cppreference.com/w/cpp/language/reference &&

	https://en.cppreference.com/w/cpp/language/attributes

	https://en.cppreference.com/w/cpp/language/nullptr

	https://en.cppreference.com/w/cpp/language/string_literal

	https://en.cppreference.com/w/cpp/language/character_literal

	https://en.cppreference.com/w/cpp/language/user_literal

	https://en.cppreference.com/w/cpp/language/aggregate_initialization

	https://en.cppreference.com/w/cpp/language/range-for

	https://en.cppreference.com/w/cpp/language/decltype

	https://en.cppreference.com/w/cpp/language/auto

	https://en.cppreference.com/w/cpp/language/constexpr

	https://en.cppreference.com/w/cpp/language/parameter_pack

 */

/**
 Trailing return type

 https://en.cppreference.com/w/cpp/language/function

 https://www.ibm.com/support/knowledgecenter/en/ssw_ibm_i_73/rzarg/trailing_return.htm

*/

// int before(int a) { return a; }
auto trailing_return_type(int a) -> int
{
	return a;
}

/**
 @}
 @defgroup lambda11 Lambda
 https://en.cppreference.com/w/cpp/language/lambda
 https://www.geeksforgeeks.org/lambda-expression-in-c/
 @{
 */

static void lambda_basics(void)
{
	int i = 1;

	auto annotated_named_lambda_expression =  // optional name
		[ ] // capture
		( ) // optional list of arguments
		{ }; // body

	// Primitive named lambdas are just like closure functions:
	// https://en.wikipedia.org/wiki/Closure_(computer_programming)

	// declaration like a function:
	// void closure() { };
	auto closure = [] { };

	closure();

	// with arguments
	auto pass = [] (int a) -> int { return a; };
	assert(pass(5) == 5);

	// lambda captures external value
	auto get_i = [=] () -> int { return i; };
	assert(get_i() == 1);

	// lambda captures external variable by reference
	// with omitted arguments and return type
	auto inc_get = [&] { return ++i; };
	assert(inc_get() == 2);
	assert(inc_get() == 3);

	// annotated expanded empty inline lambda call:
	[ ] // capture
		( ) // optional list of arguments
			-> void // optional return value
			{ } // body
	( ); // call with arguments

	// annotated expanded sample inline lambda call:
	[i] // capture
		(int a) // optional list of arguments
			-> int // optional return value
			{ return i + a; } // body
	(1); // call with argument

	// inline lambda which is called in place
	// https://en.wikipedia.org/wiki/Anonymous_function

	// assert((1 + 1) == 2);
	assert([](int a) { return a + 1; }(1) == 2);

	// Actually calling lambda inline is useless
	// and is provided only for demonstration.
}

static int glob;

static void lambda_capture(void)
{
	// read only
	int i = 2;
	assert([=]{return i; }() == 2);

	// read and write access
	[&](int a){i = a;}(3);
	assert(i == 3);

	// explicit r/o and r/w
	int j;
	[i, &j](){ j = i; }();
	assert(j == i);

	// r/o by default
	i++;
	[=, &j](){ j = i; }();
	assert(j == i);

	// r/w by default
	i++;
	[&, i](){ j = i; }();
	assert(j == i);

	// can access globals anyway
	auto inc_global = [] () -> int { return ++glob; };
	assert(inc_global() == 1);
	assert(inc_global() == 2);
}

/// More complex useful examples

// int use_lambda(int a; int (func*)(int))
static int use_lambda(int a, function<int(int)> f)
{
	return f(a);
}

/// https://en.cppreference.com/w/cpp/utility/functional/function
static function<int(int)> g_f;

static void set_lambda(function<int(int)> f)
{
	g_f = f;
}

static int call_lambda(int a)
{
	return g_f(a);
}

static void lambda_complex(void)
{
	auto increment = [] (int a) -> int { return a + 1; };
	assert(increment(5) == 6);

	// named lambda as argument
	assert(use_lambda(2, increment) == 3);
	set_lambda(increment);
	assert(call_lambda(3) == 4);

	// inline lambda as argument
	assert(use_lambda(1, [](int a) {return a + 1;}) == 2);
}

void func_11()
{
	class functor {
		int y = 1;
		public:
		int operator()(int a) const {
			return a + y;
		}
	};
	functor ft;
	assert(ft(1) == 2);

	// https://en.cppreference.com/w/cpp/utility/functional/function
	function<int(int)> ft2 = ft;
	assert(ft(2) == 3);
	return;

	// https://en.cppreference.com/w/cpp/utility/functional/bind
	auto binded = std::bind(ft2, 3);
	assert(binded() == 5);
}

void sort_11()
{
	std::array<int, 10> s = {5, 7, 4, 2, 8, 6, 1, 9, 0, 3};
	std::sort(s.begin(), s.end(),
		  // sort using a lambda expression
		  [](int a, int b)
		  { return a > b; }
		 );
}

/// @}

int main(void)
{
	cout << __cplusplus << endl;
	auto r = trailing_return_type(1);
	lambda_basics();
	lambda_capture();
	lambda_complex();
	func_11();
	sort_11();
	return 0;
}
/// @}

extern "C" {
void main3()
{
	struct ab {
		int a;
		int b;
	};


	// Point2D point2D = {.x = 1, .y = 2};
	// Point2D point2D = {.x , };
	ab ab {1, 2};

	// Point3D point3D {.x = 1, .y = 2, .z = 2};
}
}
