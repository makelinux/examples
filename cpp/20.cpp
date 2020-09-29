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

#if __has_include (<bit>)
#include <bit>
#endif
#include <vector>
#include <cmath>
#include <cassert>
#include <vector>
#include <map>
#include <memory>
#include <thread>
#include <sstream>
#include <experimental/array>
#if __has_include (<concepts>)
#include <concepts>
#endif

using namespace std;

/**
 @defgroup lang20 Language
 https://en.cppreference.com/w/cpp/language
 @{
 */

#if __cpp_lib_three_way_comparison
static_assert(1 <=> 2 < 0 );
static_assert(2 <=> 1 > 0 );
static_assert(1 <=> 1 == 0 );
#else
#pragma message("undefined __cpp_lib_three_way_comparison")
#endif

#if __cpp_char8_t
/// https://en.cppreference.com/w/cpp/keyword/char8_t
char8_t char8;
#endif

/// https://en.cppreference.com/w/cpp/container/array/to_array

auto to_array_demo = experimental::to_array("foo");
static_assert(to_array_demo.size() == 4);

void init_20()
{
	struct point { int x, y; };
	struct line { point a, b; };

	// https://en.cppreference.com/w/cpp/language/aggregate_initialization

#if __cplusplus > 201707
	point p1 = { .x = 1 };
	assert(p1.x == 1);
	assert(!p1.y);

	point p2 { {} , 2 };
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

void types_20()
{
#if __cpp_lib_bit_cast
	cout << typeid(bit_cast<double>(0));
#endif
}

void dynamic_memory_20()
{
	/// Shared array
	/// https://en.cppreference.com/w/cpp/memory/shared_ptr/make_shared
	auto a = make_shared<int[10]>();
	static_assert(is_same_v<decltype(a.get()), int*>);

	/// https://en.cppreference.com/w/cpp/container/map/contains
	map<int, int> m = {{2,3}};
#if __cplusplus > 201707
	assert(m.contains(2));
#endif
#if __cpp_lib_erase_if
	/// [erase_if](https://en.cppreference.com/w/cpp/container/map/erase_if)
	vector<int> v = {11, 12, 13};
	assert(erase_if(v, [](int a) {return a >= 13;}) == 1);
	assert(v.size() == 2);
#endif
}

namespace lambda {

#if __cpp_template_template_args
/// Lambda capture of parameter pack
template <typename ... Args>
auto make_lambda_with_parameter_pack_capture(Args&& ... args)
{
	// parameter pack capture:
	return [... args = forward<Args>(args)] {
		return (... + args);
	};
}
#endif

void lambda_20()
{
#if __cplusplus >= 201709
	// generic lambda, operator() is a template with two parameters
	auto glambda = []<class T>(T a, auto&& b) { return a < b; };
	assert(glambda(1,2));
	// generic lambda, operator() is a template with one parameter pack
	auto f = []<typename ...Ts>(Ts&& ...ts) {
		return 1;
	};
	assert(f(1,2,3));

	struct point { int x, y; };
	auto point_lambda = []<class T=point>(T&& var) {};
	point_lambda({1, 2});

	#if __cpp_template_template_args
	assert(make_lambda_with_parameter_pack_capture(1,2,3)() ==  6);
	#endif
#endif
}

}
using namespace lambda;


/// @} lang20

/**
 @defgroup templ20 Template

 https://en.cppreference.com/w/cpp/language/templates

 @{
*/

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

// Using [requires](https://en.cppreference.com/w/cpp/keyword/requires)

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
is_signed_v<T> || (is_unsigned_v<T> && ! is_void_v<void>) // constraint expression
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

#if __cpp_concepts < 201907

/**
  In Technical Specification a concept can be defined as function
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
  defining concept as function with requires-expression
 */

template <typename T> concept bool integral_func_req_ct()
	requires requires () { is_integral_v<T>; }
	{ return true; }

template <integral_func_req_ct T> constexpr T _inc4(T a) { return a + 1; }

static_assert(_inc4(1) == 2);

template<typename T> concept compound_requirement =
requires(T x) {{x + 1} -> int;};

#endif

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




/// @}

/// @}
#else
#pragma message("undefined __cpp_concepts")
#endif


#if __cpp_lib_ranges

#include <ranges>

/// [ranges](https://en.cppreference.com/w/cpp/ranges)

struct ranges_20 {
	ranges_20() {
		auto data = {0, 1, 2, 3};
		/// [reverse_view](https://en.cppreference.com/w/cpp/ranges/reverse_view)
		ranges::reverse_view rv {data};
		auto r = data | views::reverse;
		// r is kind of transform_view
		vector result(r.begin(), r.end());
		assert(vector(rv.begin(), rv.end()) == result);
		assert((result == vector{3, 2, 1, 0}));
	}
} ranges_20;

#else
#pragma message("undefined __cpp_lib_ranges")
#endif



/**
 @defgroup other20 Other
 @{

  TODO:

  https://en.cppreference.com/w/cpp/language/range-for

  https://en.cppreference.com/w/cpp/language/coroutines

  https://en.cppreference.com/w/cpp/language/constinit

 */

/// @}

#include <experimental/source_location>

/// [source_location](https://en.cppreference.com/w/cpp/utility/source_location)

struct location_20 {
	location_20() {
		auto l = experimental::source_location::current();
		basic_stringstream<char> buff;
		buff << l.file_name() << ":" << l.line() << ":" << l.column() << l.function_name();
		assert(buff.str().length());
	}
} location_20;

int main()
{
	init_20();
	types_20();
	dynamic_memory_20();
	lambda_20();
#if __cpp_lib_jthread
	jthread t([]{ });
#endif
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
