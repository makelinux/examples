/*
   "Traditional" C, subset of K&R 
 */

#include <string.h>

int max();

max(a, b)
int a, b;
{
    return a > b ? a : b;
}

double g()
{
    return 0.1;
}

int main()
{
	long int li;
	unsigned u = -1;
	struct { int x, y; } s;

	memset(&s, 0, sizeof s);
	u-=1;
	(void) u;
}
