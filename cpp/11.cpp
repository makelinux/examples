/**
 @file
 @brief C++11
 @defgroup CPP11 C++11 examples

 https://en.wikipedia.org/wiki/C++11

 https://github.com/AnthonyCalandra/modern-cpp-features/blob/master/CPP11.md

 @{

 */

static_assert(__cplusplus == 201103, "");

#include <signal.h>
#include <unistd.h>
#include <utility>
#include <vector>
#include <iostream>
#include <cassert>
#include <functional>
#include <algorithm>
#include <array>
#include <forward_list>
#include <memory>
#include <chrono>
#include <thread>
#include <mutex>
#include <future>

#if __has_include (<version>)
#include <version>
#endif

using namespace std;

/**
 @defgroup lang11 Language
 @{

 */

void types_11()
{
	static_assert(__cpp_decltype, "");

	int a;
	// https://en.cppreference.com/w/cpp/header/type_traits
	decltype(a) b; // https://en.cppreference.com/w/cpp/language/decltype

	assert((is_same<decltype(a), decltype(b)>::value));
	assert((!is_same<decltype(a), unsigned>::value));
	assert((is_same<int, int32_t>::value));
	assert((is_same<signed, int32_t>::value));

	assert(is_integral<int>::value);
	assert(is_integral<bool>::value);
	assert(!is_integral<float>::value);
	assert(is_pointer<int*>::value);
	assert(sizeof (long long) >= 8);
}

/// [unique_ptr](https://en.cppreference.com/w/cpp/memory/unique_ptr)

void unique_pounter()
{
	int d = 0;
	unique_ptr<int> u1;
	assert(!u1);
	u1.reset(&d);
	assert(u1);
	*u1 = 1;
	assert(d == 1);

	unique_ptr<int> u2;
	// u2 = u1; - prohibited

	int * p1 = u1.get();
	u2 = move(u1); // [move](https://en.cppreference.com/w/cpp/utility/move)
	assert(u2.get() == p1);
	assert(u2);
	assert(!u1);
	assert(u2.get() == &d);
	// must release because d is local
	u2.release();
	u2.reset(new int(10));
	assert(*u2 == 10);

	u2.reset(); // deletes int(10)
	assert(u2 == nullptr); // [nullptr](https://en.cppreference.com/w/cpp/language/nullptr)

	assert(!u2);
}

/// [shared_ptr](https://en.cppreference.com/w/cpp/memory/shared_ptr)

void shared_pointer()
{
	shared_ptr<int> s1;
	assert(!s1);
	assert(!s1.use_count());

	auto s2 = make_shared<int>(1);
	assert(s2.use_count() == 1);

	s1 = s2;
	assert(s1.use_count() == 2);

	*s1 = 2;
	assert(*s1 == *s1.get());
	assert(*s2 == 2);

	s2 = nullptr; // like s2.reset();
	assert(s1.use_count() == 1);
	assert(!s2.use_count());
}

/// [weak_ptr](https://en.cppreference.com/w/cpp/memory/weak_ptr)

void weak_pointer()
{
	std::weak_ptr<int> wp;

	assert(!wp.lock());
	assert(!wp.use_count());
	auto sp = std::make_shared<int>(1);
	wp = sp;
	assert(*wp.lock() == 1);
}

/**
  [new](https://en.cppreference.com/w/cpp/memory/new/operator_new),

  [delete](https://en.cppreference.com/w/cpp/memory/new/operator_delete)
 */

void dynamic_memory_11()
{
	auto a = new int[3] {1, 2, 3};
	assert(a[2] == 3);
	delete[] a;

	auto as = new string[3] {"1", "2", "3"};
	assert(as[2] == "3");
	delete[] as; // calls destructors for all members

	unique_pounter();

	shared_pointer();

	weak_pointer();
}

/// func_type - overloaded functions

char func_type(const int& x)
{
	assert(is_const<typename remove_reference<decltype(x)>::type>::value);
	assert(is_lvalue_reference<decltype(x)>::value);
	return 'C';
}

char func_type(int& x)
{
	assert(is_lvalue_reference<decltype(x)>::value);
	return 'L';
}

char func_type(int&& x)
{
	assert(is_rvalue_reference<decltype(x)>::value);
	return 'R';
}

template<class T>
char func_type_template(T&& x) // x is a forwarding reference
{
	// x is not R-value here
	assert(func_type(x) != 'R');

	// x can be forwarded as R or L value
	// https://en.cppreference.com/w/cpp/utility/forward
	return func_type(forward<T>(x)); // like func_type((T)(x));
}

void references_11()
{
	// https://en.cppreference.com/w/cpp/language/reference
	assert(is_reference<int&>::value);

	// L-value:
	assert(is_lvalue_reference<int&>::value);

	// R-value
	assert(is_rvalue_reference<int&&>::value);

	const int c = 1;
	int i;

	assert(func_type(c) == 'C');
	assert(func_type(i) == 'L');
	assert(func_type(1) == 'R');

	assert(func_type_template(c) == 'C');
	assert(func_type_template(i) == 'L');
	assert(func_type_template(1) == 'R');
}

/**
  [direct_initialization](https://en.cppreference.com/w/cpp/language/direct_initialization)

  [list_initialization](https://en.cppreference.com/w/cpp/language/list_initialization)

  [Member_initialization](https://en.cppreference.com/w/cpp/language/data_members#Member_initialization)

  [aggregate_initialization](https://en.cppreference.com/w/cpp/language/aggregate_initialization)

  */

void init_11()
{
	class C { public: int a, b, c; };
	auto o2 = C {1, 2, 3};
	C o3 {1, 2, 3};
	(void) o3;

	// https://en.cppreference.com/w/cpp/language/zero_initialization
	auto z1 = C();
	C z2 = {};
	auto z3 = C {};

	assert(!z1.a);
	assert(!z2.a);
	assert(!z3.a);
	array<int, 3> a {1, 2};
}

/**
 Trailing return type

 https://en.cppreference.com/w/cpp/language/function

 https://www.ibm.com/support/knowledgecenter/en/ssw_ibm_i_73/rzarg/trailing_return.htm

*/


/// https://en.cppreference.com/w/cpp/language/auto
auto auto_int = 1;

// int before(int a) { return a; }
auto trailing_return_type(int a) -> int
{
	return a;
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
	auto binded = bind(ft2, 3);
	assert(binded() == 5);
}

static_assert(__cpp_constexpr, "");

/// https://en.cppreference.com/w/cpp/language/constexpr

constexpr int constexpr_factorial(int n)
{
    return n <= 1 ? 1 : (n * constexpr_factorial(n - 1));
}

/// https://en.cppreference.com/w/cpp/language/parameter_pack

template<typename T>
T constexpr adder(T v) {
  return v;
}

template<typename T, typename... Args>
T constexpr adder(T first, Args... args) {
  return first + adder(args...);
}

static_assert(adder(1,2,3) == 6,"");

struct Base11
{
     virtual void method1();
     virtual void method2();
};

struct Derived11 : Base11
{
    void method1() override; ///< [ref](https://en.cppreference.com/w/cpp/language/override)
    void method2() final; ///< [ref](https://en.cppreference.com/w/cpp/language/final)
};

/// @}

/**
 @defgroup lambda11 Lambda
 https://en.cppreference.com/w/cpp/language/lambda
 https://www.geeksforgeeks.org/lambda-expression-in-c/
 @{
 */

static void lambda_basics(void)
{
	auto annotated_named_lambda_expression =  // optional name
		[ ] // capture clause
		( ) // optional list of arguments
		{ }; // body

	// Primitive named lambdas are just like closure functions:
	// https://en.wikipedia.org/wiki/Closure_(computer_programming)

	// declaration like a function:
	// void closure() { };
	auto closure = [] { };

	closure();

	// with arguments
	auto pass = [] (int a) { return a; };
	assert(pass(5) == 5);

	// lambda captures external value
	int c = 1;
	auto get_i = [=] () { return c; };
	assert(get_i() == 1);

	// lambda captures external variable by reference
	// with omitted arguments and return type
	auto inc_get = [&] { return ++c; };
	assert(inc_get() == 2);
	assert(inc_get() == 3);

	// annotated expanded empty inline lambda call:
	[ ] // capture
	( ) // optional list of arguments
	-> void // optional return value
	{ } // body
	( ); // call with arguments

	// annotated expanded sample inline lambda call:
	c = // result
	[c] // capture
	(int a) // an argument
	-> int // return value
	{ return c + a; } // body
	(1); // call with argument
	assert(c == 4);

	// inline lambda which is called in place
	// https://en.wikipedia.org/wiki/Anonymous_function

	// assert((1 + 1) == 2);
	assert([](int a) { return a + 1; }(1) == 2);

	// Actually calling lambda inline is useless
	// and is provided only for demonstration.
}

/// @cond
static int glob;
/// @endcond

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
	auto inc_global = [] () { return ++glob; };
	assert(inc_global() == 1);
	assert(inc_global() == 2);
}

/// [container](https://en.cppreference.com/w/cpp/container)

void container_11()
{
	// [list_initialization](https://en.cppreference.com/w/cpp/language/list_initialization)
	vector<int> v = {1, 2, 3};
	assert(v.data()[2] == 3);

	v.shrink_to_fit();

	v.emplace(v.cbegin(), 0);
	assert(v.front() == 0);

	v.emplace_back(4);
	assert(v.back() == 4);

	array<int, 1> a1, a2;
	swap(a1, a2);

	/// [forward_list](https://en.cppreference.com/w/cpp/container/forward_list)
	forward_list<int> fl;

	fl.push_front(1);
	assert(fl.front() == 1);
	fl.emplace_front(2);
	assert(fl.front() == 2);
	fl.insert_after(fl.cbegin(), 3);
	assert(fl.front() + 1 == 3);
	assert(fl.front() == 2);
	fl.erase_after(fl.cbefore_begin()); // like fl.pop_front();
	assert(fl.front() == 3);
	fl.pop_front();
}

/// [algorithm](https://en.cppreference.com/w/cpp/algorithm)

void algorithm_11()
{
	vector<int> v = {1, 2, 3};
	assert(find(begin(v), end(v), 0) == end(v));
	assert(find(begin(v), end(v), 1) != end(v));
}

/// Compare with @ref sort_03

void sort_11()
{
	/// [array](https://en.cppreference.com/w/cpp/container/array)

	array<int, 10> s {5, 7, 4, 2, 8, 6, 1, 9, 0, 3};
	sort(s.begin(), s.end(),
		  // sort using a lambda expression
		  [](int a, int b)
		  { return a > b; }
		 );
}

/// @}

/**
 @defgroup lambda11_complex More complex Lambdas
 @{
 */

/// @cond

/// [function](https://en.cppreference.com/w/cpp/utility/functional/function)

// int use_lambda(int a; int (func*)(int))
static int use_lambda(int a, function<int(int)> f)
{
	// lambda argument is like pointer to functions
	return f(a);
}

static function<int(int)> g_f;

static void set_lambda(function<int(int)> &&f)
{
	g_f = f;
}

static int call_lambda(int a)
{
	return g_f(a);
}

/// @endcond

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

	int x = 0;
	[x] () mutable { assert(++x);}();
	assert(x == 0);
}

/// @} lambda11_complex

/**
 @defgroup threads11 Threads
 [threads](https://en.cppreference.com/w/cpp/thread)
 @{
  */

/// @cond

// just function with delay for demonstration
int lento(int a = 0)
{
	this_thread::yield();
	this_thread::sleep_for(chrono::milliseconds(20));
	return a;
}
/// @endcond

/**
  https://en.cppreference.com/w/cpp/thread/condition_variable
  */

void condition_variable_11()
{
	mutex m;
	bool ready;
	condition_variable cv;
	thread initiator([&m, &ready, &cv] {
		unique_lock<mutex> lk(m);
		lento();
		lk.unlock();
		ready = true;
		cv.notify_one();
	});
	unique_lock<mutex> lk(m);
	cv.wait(lk, [&ready] {return ready;});
	initiator.join();
}

void threads_11()
{
	this_thread::yield();
	this_thread::get_id();
	this_thread::sleep_for(chrono::nanoseconds(1));
	promise<int> p;
	future<int> f = p.get_future();
	int v = 0;
	thread t([&p, &v]{
		 lento();
		 p.set_value(2);
		 v = 3;
		 });
	assert(v == 0);
	assert(f.get() == 2);
	lento();
	assert(v == 3);
	thread t2;
	t2.swap(t);
	assert(!t.joinable());
	assert(t2.joinable());
	t2.join();
	try {
		t2.join();
		t2.detach();
	} catch(const system_error& e) {
		assert(e.code().value() == 22);
	}
	assert(!t2.joinable());

	// detach demo
	{
		thread t3([&p, &v]{
			  v = 4;
			  });
		t3.detach();
	}
	lento();
	assert(v == 4);

	condition_variable_11();
}

void mutex_11()
{
	int unguarded = 0, guarded = 0;
	mutex m;

	thread t1([&unguarded, &guarded, &m]{
		  unguarded = lento(unguarded) + 1;

		  lock_guard<mutex> guard(m);
		  guarded = lento(guarded) + 1;
		  });
	thread t2([&unguarded, &guarded, &m]{
		  unguarded = lento(unguarded) + 1;

		  lock_guard<mutex> guard(m);
		  guarded = lento(guarded) + 1;
		  });

	assert(unguarded == 0);
	assert(guarded == 0);
	t1.join();
	t2.join();
	assert(unguarded == 1);
	assert(guarded == 2);
}
/// @} threads11

/**
 @{

  TODO:
     function<int(void)> get_a = a;

  https://en.cppreference.com/w/cpp/language/move_constructor

  https://en.cppreference.com/w/cpp/language/move_assignment

  https://en.cppreference.com/w/cpp/language/attributes

  https://en.cppreference.com/w/cpp/language/string_literal

  https://en.cppreference.com/w/cpp/language/character_literal

  https://en.cppreference.com/w/cpp/language/user_literal

  https://en.cppreference.com/w/cpp/language/initializer_list

  https://en.cppreference.com/w/cpp/language/range-for

  https://en.cppreference.com/w/cpp/utility/declval

  https://en.cppreference.com/w/cpp/language/range-for

  https://en.cppreference.com/w/cpp/types/is_move_constructible

  https://en.cppreference.com/w/cpp/types/is_constructible

  https://en.cppreference.com/w/cpp/utility/functional/ref

  https://en.cppreference.com/w/cpp/utility/functional/reference_wrapper

 @}
 */

void sig(int)
{
	abort();
}

int main(void)
{
	signal(SIGALRM, sig);
	alarm(1);
	references_11();
	init_11();
	auto r = trailing_return_type(1);
	(void) r;
	lambda_basics();
	lambda_capture();
	lambda_complex();
	func_11();
	container_11();
	algorithm_11();
	sort_11();
	dynamic_memory_11();
	static_assert(constexpr_factorial(4), "");

	types_11();
	threads_11();
	mutex_11();

	return 0;
}

/// @}
