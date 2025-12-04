#include "include/libft.h"
#include <stdio.h>

int main()
{
	ft_atoi("   -42as");
	printf("%s\n", ft_itoa(-42675));
	printf("%s\n", ft_itoa(-10));
	printf("%s\n", ft_itoa(5));
	printf("%s\n", ft_itoa(0));
	printf("%s\n", ft_itoa(1 << 31));
}

