/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_base.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maprunty <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/14 05:12:41 by maprunty          #+#    #+#             */
/*   Updated: 2025/12/14 09:58:15 by maprunty         ###   ########.fr       */
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

void	ft_putnbr_ptr(size_t n, t_format *fmt)
{
	size_t	base;
	char	*symbols;

	symbols = "0123456789abcdef";
	base = 16;
	if (n < base)
		(ft_putchar_fd_count(symbols[n], fmt->fd, &fmt->count));
	else
	{
		ft_putnbr_ptr(n / base, fmt);
		ft_putnbr_ptr(n % base, fmt);
	}
}

void	ft_putnbr_base_fmt(long int n, char *base, t_format *fmt)
{
	int		base_len;

	base_len = ft_isvalid_base(base);
	if (fmt->isneg)
	{
		n *= -1;
		fmt->isneg = 0;
	}
	if (n >= base_len)
		ft_putnbr_base_fmt(n / base_len, base, fmt);
	n %= base_len;
	if (n < base_len)
		ft_putchar_fd_count(base[n % base_len], fmt->fd, &fmt->count);
}
