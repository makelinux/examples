_Static_assert(__STDC_VERSION__ > 201100, "");

/**
 @file
 @brief C11

 [C11 @ wikipedia](https://en.wikipedia.org/wiki/C11_(C_standard_revision))

 [C11 gcc status](https://gcc.gnu.org/wiki/C11Status)

  */
#include <stdnoreturn.h>
#include <stdatomic.h>
#include <math.h>
#include <assert.h>
#include <stdio.h>

#if !__STDC_NO_THREADS__
#include <threads.h>

/**

  https://en.cppreference.com/w/c/thread

  https://www.gnu.org/software/libc/manual/html_node/ISO-C-Threads.html
  */

int run(void *arg)
{
	*(int *)arg = 1;
}

int thrd_passed;

_Static_assert(thrd_success == 0, "");

void thrd_test()
{
	thrd_t thread;
	int res;
	int passed = 0;
	res = thrd_create(&thread, run, &passed);
	assert(!res);
	assert(res == thrd_success);

	thrd_join(thread, NULL);
	assert(passed);
}

#else

#pragma message "thrd_test skipped"
void thrd_test()
{
}

#endif

#define cbrt(x) _Generic((x), long double: cbrtl, \
                              default: cbrt, \
                              float: cbrtf)(x)

int main()
{
	assert(__STDC_VERSION__ > 201100);
	atomic_int acnt;
	++acnt; // is thread safe
	assert(cbrt(1.1 * 1.1 * 1.1) == 1.1);
	assert(cbrt(8) == 2);
	thrd_test();
	return 0;
}
