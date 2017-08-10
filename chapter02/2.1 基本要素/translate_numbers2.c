#include <stdio.h>

int main(int argc, char const *argv[])
{
	int n;
	
	while(1)
	{
		scanf("%d", &n);

		switch(n)
		{
		case 1:
			printf("one\n");
			break;
		case 2:
			printf("two\n");
			break;
		case 3:
			printf("three\n");
			break;
		case 4:
			printf("four\n");
			break;
		default:
			printf("unknown\n");
		}
	}

	return 0;
}
