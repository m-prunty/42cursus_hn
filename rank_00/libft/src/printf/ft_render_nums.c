/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_render_nums.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maprunty <maprunty@student.42heilbronn.de  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/11 18:54:21 by maprunty          #+#    #+#             */
/*   Updated: 2025/11/17 12:58:51 by maprunty         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char	*get_base(t_format *fmt, char *base_s)
{
	if (ft_strchr("idu", fmt->spec))
		ft_strlcpy(base_s, BASE, 11);
	else if (ft_strchr("xXp", fmt->spec))
		ft_strlcpy(base_s, BASE, 17);
	if (ft_isupper(fmt->spec))
		ft_striteri(base_s, ft_iter_up);
	return (base_s);
}

int	ft_count_digits_base(unsigned long long n, int base, t_format *fmt)
{
	int	base_len;

	base_len = 0;
	if (!n)
		return (1);
	if (ft_strchr("id", fmt->spec))
	{
		if ((int)n < 0)
			n *= -1;
		while ((int)n)
		{
			n = (int)n / base;
			base_len += 1;
		}
	}
	while (n)
	{
		n /= base;
		base_len += 1;
	}
	return (base_len);
}

void	just_left(unsigned long long res, char *base_s, t_format *fmt)
{
	handle_prefix(fmt, res);
	handle_precis(fmt, res);
	if (fmt->spec == 'p')
		ft_putnbr_ptr(res, fmt);
	else if (fmt->n)
		ft_putnbr_base_fmt(res, base_s, fmt);
	print_space(fmt->width - fmt->len, &fmt->count);
}

void	just_right(unsigned long long res, char *base_s, t_format *fmt)
{
	if (ft_strchr("id", fmt->spec) && !res && !fmt->precision && fmt->width)
		fmt->len--;
	if (check_flags(fmt, ZERO) && fmt->precision < 0)
	{
		handle_prefix(fmt, res);
		handle_zero(fmt, res);
	}
	else
	{
		handle_width(fmt, res);
		handle_prefix(fmt, res);
		handle_precis(fmt, res);
	}
	if (fmt->spec == 'p')
		ft_putnbr_ptr(res, fmt);
	else if (fmt->n)
		ft_putnbr_base_fmt(res, base_s, fmt);
}

int	ft_render_nums(t_format *fmt)
{
	unsigned long long	res;
	char				base_s[17];

	res = get_value(fmt);
	if (fmt->spec == 's')
		return (1);
	if (ft_strchr("id", fmt->spec) && (int)res < 0)
		fmt->isneg = 1;
	fmt->n = ft_count_digits_base(res, ft_strlen(get_base(fmt, base_s)), fmt);
	fmt->len = fmt->n;
	if (fmt->precision > fmt->n)
		fmt->len = fmt->precision ;
	if (fmt->isneg || check_flags(fmt, PLUS) || check_flags(fmt, SPACE))
		fmt->len++;
	if ((check_flags(fmt, HASH) && res && ft_strchr("xX", fmt->spec))
		|| fmt->spec == 'p')
		fmt->len += 2;
	if (check_flags(fmt, MINUS)
		|| (!fmt->precision & !res && !check_flags(fmt, PLUS)))
		just_left(res, base_s, fmt);
	else
		just_right(res, base_s, fmt);
	return (1);
}
