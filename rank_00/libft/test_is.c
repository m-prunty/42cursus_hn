#include <ctype.h>
#include <stdio.h>
#include "include/libft.h"

int main()
{
	int i = -1;
	
	while (++i <= 128)
	{
		printf("%d, alpha:\t%i,\t upper:  \t%i,\t lower:  \t%i,\t digit:  \t%i,\t alnum:  \t%i,\t ascii:  \t%i,\t print:  \t%i\n", i, 
			isalpha(i), isupper(i), islower(i), isdigit(i), isalnum(i), isascii(i), isprint(i));
		printf("%d, ft_alpha:\t%i,\t ft_upper:\t%i,\t ft_lower:\t%i,\t ft_digit:\t%i,\t ft_alnum:\t%i,\t ft_ascii:\t%i,\t ft_print:\t%i\n", i, 
			ft_isalpha(i), ft_isupper(i), ft_islower(i), ft_isdigit(i), ft_isalnum(i), ft_isascii(i), ft_isprint(i));
	}
}
