/**
 @file
 @brief C99

 [C99 @ wikipedia](https://en.wikipedia.org/wiki/C99)

 [C99 gcc status](https://gcc.gnu.org/c99status.html)
 */

#include <assert.h>

// C++ comment

int main()
{
	assert(__STDC_VERSION__ > 199900);
	struct xy { int x, y; };
	struct nest { struct xy nested; };

	struct nest n = { .nested.x = 0 };
	struct xy out_of_order = { .y = 1, .x = 2 };
	struct xy mixed = { .x = 1, 2 };
	int array[3] = { [1] = 5 };

	{ }
	int declaration_after_statement;

	return 0;
}
