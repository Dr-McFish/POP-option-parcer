#include "primes.h"
#include <stdio.h>

int main()
{
	int i = 7;
	if (is_prime(i)) printf("%d is prime\n", i);
	else printf("%d is NOT prime\n", i);

	i = 2102;
	printf("Next prime after %d %d\n", i, next_prime(i));
}
