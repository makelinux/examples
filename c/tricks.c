/**
  @file
  @brief C tricks
  */

#include <assert.h>
#include <sys/socket.h>

struct open_array {
	int len;
	int str[];
};

void integer_tricks()
{
	// convert to boolean or bit
	static_assert(!! 0 == 0);
	static_assert(!! 123 == 1);

	// logical not
	static_assert(!!! 0 == 1);
	static_assert(!!! 123 == 0);

	// implicit "if else" with side effect
	static_assert(!(0 && 0 || 0));
	static_assert(0 && 0 || 1);
	static_assert(!(0 && 1 || 0));
	static_assert(0 && 1 || 1);
	static_assert(!(1 && 0 || 0));
	static_assert(1 && 0 || 1);
	static_assert(1 && 1 || 1/0);
}

void swaps()
{
	int a = 1, b = 2;

	a ^= b, b ^= a, a ^= b;
	assert(a == 2 && b == 1);

	a = a + b - (b = a);
	assert(a == 1 && b == 2);

	a ^= b ^= a ^= b;
	assert(a == 2 && b == 1);
}

int main()
{
	integer_tricks();
	swaps();

	// inline automatic pointer to integer
	assert(*(int[]){1} == 1);
	setsockopt(0, 0, 0, (int[]){1}, sizeof(int));

	int a, b;

	// https://en.cppreference.com/w/c/language/operator_other
	// https://en.wikipedia.org/wiki/Comma_operator

	// Avoiding compound statement
	if (1)
		a = 1, b = 2, assert(1);
	assert(a == 1 && b == 2);

	// void function can be part of comma operator
	b = (0, assert(1), 2, 3);

	assert(b == 3);

	// Avoiding use of strlen
	int i;
	char s[] = "abc";
	for (i = 0; s[i]; i++);
	assert(i == 3);
}

/**
  @file

  References:

  https://www.techbeamers.com/top-c-programming-tips-and-tricks-for-you/

  https://stackoverflow.com/questions/599365/what-is-your-favorite-c-programming-trick?answertab=votes#tab-top

 */
