#include <stdio.h>

int main()
{
	printf("-|%*s|-\n", strlen("hello world") + 2, "hello world");
	return (0);
}