#include <stdio.h>

int main(int argc, char const *argv[])
{
	int n;
	
	while(1)
	{
		scanf("%d", &n);

		if(n == 1)
			printf("one\n");
		else if(n == 2)
			printf("two\n");
		else if(n == 3)
			printf("three\n");
		else if(n == 4)
			printf("four\n");
		else
			printf("unknown\n");
	}

	return 0;
}
