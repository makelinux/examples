#include <utility>
#include <tuple>
#include <unordered_map>
#include <variant>
#include <string>
#include <cassert>
#include <algorithm>
#include <map>
#include <set>
#include <iostream>

using namespace std;

/**
 @mainpage
 @ref CPP11

 @ref CPP17

 @file
 @brief C++17
 @defgroup CPP17 C++17 features
 @{
 @defgroup templ17 Template
 https://en.cppreference.com/w/cpp/language/lambda
 https://docs.microsoft.com/en-us/cpp/cpp/lambda-expressions-constexpr
 @{
 @defgroup class_template_argument_deduction Class template argument deduction
 https://en.cppreference.com/w/cpp/language/class_template_argument_deduction
 @{
 */

/// @brief pair<int, double> p(1, 2.3);
pair p(1, 2.3);

/// @brief auto t = make_tuple(4, 3, 2.5);
tuple t(3, 4, 5);

/// @brief less<void> l;
less l;

template <typename T = float>
struct arg_deduction {
	T val;
	arg_deduction() : val() {}
	arg_deduction(T val) : val(val) {}
};

/// @brief arg_deduction<int>
arg_deduction c1 {1};

/// @brief arg_deduction<float>
arg_deduction c2;

/**
 @}
 @{
 @defgroup template_parameters Template parameters
 https://en.cppreference.com/w/cpp/language/template_parameters
 @{
 */

template<auto n> struct B { /* ... */ };

B<5> b1; // OK: non-type template parameter type is int

B<'a'> b2;

// Error:
// B<2.5> b3;

tuple<int, int> foo_tuple()
{
	// return make_tuple(1, -1);
	return {1, -1};
}

template <auto... seq>
struct my_integer_sequence {
};

/// @brief auto seq = integer_sequence<int, 0, 1, 2>();
auto seq = my_integer_sequence<0, 1, 2>();

/**
 @}
 @}
 @}
 @defgroup lambda Lambda

 @{
 @defgroup constexpr_lambda Constexpr lambda
 https://en.cppreference.com/w/cpp/language/lambda
 https://docs.microsoft.com/en-us/cpp/cpp/lambda-expressions-constexpr

 @{
 */

// explicit constexpr
auto identity = [](int n) constexpr { return n; };
static_assert(identity(1) == 1);

// lambda with auto argument is actually a template

// implicit auto constexpr:

auto can_be_constexpr1 = [](auto a) { return a; };
auto can_be_constexpr2 = [](int(*fp)(int), auto a) { return fp(a); };

static_assert(can_be_constexpr2(can_be_constexpr1, 3) == 3);

// error: non-constant condition for static assertion
// static int i=0;
// static_assert(can_be_constexpr2(can_be_constexpr1, i) == 0);

auto non_const = [](auto a) {static int s; return a; };

// error: no specialization can be constexpr because of s
// static_assert(can_be_constexpr(non_const, 3)==3);

constexpr int const_inc(int n)
{
	return [n] { return n + 1; }();
}

constexpr int(*inc)(int) = const_inc;
static_assert(const_inc(1) == 2);

/**
 @}
 @defgroup lcbv Lambda capture this by value
 https://en.cppreference.com/w/cpp/language/lambda#Lambda_capture
 @{
 */

void capture_this_by_value()
{
	struct capture_value_o {
		int value {1};
		auto get_value_copy() {
			return [*this] { return value; };
		}
	};

	capture_value_o mo;
	auto val = mo.get_value_copy();
	mo.value = 2;
	assert(val() == 1);
}

void lambda_examples()
{
	assert(can_be_constexpr1(2) == 2);
	int i = 3;
	assert(can_be_constexpr2(can_be_constexpr1, 3) == 3);
	non_const(1);
	capture_this_by_value();
}

/// @}

/**
 @}
 @defgroup folding Folding
 @{
 */

template<typename... Args>
bool folding_and(Args... args) { return (true && ... && args); }

void folding_demo()
{
	folding_and(true, false, true); // == flase
}

template<typename... Args>
auto folding_sum(Args... args) { return (... + args); }

void test2()
{
	folding_sum(1.0, 2.0f, 3); // == 6.0
}

/**
 @}
 @defgroup iv Inline variables
 https://en.cppreference.com/w/cpp/language/inline
 @{
 */

struct S { int x; };

inline S x1 = S{321};

S x2 = S{123};

/**
 @}
 @defgroup nn Nested namespaces
 @{
 */

namespace A::B::C
{
int i;
}

/**
 @}
 @defgroup sb Structured bindings
 https://en.cppreference.com/w/cpp/language/structured_binding
 @{
 */

void structured_bindings()
{

	int a[2] = {1, 2};

	auto [a0, a1] = a;
	// a0_ref = &a; a0_ref = &a;
	auto& [a0_ref, a1_ref] = a;

	float x{};
	char y{};
	int z{};

	unordered_map<string, int> mapping {
		{"a", 1},
		{"b", 2},
		{"c", 3},
	};

	for (const auto& [key, value] : mapping) {
		// Do something with key and value
	}
	//tuple<float&,char&&,int> tpl(x,move(y),z);
	//const auto& [a,b,c] = tpl;
}

/**
 @}
 @defgroup iscs Variable declaration in conditional
 https://en.cppreference.com/w/cpp/language/if
 https://en.cppreference.com/w/cpp/language/switch
 @{
 */

void conditional_with_init()
{
	if (auto a = true);

	switch (int a = 10) {
	}
}

template<class T> struct dependent_false : false_type {};

/**
 @}
 @defgroup attr New attributes 'fallthrough', 'nodiscard' and 'maybe_unused'
 https://en.cppreference.com/w/cpp/language/attributes/fallthrough
 https://en.cppreference.com/w/cpp/language/attributes/nodiscard
 https://en.cppreference.com/w/cpp/language/attributes/maybe_unused
 @{
 */

// Will warn if return of foo() is ignored
[[nodiscard]] int foo() {return 0;}
void test_attr()
{
	int a {1};
	switch (a) {
	// Indicates that falling through on case 1 is intentional
	case 1:
		[[fallthrough]]
	case 2:
		// Indicates that b might be unused, such as on production builds
		[[maybe_unused]] int b = foo();
		assert(b > 0);
		break;
	}
}

void test_variant()
{
	variant<int, float> v, w;
	v = 12; // v contains int
	int i = get<int>(v);
	w = get<int>(v);
	w = get<0>(v); // same effect as the previous line
	w = v; // same effect as the previous line

	// get<double>(v); // error: no double in [int, float]
	// get<3>(v); // error: valid index values are 0 and 1

	try {
		get<float>(w); // w contains int, not float: will throw
	} catch (const bad_variant_access&) {}

	using namespace literals;

	variant<string> x("abc");
	// converting constructors work when unambiguous
	x = "def"; // converting assignment also works when unambiguous

	variant<string, void const*> y("abc");
	// casts to void const * when passed a char const *
	assert(holds_alternative<void const*>(y)); // succeeds
	y = "xyz"s;
	assert(holds_alternative<string>(y)); // succeeds
}

/**
 @}
 @defgroup constif Compile time constexpr if
 https://en.cppreference.com/w/cpp/language/if
 @{
 */
void constif()
{
	if constexpr(true)
		printf("1\n");
}

/**
 @}
 @defgroup lit Character literal
 https://en.cppreference.com/w/cpp/language/character_literal
 @{
 */

char char_u8 = u8'x';

/**
 @}
 @defgroup enum Direct list initialization of enums
 https://en.cppreference.com/w/cpp/language/character_literal
 https://en.cppreference.com/w/cpp/language/enum
 @{
 */
enum byte : unsigned char {};
byte b { 123 };

/**
 @}
 @defgroup more More features
 @{
 */

void map_demo()
{
	/// @brief https://en.cppreference.com/w/cpp/container/map/extract
	map<int, string> m{{1, "mango"}, {2, "papaya"}, {3, "guava"}};
	auto nh = m.extract(2);
	nh.key() = 4;
	/// @brief https://en.cppreference.com/w/cpp/container/map/insert
	m.insert(move(nh));
	// m == {{1, "mango"}, {3, "guava"}, {4, "papaya"}}

	/// @brief https://en.cppreference.com/w/cpp/container/map/merge
	set<int> src {1, 3, 5};
	set<int> dst {2, 4, 5};
	dst.merge(src);
	// src == { 5 }
	// dst == { 1, 2, 3, 4, 5 }
}

int x = 50;
/// @brief x = x < 100 ? 100 : x > 200 ? 200 : x;
int x_clamped = clamp(x, 100, 200);
int main()
{
	folding_demo();
	lambda_examples();
}

/**
 @}
 @}
 */
