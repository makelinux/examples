/**
 @file
 @brief C++20
 @defgroup CPP20 C++20 examples

 https://en.wikipedia.org/wiki/C++20

 https://github.com/AnthonyCalandra/modern-cpp-features/blob/master/CPP20.md

 https://en.cppreference.com/w/cpp/20

 @{
*/

static_assert(__cplusplus >= 201707);

#include <vector>
#include <cmath>
#include <cassert>
#include <vector>
#if __has_include (<concepts>)
#include <concepts>
#endif

using namespace std;

/**
  https://en.cppreference.com/w/cpp/ranges
  https://en.cppreference.com/w/cpp/utility/source_location
  https://en.cppreference.com/w/cpp/language/coroutines
  */

void init_20()
{
	struct point { int x, y; };
	struct line { point a, b; };

	// https://en.cppreference.com/w/cpp/language/aggregate_initialization

#if __cplusplus > 201707
	point p1 = { .x = { 1 } };
	assert(p1.x == 1);
	assert(!p1.y);

	point p2 { .y { 2 } };
	assert(p2.y == 2);
	assert(!p2.x);
#endif

	line l1 = { };
	assert(!l1.a.x);
	line l2 = { 1, 2 };
	assert(l2.a.x == 1);
	assert(l2.a.y == 2);

	line l3 = { 1, 2, 3, 4 };
	assert(l3.b.x == 3);
	assert(l3.b.y == 4);
}

#if __cpp_concepts
/**
 @}

 @defgroup conc20 Concepts

 https://en.wikipedia.org/wiki/Concepts_(C++)
 https://en.cppreference.com/w/cpp/language/constraints
 https://en.cppreference.com/w/cpp/header/concepts

 @{
*/

/**
 @defgroup req20 'Requires' clause and expression
 @{
*/

// Using 'requires':
// https://en.cppreference.com/w/cpp/keyword/requires

template <typename T> requires is_integral_v<T> T constexpr requires_demo(T a) { return a + 1; }

static_assert(requires_demo(1) == 2);

/**
  requires-clause can be after function declaration and supports template overloading
 */

template <typename T> auto constexpr requires_demo(T && a) requires is_same_v<T, double> { return 2; }
static_assert(requires_demo(0.1) == 2);

// Annotated example of complex requirement
template <class T>
requires // requires-clause
is_signed_v<T> || is_unsigned_v<T> && ! is_void_v<void> // constraint expression
void complex_requirement_demo() { }

/// Annotated example of requires-expression

template < class T >
requires  // requires-clause
requires() // requires-expression
{ true;} // unevaluated requirements sequence
void requires_expression_demo() { }

template <class T> requires requires(T a) { a / 0; } auto constexpr what(T a) { return 1; }
static_assert(what(1) == 1);

template <class T> requires requires(T a) { a[0]; } auto constexpr what(T a) { return 2; }
static_assert(what("2") == 2);

/// @}

/**
  a concept can be defined as function, but not only
 */

template <typename T> concept bool integral_ct() { return is_integral_v<T>; }

template <integral_ct T> constexpr T _inc3(T a) { return a + 1; }

static_assert(_inc3(1) == 2);

// concept can replace type

template <integral_ct T> constexpr T _inc1(T a) { return a + 1; }

static_assert(_inc1<int>(1) == 2);

// can be used in generic function
constexpr auto generic_function_with_integral_concept(integral_ct v) { return v + 1; }
static_assert(generic_function_with_integral_concept(1) == 2);

integral_ct integral_var = 1; // variable defined with concept

/**
 @defgroup conc_alt20 Alternative forms of concept definition
 @{
 */

/// trivial concepts as assignment
template <typename T> concept truism = true;

#if !__cpp_lib_concepts

/// short concept definition from a constraint directly
template <class T> concept integral = is_integral_v<T>;

#endif

/**
  defining concept with requires-expression
 */

template <class T> concept integral_req_ct = requires (T a) { is_integral_v<T>; };

template <integral_req_ct T> constexpr T _inc2(T a) { return a + 1; }

static_assert(_inc2(1) == 2);

/**
  defining concept as function with requires-expression
 */

template <typename T> concept bool integral_func_req_ct()
	requires requires () { is_integral_v<T>; }
	{ return true; }

template <integral_func_req_ct T> constexpr T _inc4(T a) { return a + 1; }

static_assert(_inc4(1) == 2);

/// @}

/// @}
#else
#pragma message("undefined __cpp_concepts")
#endif

namespace lambda {

void lambda_20()
{
	// generic lambda, operator() is a template with two parameters
	auto glambda = []<class T>(T a, auto&& b) { return a < b; };
	assert(glambda(1,2));

	// generic lambda, operator() is a template with one parameter pack
	auto f = []<typename ...Ts>(Ts&& ...ts) {
		return 1;
	};
	assert(f(1,2,3));
}

}
using namespace lambda;

/// @}
int main()
{
	init_20();
	lambda_20();
}
/// @}

/**
 @mainpage

 @ref CPP20

 @ref CPP17

 @ref CPP14

 @ref CPP11

 @ref CPP03

*/
