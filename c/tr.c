/*
  "Traditional" C, before books of K&R
  https://gcc.gnu.org/onlinedocs/gcc-7.5.0/cpp/Traditional-warnings.html
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
