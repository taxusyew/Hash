#include "stdio.h"

int main()
{
	int p;
	scanf("%d",&p);

    // for (int i = 2; i < sqrt(q); i++)
	for (int i = 2; i < p/2; i++)
	{
		if((p % i) == 0)
		{
			printf("%d is not prime number",p);
			scanf("%d",&p);
			return 0;
		}
	}

	printf("%d is prime number",p);
	scanf("%d",&p);
	return 0;
}
