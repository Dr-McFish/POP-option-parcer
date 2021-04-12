#include <stdint.h>

uint64_t sqrt_aprox(uint64_t nb)
{
	uint64_t odd;
	uint64_t sqrt;

	odd = 1;
	sqrt = 0;
	if (nb <= 0)
		return (0);
	while (nb > 0)
	{
		nb = nb - odd;
		odd += 2;
		sqrt++;
	}
	return (sqrt);
}

uint64_t is_prime(uint64_t nb)
{
	uint64_t i;
	uint64_t upper_bound;

	i = 2;
	upper_bound = sqrt_aprox(nb);
	if (nb < 2)
		return (0);
	else if (nb == 2)
		return (1);
	while (i <= upper_bound)
	{
		if ((nb % i) == 0)
			return (0);
		i++;
	}
	return (1);
}

uint64_t next_prime(uint64_t nb)
{
	if (is_prime(nb))
		return (nb);
	else
		return (next_prime(nb + 1));
}
