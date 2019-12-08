#include <utility>
#include <iostream>
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

/*
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
   */

/// @}

int main(void)
{
	cout << __cplusplus << endl;
	auto x = deduced_return_type(1);
	int& y = deduced_return_type_lambda(x); // reference to `x`
	assert(&y == &x);
	assert(y == 1);

	return 0;
}
/// @}
