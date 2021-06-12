/**
 @file
 @brief C++20
 @defgroup CPP20 C++20 examples

 [C++20](https://en.wikipedia.org/wiki/C++20)

 [Modern Cpp20 features](https://github.com/AnthonyCalandra/modern-cpp-features/blob/master/CPP20.md)

 https://en.cppreference.com/w/cpp/20

 @{
*/

static_assert(__cplusplus >= 201707);

#include <functional>
#include <algorithm>
#if __has_include (<bit>)
#include <bit>
#endif
#include <vector>
#include <cmath>
#include <cassert>
#include <map>
#include <memory>
#include <thread>
#if __cpp_impl_coroutine
#include <coroutine>
#endif
#include <sstream>
#include <experimental/array>
#if __has_include (<concepts>)
#include <concepts>
#endif

using namespace std;

/**
 @defgroup lang20 Language
 [language](https://en.cppreference.com/w/cpp/language)
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
/// [char8_t](https://en.cppreference.com/w/cpp/keyword/char8_t)
char8_t char8;
#endif

/// [to_array](https://en.cppreference.com/w/cpp/container/array/to_array)

auto to_array_demo = experimental::to_array("foo");
static_assert(to_array_demo.size() == 4);

void init_20()
{
	struct point { int x, y; };
	struct line { point a, b; };

	// [aggregate_initialization](https://en.cppreference.com/w/cpp/language/aggregate_initialization)

#if __cplusplus > 201707
	point p1 = { .x = 1 };
	assert(p1.x == 1);
	assert(!p1.y);

	point p2 { {} , 2 };
	assert(p2.y == 2);
	assert(!p2.x);
#endif
#if __cpp_aggregate_paren_init >= 201902
	int a[] (0, 1, 2);
	assert(a[2] == 2);
	line l2 = { 1, 2 };
	assert(l2.a.x == 1);
	assert(l2.a.y == 2);
#endif
	line l1 = { };
	assert(!l1.a.x);
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
	/// [make_shared](https://en.cppreference.com/w/cpp/memory/shared_ptr/make_shared)
	auto a = make_shared<int[10]>();
	static_assert(is_same_v<decltype(a.get()), int*>);

	/// [contains](https://en.cppreference.com/w/cpp/container/map/contains)
	map<int, int> m = {{2,3}};
#if __cplusplus > 201707 && __GNUG__ > 8
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

#if __cpp_template_template_args && __GNUG__ > 8
/// [Lambda capture of parameter pack](https://en.cppreference.com/w/cpp/language/lambda#Lambda_capture)
template <typename ... Args>
auto make_lambda_with_parameter_pack_capture(Args&& ... args)
{
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

	#if __cpp_template_template_args && __GNUG__ > 8
	assert(make_lambda_with_parameter_pack_capture(1,2,3)() ==  6);
	#endif
#endif
}

}
using namespace lambda;


/// @} lang20

/**
 @defgroup templ20 Template

 [templates](https://en.cppreference.com/w/cpp/language/templates)

 @{
*/

#if __cpp_concepts
/**
 @}

 @defgroup conc20 Concepts

 https://en.wikipedia.org/wiki/Concepts_(C++)
 [constraints](https://en.cppreference.com/w/cpp/language/constraints)
 [concepts](https://en.cppreference.com/w/cpp/header/concepts)

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


/**
 @defgroup conc_def_20 Concept definitions
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
  [Compound_Requirements](https://en.cppreference.com/w/cpp/language/constraints#Compound_Requirements)
  [convertible_to](https://en.cppreference.com/w/cpp/concepts/convertible_to)
 */

template<typename T> concept compound_requirements =
requires(T x) {
	{x + 1} -> convertible_to<bool>;
	{x * 2} -> same_as<int>;
};



/// @}

/// @}
#else
#pragma message("undefined __cpp_concepts")
#endif

/**
 @defgroup cor20 Coroutines
 @{

	[coroutine](https://en.cppreference.com/w/cpp/coroutine)

	[coroutines](https://en.cppreference.com/w/cpp/language/coroutines)

 */

#if __cpp_impl_coroutine
auto switch_to_new_thread(jthread& out)
{
	struct awaitable {
		jthread* p_out;
		bool await_ready() { return false; }
		void await_suspend(coroutine_handle<> h) {
			jthread& out = *p_out;
			if (out.joinable())
				throw runtime_error("Output jthread parameter not empty");
			out = jthread([h] { h.resume(); });
		}
		void await_resume() {}
	};
	return awaitable{&out};
}

struct task {
	struct promise_type {
		struct task get_return_object() { return {}; }
		suspend_never initial_suspend() { return {}; }
		suspend_never final_suspend() noexcept { return {}; }
		void return_void() {}
		void unhandled_exception() {}
	};
};

struct task resuming_on_new_thread(jthread& out)
{
	auto starting_tid = this_thread::get_id();
	// suspends coroutine
	co_await switch_to_new_thread(out); ///< [co_await](https://en.cppreference.com/w/cpp/keyword/co_await)
	// awaiter is destroyed here
	assert(this_thread::get_id() != starting_tid);
}

void coroutine_demo()
{
	jthread out;
	resuming_on_new_thread(out);
}
#else
void coroutine_demo() {}
#pragma message("undefined __cpp_impl_coroutine")
#endif
/// @}

/**
 @defgroup other20 Other
 @{

  TODO:

  [range-for](https://en.cppreference.com/w/cpp/language/range-for)

 */

#if __cpp_lib_ranges

#include <ranges>

/// [ranges](https://en.cppreference.com/w/cpp/ranges)
/// [range algorithms](https://en.cppreference.com/w/cpp/algorithm/ranges)
/// [sort](https://en.cppreference.com/w/cpp/algorithm/ranges/sort)
/// [distance](https://en.cppreference.com/w/cpp/iterator/ranges/distance)

void sort_20()
{
	vector<int> v = {5, 7, 4, 2, 8, 6, 1, 9, 1, 3};
	ranges::sort(v);
	assert(v.front() <= v.back());
	assert(ranges::distance(v));
	assert(!ranges::distance(v.begin(), v.begin()));
}

void ranges_20()
{
	auto data = {0, 1, 2, 3};
	/// [reverse_view](https://en.cppreference.com/w/cpp/ranges/reverse_view)
#if __clang_major__ != 10
	ranges::reverse_view rv {data};
	auto r = data | views::reverse;
	// r is kind of transform_view
	vector result(r.begin(), r.end());
	assert(vector(rv.begin(), rv.end()) == result);
	assert((result == vector{3, 2, 1, 0}));
#endif
	auto [min, max] = ranges::minmax({3, 2, 1});
	auto a = ranges::minmax({3, 2, 1});
	assert(min == 1);
	assert(max == 3);
	assert(!in_range<std::size_t>(-1));
}

#else
#pragma message("undefined __cpp_lib_ranges")
#endif

#include <experimental/source_location>

/// [source_location](https://en.cppreference.com/w/cpp/utility/source_location)

void location_20()
{
	auto l = experimental::source_location::current();
	basic_stringstream<char> buff;
	buff << l.file_name() << ":" << l.line() << ":" << l.column() << l.function_name();
	assert(buff.str().length());
}

/**
  [functional](https://en.cppreference.com/w/cpp/header/functional)
  [bind_front](https://en.cppreference.com/w/cpp/utility/functional/bind_front)
 */

void functional_20()
{
	auto constexpr plus_one = std::bind_front(std::plus<int>(), 1);
	static_assert(plus_one(2) == 3);
}

/// @} other20

int main()
{
	init_20();
	types_20();
	dynamic_memory_20();
	lambda_20();
#if __cpp_lib_jthread
	jthread t([]{ });
#endif
	coroutine_demo();
	sort_20();
	ranges_20();
	location_20();
	functional_20();
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
