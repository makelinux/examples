/**
  @file
  @brief "Traditional" C, before books of K&R

  https://gcc.gnu.org/onlinedocs/cpp/Traditional-warnings.html

  See also:
  * [K&R_C](https://en.wikipedia.org/wiki/K%26R_C)

 */

#include <string.h>

int max();

max(a, b)
int a, b;
{
	return a > b ? a : b;
}

int main()
{
	long int li;
	unsigned u = -1;
	struct { int x, y; } s;

	memset(&s, 0, sizeof s);
	u -= 1;
	(void) u;
	return 0;
}
