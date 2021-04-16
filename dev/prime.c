#include <stdint.h>
#include <stdbool.h>

int sqrt_aprox(int nb)
{
	int odd;
	int sqrt;

	odd = 1;
	sqrt = 0;
	if (nb <= 0)
		return (0);
	while (nb > 0) {
		nb = nb - odd;
		odd += 2;
		sqrt++;
	}
	return (sqrt);
}

bool is_prime(int nb)
{
	if (nb < 2)
		return (false);
	else if (nb == 2)
		return (true);
	int upper_bound = sqrt_aprox(nb);
	int i = 2;
	while (i <= upper_bound) {
		if ((nb % i) == 0)
			return (false);
		i++;
	}
	return (true);
}

int next_prime(int nb)
{
	if (is_prime(nb))
		return (nb);
	else
		return (next_prime(nb + 1));
}
