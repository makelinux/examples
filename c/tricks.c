/**
  @file
  @brief C tricks
  */

#include <assert.h>
#include <string.h>
#include <stdio.h>
#include <sys/socket.h>

#define STRINGIFY_(arg)          #arg
#define STRINGIFY(arg)           STRINGIFY_(arg)

struct open_array {
	int len;
	int str[];
};

void integer_tricks()
{
	// convert to boolean or bit
	static_assert(!! 0 == 0);
	static_assert((!! 123) == 1);

	// logical not
	static_assert((!!! 0) == 1);
	static_assert(!!! 123 == 0);

	// implicit "if else" with side effect
	static_assert(!((0 && 0) || 0));
	static_assert((0 && 0) || 1);
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

struct itos_ {
	char str[12]; /* more than length of INT_MAX */
};

/**
  https://en.cppreference.com/w/c/language/lifetime
  */

static inline struct itos_ itos(int i)
{
	struct itos_ s;
	(void)snprintf(s.str, sizeof(s.str), "%d", i);
	return s;
}

int main()
{
	assert(0 == strcmp(STRINGIFY(123), "123"));

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

	assert(0 == strcmp("1234", itos(1234).str));
	//memory leak: assert(0 > strcmp(itos(123).str, itos(456).str));
}

/**
  @file

  References:

  https://www.techbeamers.com/top-c-programming-tips-and-tricks-for-you/

  https://stackoverflow.com/questions/599365/what-is-your-favorite-c-programming-trick?answertab=votes#tab-top

 */
