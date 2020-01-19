static_assert(__cplusplus >= 201707);

#include <iostream>
#include <vector>
#include <string_view>
#include <cmath>
#include <cassert>
#include <vector>
#include <iostream>



using namespace std;

/**
  https://en.cppreference.com/w/cpp/ranges
  https://en.cppreference.com/w/cpp/utility/source_location
  https://en.cppreference.com/w/cpp/language/coroutines
  */

void init_20()
{
	struct point { int x, y; };
	struct line { point a, b; };

	// https://en.cppreference.com/w/cpp/language/aggregate_initialization

#if __cplusplus > 201707
	point p1 = { .x = { 1 } };
	assert(p1.x == 1);
	assert(!p1.y);

	point p2 { .y { 2 } };
	assert(p2.y == 2);
	assert(!p2.x);
#endif

	line l1 = { };
	line l2 = { 1, 2 };
	assert(l2.a.x == 1);
	assert(l2.a.y == 2);

	line l3 = { 1, 2, 3, 4 };
	assert(l3.b.x == 3);
	assert(l3.b.y == 4);
}

#if __cpp_concepts

// https://en.wikipedia.org/wiki/Concepts_(C++)
// https://en.cppreference.com/w/cpp/language/constraints
// https://github.com/AnthonyCalandra/modern-cpp-features/blob/master/CPP20.md

// Using 'requires':

template<typename T>
requires is_same_v<T, int>
T inc(T a)
{ return a + 1; };

template<typename T>
T inc(T a)
requires is_same_v<T, string>
{ return a + "1"; };

void concept_demo()
{
	assert(inc<int>(1) == 2);
	assert(inc<string>("1") == "11");
}

#else
void concept_demo() {}
#pragma message("undefined __cpp_concepts")
#endif
int main()
{
	init_20();
	concept_demo();
}
