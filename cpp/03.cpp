/**
 @file
 @brief C++03 / C++98

 @defgroup CPP03 C++03 examples
 @brief C++03 / C++98

 https://en.wikipedia.org/wiki/C++03

 @{
 */
#include <utility>
#include <iostream>
#include <cassert>
#include <cstring>
#include <algorithm>
#include <vector>
#include <deque>
#include <list>
#include <queue>
#include <stack>
#include <typeinfo>

using namespace std;

/**
 @defgroup lang03 Language
 @{

 */

void init_03()
{

	// https://en.cppreference.com/w/cpp/language/copy_initialization
	int x3 = {3};
	double x4 = {3.0};

	struct point { int x, y; };

	point p1 = {1, 2};
	(void) p1.x;
	(void) p1.y;

#if gcc_extension
	// designated initializers
	// https://gcc.gnu.org/onlinedocs/gcc/Designated-Inits.html
	__extension__
	point gpp_ext = { .x = 1 }; // C99-like gcc extension
	__extension__
	point gcc_ext = { x: 1 }; // C-like gcc extension
#endif

	// Mutable
	struct struct_with_mutable {
		struct_with_mutable(){};
		mutable int m;
	} const const_struct_with_mutable;
	const_struct_with_mutable.m = 2;
	assert(const_struct_with_mutable.m == 2);
	int y = 0;
	int& reference = y;
}

template<class C>
void test_generic_container(C & c)
{
	assert(c.empty());
	assert(c.max_size() > 1000);
	c.push_back(0);
	assert(c.front() == 0);
	assert(c.back() == 0);
	assert(c.size() == 1);
	c.erase(c.begin());
	c.push_back(1);
	c.erase(c.begin());
	c.assign(4, 1);
	assert(c.size() == 4);
	c.clear();
}

template<class V>
void test_vector_container(V & v)
{
	string err;
	try {
		v.at(666) = 0;
	} catch (std::out_of_range const& exc) {
		err = exc.what();
	}
	assert(err.length());
	assert(v[0] == 1);
	v.resize(4);

	int arr[] = {1, 2, 3};
	v.insert(v.begin(), arr, arr+3);
	assert(v[1] == 2);

}

/// [container](https://en.cppreference.com/w/cpp/container)

void container_03()
{
	list<int> l;
	test_generic_container(l);

	std::vector<int> v;
	test_generic_container(v);
	test_vector_container(v);

	v.reserve(10);
	assert(v.capacity() == 10);

	deque<int> d;
	test_generic_container(d);
	test_vector_container(d);

	stack<int> s;
	queue<int> q;
}

/**
 @fn void sort_03()
 http://www.cplusplus.com/reference/algorithm/sort/?kw=sort

 Compare with @ref lambda::sort_11
 */

/// @private
bool func(int i, int j) { return i < j; }

/// @private
struct _ {
	bool operator() (int i, int j) { return i < j; }
} functor;

void sort_03()
{
	int a[] =  {5, 7, 4, 2, 8, 6, 1, 9, 0, 3};
	std::vector<int> v (a, a + sizeof(a) / sizeof(a[0]));

	// using default comparison (operator <):
	std::sort (v.begin(), v.begin()+4);

	// using function as comp
	sort (v.begin() + 4, v.end(), func);

	// sort using a standard library compare function object
	std::sort(v.begin(), v.end(), std::greater<int>());

	// using object as comp

	std::sort (v.begin(), v.end(), functor);

	int prev = -1;
	for (std::vector<int>::iterator i=v.begin(); i != v.end(); ++i) {
		assert(*i >= prev);
		prev = *i;
	}
}

/// https://en.cppreference.com/w/cpp/language/reference
int& a_ref(int &a) { return a; }

struct Common
{
    int n;
    Common(int x) : n(x) {}
};

/// [ref](https://en.cppreference.com/w/cpp/language/virtual)
struct Virtual_A : virtual Common { Virtual_A() : Common(1) {} };
struct Virtual_B : virtual Common { Virtual_B() : Common(2) {} };
struct Diamond : Virtual_A, Virtual_B {
	Diamond() : Common(3), Virtual_A(), Virtual_B() {}
};

void types_03()
{
	int a = 0;
	assert(typeid(int) == typeid(a));
	assert(typeid(int).name() == string("i"));

	a_ref(a) = 2;
	assert(a == 2);

	Diamond d;
	assert(d.Virtual_A::n == 3);
	assert(d.Virtual_B::n == 3);
}

/// @}

int main(void)
{
	assert(__cplusplus == 199711);

	init_03();
	container_03();
	sort_03();
	types_03();
}

/// @}
