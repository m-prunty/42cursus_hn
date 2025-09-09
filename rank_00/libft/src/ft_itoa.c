/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maprunty <maprunty@student.42heilbronn.de  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/05 15:42:37 by maprunty          #+#    #+#             */
/*   Updated: 2025/09/09 10:40:28 by maprunty         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
/*
Parameters
n: the integer to convert.

Return value
The string representing the integer.
NULL if the allocation fails.

Description 
Allocates (with malloc(3)) and returns a string
representing the integer received as an argument.
Negative numbers must be handled.
 */

void	ft_putchar_recs(char **s, int c)
{
	**s = c;
	(*s)++;
	**s = '\0';
}

int		ft_count_digits(long int n)
{
	if (!n)
		return (0);
	if (n < 0)
		return (ft_count_digits(-n) + 1);
	else
		return (ft_count_digits(n / 10) + 1);
}

void	ft_itoa_str(char **s, int n)
{
	long int	lint;

	if (n <= 1 << 31)
	{
		lint = ~(long)(1 << 31) + 1;
		ft_itoa_str(s, -lint / 10);
		ft_putchar_recs(s, lint % 10 + '0');
	}
	else if (n < 0)
	{
		ft_putchar_recs(s, '-');
		ft_itoa_str(s, -n);
	}
	else if (n >= 10)
	{
		ft_itoa_str(s, n / 10);
		ft_putchar_recs(s, n % 10 + '0');
	}
	else
	{
		ft_putchar_recs(s, n % 10 + '0');
		**s = '\0';
	}
}

char	*ft_itoa(int n)
{
	char	*s;
	int		i;

	i = ft_count_digits(n) ;
	if (!n)
		i += 1;
	s = malloc(sizeof(char) * (i + 1));
	if (!s)
		return (NULL);
	ft_itoa_str(&s, n);
	return (s - i);
}
