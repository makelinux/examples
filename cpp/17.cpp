/**
 @file
 @brief C++17
 @defgroup CPP17 C++17 examples

 https://en.wikipedia.org/wiki/C++17

 https://github.com/AnthonyCalandra/modern-cpp-features/blob/master/CPP17.md

 https://en.cppreference.com/w/cpp/language/history/17

 https://en.cppreference.com/w/cpp/language/range-for

 @{
*/

static_assert(__cplusplus == 201703);

#include <utility>
#include <tuple>
#include <unordered_map>
#include <variant>
#include <string>
#include <string_view>
#include <cassert>
#include <algorithm>
#include <map>
#include <set>
#include <iostream>
#include <vector>
#include <memory>
#include <functional> //11
#include <utility>
#include <valarray>
//#include <execution>

using namespace std;

void references_17()
{
	static_assert(std::is_reference_v<int&>);

	// L-value:
	static_assert(std::is_lvalue_reference_v<int&>);

	// R-value
	static_assert(std::is_rvalue_reference_v<int&&>);
}

/**
 @defgroup templ17 Template

 https://en.cppreference.com/w/cpp/language/templates

 @{
*/

#if __cpp_deduction_guides

/**
 @defgroup template_argument_deduction Template argument deduction

 https://en.cppreference.com/w/cpp/language/template_argument_deduction

 https://en.cppreference.com/w/cpp/language/class_template_argument_deduction

 @{
 */

/// @brief pair<int, double> p(1, 2.3);
constexpr pair p(1, 2.3);
static_assert(p.second == 2.3);

/// @brief auto t = make_tuple(4, 3, 2.5);
constexpr tuple t(4, 2, 2.5);

static_assert(std::get<2>(t) == 2.5);

template <typename T = float>
struct arg_deduction {
	T val;
	arg_deduction() : val() {}
	arg_deduction(T val) : val(val) {}
};

/// @brief before_arg_deduction<int>
arg_deduction c1 {1};

#if __cpp_deduction_guides > 201611

/// @brief before_arg_deduction<float>
arg_deduction c2;

/// @brief less<void> l;
less less;

#endif

/// @}
#else
#pragma message("undefined __cpp_deduction_guides")
#endif

/**
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

/// @} template_parameters
/// @} templ17

/**
 @defgroup lambda17 Lambda

 @{
 */

/**
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

/// @}

/**
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

void lambda_17()
{
	assert(can_be_constexpr1(2) == 2);
	int i = 3;
	assert(can_be_constexpr2(can_be_constexpr1, 3) == 3);
	non_const(1);
	capture_this_by_value();
}

/// @} lcbv

/// @} lambda17

/**
 @defgroup land17 Language
 @{

 https://en.cppreference.com/w/cpp/language

 @defgroup folding Folding
 @{
 */

template<typename... Args>
constexpr bool folding_and(Args... args) { return (true && ... && args); }

template<typename... Args>
constexpr auto folding_sum(Args... args) { return (... + args); }

void folding_demo()
{
	static_assert(!folding_and(true, false, true));
	static_assert(folding_sum(1.0, 2.0f, 3) == 6.0);
}

/**
 @} folding
 @defgroup nn Qualified nested namespace

 https://en.cppreference.com/w/cpp/language/namespace

 http://www.open-std.org/jtc1/sc22/wg21/docs/papers/2014/n4026.html

 @{
 */

/// Before: namespace other { namespace other2 {
namespace outer_namespace::qualified_nested_namespace {
	int in_qualified_nested_namespace;
}
// } } - just for symmetry 

/**
 @} nn
 @defgroup sb Structured bindings

 https://en.cppreference.com/w/cpp/language/structured_binding
 @{
 */

static_assert(__cpp_structured_bindings);

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
 @} sb
 @defgroup iscs Variable declaration in conditionals

 https://en.cppreference.com/w/cpp/language/if

 https://en.cppreference.com/w/cpp/language/switch

 @{
 */

void conditional_with_init()
{
	if (auto a = true) {
	};

	switch (int a = 10) {
	}
}

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
		[[fallthrough]];
	case 2:
		// Indicates that b might be unused, such as on production builds
		[[maybe_unused]] int b = foo();
		assert(b > 0);
		break;
	}
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

static char char_u8 = u8'x';

/**
 @}
 @defgroup enum Direct list initialization of enums
 https://en.cppreference.com/w/cpp/language/character_literal
 https://en.cppreference.com/w/cpp/language/enum
 @{
 */
enum byte_e : unsigned char {};
static byte_e b { 123 };

/// @}

void types_17()
{
	static_assert(is_integral_v<int>);
	static_assert(__cpp_hex_float);
	double hex_double = 0x1.2p3; // https://en.cppreference.com/w/cpp/language/floating_literal
	assert(hex_double == 9.0);

	static_assert(is_invocable<decltype(types_17)>::value);
	static_assert(is_invocable<int()>::value);
	static_assert(is_invocable_r<int, int()>::value);
	static_assert(is_invocable_r<void, void(int), int>::value);
	static_assert(negation_v<bool_constant<false>>);

	auto inc = [](int a) -> int { return a + 1; };
	static_assert(is_invocable_r<int, decltype(inc), int>::value);
	static_assert(__cpp_lib_invoke);
	// https://en.cppreference.com/w/cpp/utility/functional/invoke
	assert(invoke(inc, 2) == 3);
}


/**
 @}
 @defgroup lib17 Library
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

/// https://en.cppreference.com/w/cpp/utility/variant
void variant_demo()
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
	assert(holds_alternative<void const*>(y));
	y = "xyz"s;
	assert(holds_alternative<string>(y));
}

void clamp_demo()
{
	static_assert(__cpp_lib_clamp);
	///  clamp(x, low, high) == x < low ? low : x > high ? high : x;
	assert(clamp(0, 1, 3) == 1);
	assert(clamp(2, 1, 3) == 2);
	assert(clamp(4, 1, 3) == 3);
}

void dynamic_memory_17()
{
	int d[2] = {10, 11};
	unique_ptr<int[]> u1(d);
	assert(u1.get()[0] == 10); // C++11
	assert(u1[1] == 11);
	assert((bool)u1);
	u1.release();
	const shared_ptr<int> s1{0};
	//cout << s1.element_type.name() << endl;
	//cout << typeid(s1.weak_type).name() << endl;
	assert(typeid(reinterpret_pointer_cast<shared_ptr<int>>(s1)).name()
	       == string("St10shared_ptrIS_IiEE"));
	vector<int> s = {5, 7, 4, 2, 8, 6, 1, 9, 0, 3};

	// https://en.cppreference.com/w/cpp/numeric/valarray/deduction_guides
	int a[] = {1, 2, 3};
	valarray va(a, 3); // uses explicit deduction guide
	static_assert(is_integral_v<remove_reference<decltype(va[0])>::type>);
}


void string_view_demo()
{
	static_assert(__cpp_lib_string_view);
	string s = "abcd";
	string_view v = s;
	assert(v.data()  == s.c_str());
	assert(v.substr(1, 2).data() >= s.c_str());
	assert(v.substr(1, 2).data() <= s.c_str() + s.length());
}

/// @} lib17

/**
 @defgroup other17 Other
 @{

 */

/// https://en.cppreference.com/w/cpp/language/inline

inline int inline_var;

/// @}

int main()
{
	references_17();
	folding_demo();
	lambda_17();
	variant_demo();
	clamp_demo();
	dynamic_memory_17();
	string_view_demo();
	// for (auto&& [first,second] : mymap) { }
	types_17();
}

/// @} CPP17
