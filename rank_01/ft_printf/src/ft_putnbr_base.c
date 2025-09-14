/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_base.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maprunty <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/14 05:12:41 by maprunty          #+#    #+#             */
/*   Updated: 2025/09/14 08:04:36 by maprunty         ###   ########.fr       */
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

void	ft_putnbr_base(int nbr, char *base)
{
	long	lnb;
	int		base_len;

	base_len = ft_isvalid_base(base);
	if (base_len)
	{
		if (nbr == 1 << 31)
		{
			lnb = ~(long)(1 << 31) + 1;
			ft_putnbr_base(-lnb / base_len, base);
			ft_putchar_fd(base[lnb % base_len], FD);
		}
		else if (nbr < 0)
		{
			ft_putchar_fd('-', FD);
			ft_putnbr_base(-nbr, base);
		}
		else if (nbr >= base_len)
			ft_putnbr_base(nbr / base_len, base);
		ft_putchar_fd(base[nbr % base_len], FD);
	}
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
