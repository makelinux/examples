/* 
 https://developerinsider.co/difference-between-c-and-ansi-c/
 */

#include <assert.h>

function_returns_int()
{
	return 0;
}

void proc()
{
}

int main()
{
	{
		struct xy { int x, y; };
		struct line { struct xy a, b; };
		struct line c = {1, };
		assert(c.a.x);
		assert(!c.b.y);
	}
	{
		char s[10] = {'a', };
		assert(!s[9]);
	}
	{
		signed char negative = -127;
		assert(negative < 0);
	}
	{
		long double ld;
		assert(sizeof ld == 16);
	}
	{
		const c = 1;
		assert(c);
	}
	{
		enum { e0, e1  } e;
		e = e1;
		assert(!e0);
		assert(e);
	}
	assert(!function_returns_int());
	return 0;
}
