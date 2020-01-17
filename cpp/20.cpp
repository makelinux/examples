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
	point p1 = { .x = { 1 }, .y{ 2 } };
	point p2 { .x = { 1 }, .y{ 2 } };
#endif
#ifndef __clang__
	point p4 = { x: 1, y: 2 }; // C-like gcc extension
#endif
	line l1 = {};
	line l2 = {1, 2};
	assert(l2.a.x == 1);
	assert(l2.a.y == 2);

	line l3 = {1, 2, 3, 4};
	assert(l3.b.x == 3);
	assert(l3.b.y == 4);
}

int main()
{
	init_20();
}
