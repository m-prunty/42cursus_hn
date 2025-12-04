/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handlers.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maprunty <maprunty@student.42heilbron      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/15 23:25:20 by maprunty          #+#    #+#             */
/*   Updated: 2025/11/17 13:02:38 by maprunty         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	handle_zero(t_format *fmt, int res)
{
	int	i;

	if (fmt->precision < 0 && check_flags(fmt, ZERO)
		&& !check_flags(fmt, MINUS))
	{
		i = fmt->width - fmt->n - (check_flags(fmt, PLUS))
			- (fmt->isneg && !check_flags(fmt, PLUS))
			- (!fmt->isneg && check_flags(fmt, SPACE))
			- ((check_flags(fmt, HASH)
					&& res && ft_strchr("xX", fmt->spec)) * 2);
		while (i-- > 0)
			ft_putchar_fd_count('0', FD, &fmt->count);
	}
}

void	handle_precis(t_format *fmt, int res)
{
	int	i;

	i = 0;
	if (ft_strchr("sc", fmt->spec))
	{
		if (fmt->spec == 's' && fmt->precision >= 0 && fmt->precision < fmt->n)
			fmt->n = fmt->precision;
		return ;
	}
	else if (fmt->precision > fmt->n || (!fmt->precision && !res))
	{
		if (!fmt->precision && !res)
		{
			fmt->n--;
			fmt->width++;
		}
		i = fmt->precision - fmt->n;
	}
	while (i-- > 0)
		ft_putchar_fd_count('0', FD, &fmt->count);
}

void	handle_prefix(t_format *fmt, unsigned long long res)
{
	if (ft_strchr("p", fmt->spec)
		|| (ft_strchr("xX", fmt->spec) && (check_flags(fmt, HASH) && res)))
	{
		if (res || APPLE)
		{
			if (ft_islower(fmt->spec))
				ft_putstr_fd_count("0x", FD, &fmt->count);
			else
				ft_putstr_fd_count("0X", FD, &fmt->count);
		}
		return ;
	}
	else if (ft_strchr("id", fmt->spec))
	{
		if (fmt->isneg)
			ft_putchar_fd_count('-', FD, &fmt->count);
		else if (check_flags(fmt, PLUS))
			ft_putchar_fd_count('+', FD, &fmt->count);
		else if (check_flags(fmt, SPACE) && !fmt->isneg)
			ft_putchar_fd_count(' ', FD, &fmt->count);
	}
}

void	handle_width(t_format *fmt, int res)
{
	if (ft_strchr("sc%", fmt->spec))
	{
		if (res && fmt->width > fmt->n)
			print_space(fmt->width - fmt->n, &fmt->count);
	}
	else if ((!check_flags(fmt, ZERO) || fmt->precision >= 0))
		print_space(fmt->width - fmt->len, &fmt->count);
}
