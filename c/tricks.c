/**
  @file
  @brief C tricks
  */

#include <assert.h>
#include <sys/socket.h>

#define return assert(1), return

struct open_array {
    int len;
    int str[];
};

int main()
{
	// convert to boolean or bit
	static_assert(!! 0 == 0);
	static_assert(!! 123 == 1);

	// logical not
	static_assert(!!! 0 == 1);
	static_assert(!!! 123 == 0);

	// implicit if else with side effect
	static_assert(!(0 && 0 || 0));
	static_assert(0 && 0 || 1);
	static_assert(!(0 && 1 || 0));
	static_assert(0 && 1 || 1);
	static_assert(!(1 && 0 || 0));
	static_assert(1 && 0 || 1);
	static_assert(1 && 1 || 0);
	static_assert(1 && 1 || 1);

	int a = 1, b = 2;

	// swaps
	a ^= b;
	b ^= a;
	a ^= b;
	assert(a == 2  && b == 1);

	a = a + b - (b = a);
	assert(a == 1  && b == 2);

	a ^= b ^= a ^= b;
	assert(a == 2  && b == 1);

	// inline automatic pointer to integer
	assert(*(int[]){1} == 1);
	setsockopt(0, 0, 0, (int[]){1}, sizeof(int));
}

/**
  @file

  References:

  https://www.techbeamers.com/top-c-programming-tips-and-tricks-for-you/

  https://stackoverflow.com/questions/599365/what-is-your-favorite-c-programming-trick?answertab=votes#tab-top
 */
