#include <unistd.h>

void task_1(int lim)
{
	for (int j = 0; j < lim; j++)
		getppid();
}

void x1(void)
{
	for (int j = 0; j < 100; j++)
		task_1(200000);
}

void task_2(int lim)
{
	for (int j = 0; j < lim; j++)
		getppid();
}

void x2(void)
{
	for (int j = 0; j < 1000; j++)
		task_2(10000);
}
