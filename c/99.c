/// https://en.wikipedia.org/wiki/C99

#include <assert.h>

// C++ comment

int main()
{
	assert(__STDC_VERSION__ > 199900);
	struct xy { int x, y; };
	struct ab { struct xy a, b; };

	struct xy a1 = { .y = 1, .x = 2 };

	int arr[3] = { [1] = 5 };

	struct ab b = { .a.x = 0 };
	struct xy a2 = { .x = 1, 2 };

	{ }
	int declaration_after_statement;

	return 0;
}
