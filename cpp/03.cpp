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

void types_03()
{
	int a = 0;
	assert(typeid(int) == typeid(a));
	assert(typeid(int).name() == string("i"));

	a_ref(a) = 2;
	assert(a == 2);
}

/// @}

int main(void)
{
	assert(__cplusplus == 199711);

	init_03();

	sort_03();

	types_03();
}

/// @}
