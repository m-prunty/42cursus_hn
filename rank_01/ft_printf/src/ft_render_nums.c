/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_render.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maprunty <maprunty@student.42heilbronn.de  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/11 18:54:21 by maprunty          #+#    #+#             */
/*   Updated: 2025/11/16 01:28:29 by maprunty         ###   ########.fr       */
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

void	just_left(unsigned long long res, int len, char *base_s, t_format *fmt)
{
	handle_sym(fmt);
	handle_hash(fmt, res);
	handle_precis(fmt, res);
	if (fmt->spec == 'p')
		ft_putnbr_ptr(res, fmt);
	else if (fmt->n)
		ft_putnbr_base_fmt(res, base_s, fmt);
	print_space(fmt->width - len, &fmt->count);
}

void	just_right(unsigned long long res, int len, char *base_s, t_format *fmt)
{
	if (!check_flags(fmt, ZERO) || fmt->precision >= 0)
		print_space(fmt->width - len, &fmt->count);
	handle_sym(fmt);
	handle_hash(fmt, res);
	if (check_flags(fmt, ZERO) && fmt->precision < 0)
		handle_zero(fmt);
	else
		handle_precis(fmt, res);
	if (fmt->spec == 'p')
		ft_putnbr_ptr(res, fmt);
	else if (fmt->n)
		ft_putnbr_base_fmt(res, base_s, fmt);
}

int	ft_render_nums(t_format *fmt)
{
	unsigned long long	res;
	char				base_s[17];
	int					len;

	len = 0;
	res = get_value(fmt);
	if (fmt->spec == 'p' && !res)
		return (1);
	if (fmt->spec == 'p')
		len += 2;
	if (ft_strchr("id", fmt->spec) && (int)res < 0)
		fmt->isneg = 1;
	get_base(fmt, base_s);
	fmt->n = ft_count_digits_base(res, ft_strlen(base_s), fmt);
	len += fmt->n;
	if (fmt->precision > fmt->n)
		len = fmt->precision;
	if (fmt->isneg || check_flags(fmt, PLUS) || check_flags(fmt, SPACE))
		len++;
	if (check_flags(fmt, MINUS) || (!fmt->precision && !res))
		just_left(res, len, base_s, fmt);
	else
		just_right(res, len, base_s, fmt);
	return (1);
}
