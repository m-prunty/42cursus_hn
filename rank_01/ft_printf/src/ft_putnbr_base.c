/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_base.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maprunty <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/14 05:12:41 by maprunty          #+#    #+#             */
/*   Updated: 2025/11/12 10:49:20 by maprunty         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "ft_printf.h"

int	ft_isvalid_base(char *base)
{
	int	i;
	int	j;
	int	len;

	i = -1;
	len = ft_strlen(base);
	if (len > 1)
	{
		while (base[++i])
		{
			if (base[i] == '+' || base[i] == '-')
				return (0);
			else
			{
				j = -1;
				while (++j < i)
					if (base[j] == base[i])
						return (0);
			}
		}
		return (i);
	}
	return (0);
}


void	ft_putnbr_base_fmt(long int n, char *base, t_format *fmt)
{
	int		base_len;

	base_len = ft_isvalid_base(base);
	/*	if (n <= ((long)1 << 63))
		{
		if ()//ft_strchr("id", fmt->spec))

		ft_putchar_fd_count('-', FD, count);
		ft_putnbr_base_fmt((~((long)1 << 63)) / base_len , base, count, fmt);
		n = (n % base_len) * -1;
		}
		*/
	if (fmt->isneg) 
	{
		//n = (int)n;
		n *=-1;
		fmt->isneg = 0;
	}
	if (n >= base_len)
	{
		ft_putnbr_base_fmt(n / base_len, base, fmt);
		n %= base_len;
	}
	if (n < base_len)
		ft_putchar_fd_count(base[n], FD, &fmt->count);
}

/*
#include <stdio.h>
int	main()
{
ft_putnbr_base(12345, "001123456789");
ft_putchar_fd_count('\n', FD, &count);
//ft_putnbr_base(-12345, "0abccde1");
ft_putchar_fd_count('\n', FD, &count);
//ft_putnbr_base(0, "abcd");
ft_putchar_fd_count('\n', FD, &count);
//printf("%i", ~(1<<31));
//printf("%i", (1<<31));
ft_putnbr_base((1<<31), "01");
ft_putchar_fd_count('\n', FD, &count);
ft_putnbr_base(~(1<<31), "0123456789");
ft_putchar_fd_count('\n', FD, &count);
}
*/
