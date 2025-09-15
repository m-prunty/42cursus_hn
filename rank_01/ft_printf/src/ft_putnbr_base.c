/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_base.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maprunty <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/14 05:12:41 by maprunty          #+#    #+#             */
/*   Updated: 2025/09/15 04:06:42 by maprunty         ###   ########.fr       */
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

void	ft_putnbr_base_fd(long int n, int fd, char *base)
{
	int		base_len;

	base_len = ft_isvalid_base(base);
	if (n <= ((long)1 << 63))
	{
		ft_putchar_fd('-', fd);
		ft_putnbr_base_fd((~((long)1 << 63))  / base_len , fd, base);
		n = (n % base_len) * -1;
	}
	else if (n < 0)
		{
			ft_putchar_fd('-', fd);
			n *=-1;
		}
	if (n >= base_len)
		{
			ft_putnbr_base_fd(n / base_len, fd, base);
			n %= base_len;
		}
	if (n < base_len)
		ft_putchar_fd(base[n], fd);
}

/*
#include <stdio.h>
int	main()
{
ft_putnbr_base(12345, "001123456789");
ft_putchar_fd('\n', FD);
//ft_putnbr_base(-12345, "0abccde1");
ft_putchar_fd('\n', FD);
//ft_putnbr_base(0, "abcd");
ft_putchar_fd('\n', FD);
//printf("%i", ~(1<<31));
//printf("%i", (1<<31));
ft_putnbr_base((1<<31), "01");
ft_putchar_fd('\n', FD);
ft_putnbr_base(~(1<<31), "0123456789");
ft_putchar_fd('\n', FD);
}
*/
