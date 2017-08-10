#include <stdio.h>

int main(void)
{
	printf("[%d]\n", __LINE__);

	goto label;

	printf("[%d]\n", __LINE__);
label:

	printf("[%d]\n", __LINE__);
}
