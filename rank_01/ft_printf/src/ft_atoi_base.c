/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maprunty <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/14 05:12:41 by maprunty          #+#    #+#             */
/*   Updated: 2025/09/14 08:04:42 by maprunty         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_convert_charbase(char c, int *val, char *base)
{
	*val = 0;
	while (base[*val])
	{
		if (c == base[*val])
			return (*val);
		(*val)++;
	}
	return (-1);
}

int	ft_atoi_base(char *str, char *base)
{
	int	res;
	int	neg;
	int	base_len;
	int	val;

	base_len = ft_isvalid_base(base);
	val = 0;
	res = 0;
	neg = 1;
	if (base_len)
	{
		while (*str == ' ' || (*str >= 9 && *str <= 13))
			str++;
		while (*str == '-' || *str == '+')
			if (*str++ == '-')
				neg *= -1;
		while (*str)
		{
			if (ft_convert_charbase(*str++, &val, base) >= 0)
				res = res * base_len + val;
			else
				break ;
		}
	}
	return (res * neg);
}
/*
#include <stdio.h>
#include <unistd.h>
int ft_putchar(char c)
{
	write(1, &c, 1);
}
int	main()
{
	printf("%i\n",ft_atoi_base("12345","001123456789"));
	ft_putchar('\n');
	printf("%i\n",ft_atoi_base("-110002345", "011"));
	ft_putchar('\n');
	printf("%i\n",ft_atoi_base("0", "a"));
	ft_putchar('\n');
	//printf("%i", ~(1<<31));
	//printf("%i", (1<<31), );
	printf("%i\n",ft_atoi_base("10000000000000000000000000000000a", "01"));
	ft_putchar('\n');
	printf("%i\n",ft_atoi_base("0111111111111111111111111111111111a", "01"));
	ft_putchar('\n');
	printf("%i\n",ft_atoi_base("-a","0123456789abcdef"));
	ft_putchar('\n');
}
*/
