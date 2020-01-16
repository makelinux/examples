#include <utility>
#include <iostream>
#include <cassert>
#include <algorithm>
#include <vector>

using namespace std;

/**
 @file
 @brief C++03 / C++98

 @defgroup CPP03 C++03 examples
 @brief C++03 / C++98

 https://en.wikipedia.org/wiki/C++03

 @{
 */

bool func(int i, int j) { return i < j; }

struct _ {
  bool operator() (int i, int j) { return i < j; }
} functor;

/**
 http://www.cplusplus.com/reference/algorithm/sort/?kw=sort

 Compare with @ref sort_11
 */

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

int main(void)
{
	assert(__cplusplus == 199711);

	int x3 = {3};
	double x4 = {3.0};

	sort_03();
}

/// @}
