/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maprunty <maprunty@student.42heilbronn.de  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/11 18:26:36 by maprunty          #+#    #+#             */
/*   Updated: 2025/11/17 13:12:40 by maprunty         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_render(t_format *fmt)
{
	unsigned char	chr[2];

	ft_bzero(chr, 2);
	if (fmt->spec == '%' && !APPLE)
		return (ft_putchar_fd_count('%', FD, &fmt->count), 1);
	if (ft_strchr("cs%", fmt->spec))
		ft_render_chars(fmt, NULL, chr);
	else if (ft_strchr("pdiuxX", fmt->spec))
		ft_render_nums(fmt);
	return (0);
}

void	ft_init_format(t_format *fmt, const char *f_str)
{
	fmt->str = ++f_str;
	ft_memset(fmt->flags, '\0', 5 * sizeof(t_flag));
	fmt->len = 0;
	fmt->isneg = 0;
	fmt->width = 0;
	fmt->precision = -1;
	fmt->count = 0;
	fmt->spec = '\0';
}

int	ft_printf(const char *f_str, ...)
{
	int			count;
	t_format	*fmt;

	count = 0;
	fmt = (t_format *)malloc(sizeof(t_format));
	if (!fmt)
		return (0);
	va_start(fmt->ap, f_str);
	while (*f_str)
	{
		if (*f_str == '%')
		{
			ft_init_format(fmt, f_str);
			ft_parse(fmt);
			f_str += fmt->count;
			fmt->count = 0;
			if (fmt->spec)
				ft_render(fmt);
			count += fmt->count;
		}
		if (*f_str && *f_str != '%')
			ft_putchar_fd_count(*f_str++, FD, &count);
	}
	va_end(fmt->ap);
	return (free(fmt), count);
}
