#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int cmp(const void *p1, const void *p2)
{
	return *(int *)p1 - *(int *)p2;
}

void sort_libc()
{
	int list[] = {3, 1, 2};

	qsort(list, 3, sizeof(list[0]), cmp);
	assert(list[0] == 1);
	assert(list[2] == 3);
}

int main()
{
	sort_libc();
	return 0;
}
