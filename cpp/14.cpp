#include <utility>
#include <iostream>
#include <memory>
#include <chrono>
#include <tuple>
#include <string>
#include <cassert>

using namespace std;

/**
 @file
 @brief C++14
 @defgroup CPP14 C++14 examples

 https://en.wikipedia.org/wiki/C++14

 https://isocpp.org/wiki/faq/cpp14-language

 https://github.com/AnthonyCalandra/modern-cpp-features/blob/master/CPP14.md

 @{
 @defgroup lambda14 Lambda
 https://en.cppreference.com/w/cpp/language/lambda
 @{
 */
static void lambda_demo()
{
	// Generic lambdas
	// auto before_generic_lambda = [](int x) { return x; };
	auto generic_lambda = [](auto x) { return x; };

	auto universal_size = [](const auto& m) { return m.size(); };

	auto capture_initializers = [value = 1] { return value; };

	unique_ptr<int> ptr(new int(10));
	auto capture_by_move = [value = std::move(ptr)] { return *value; };
}
/**
 @}
 @defgroup ded14 Deduction
 @{
 */

// template <typename T> T before_deduced_return_type(int a) { return a; }
auto deduced_return_type(int a)
{
	return a;
}

// template <typename T> T& before_deduced_return_type_template(T& a) { return a; }
template <typename T> auto& deduced_return_type_template(T& t)
{
	return t;
}

// Returns a reference to a deduced type.
auto deduced_return_type_lambda = [](auto& x) -> auto& {
	return deduced_return_type_template(x);
};

/**
 @}
 @defgroup other14 Other
 @{
	https://en.cppreference.com/w/cpp/language/variable_template
	https://en.cppreference.com/w/cpp/language/constexpr
	https://en.cppreference.com/w/cpp/language/integer_literal
	https://en.cppreference.com/w/cpp/language/function // decltype(auto)
	https://en.cppreference.com/w/cpp/language/aggregate_initialization
	https://en.cppreference.com/w/cpp/language/lambda

	https://en.cppreference.com/w/cpp/memory/unique_ptr/make_unique
	https://en.cppreference.com/w/cpp/thread/shared_timed_mutex
	https://en.cppreference.com/w/cpp/thread/shared_lock
	https://en.cppreference.com/w/cpp/utility/integer_sequence
	https://en.cppreference.com/w/cpp/utility/exchange
	https://en.cppreference.com/w/cpp/io/manip/quoted

	// [[deprecated]]
 */

/// Binary literals, digit separators

auto binary_literal = 0b0100'1100'0110;

auto integer_literal = 1'000'000;

auto floating_point_literal = 0.000'015'3;

/// Standard user-defined literals

auto str = "hello world"s; // auto deduces string
auto dur = 60s;            // auto deduces chrono::seconds

/// Tuple addressing via type

static void tuple_demo()
{
	tuple<string, string, int> tuple_by_type("foo", "bar", 7);

	int i = get<int>(tuple_by_type);
	assert(i == 7);

	int j = get<2>(tuple_by_type);
	assert(j == 7);
}

/// Template variables
namespace template_variables {

template<typename T>
constexpr T pi = T(3.141592653589793238462643383);

// Usual specialization rules apply:
template<>
constexpr const char* pi<const char*> = "pi";

static void demo()
{

	assert(pi<int> == 3);
	assert(string(pi<const char*>) == "pi");
}

}
/// @}

int main(void)
{
	cout << __cplusplus << endl;
	auto x = deduced_return_type(1);
	int& y = deduced_return_type_lambda(x); // reference to `x`
	assert(&y == &x);
	assert(y == 1);
	tuple_demo();
	template_variables::demo();

	return 0;
}
/// @}
