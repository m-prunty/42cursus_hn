/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maprunty <maprunty@student.42heilbronn.de  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/11 18:26:36 by maprunty          #+#    #+#             */
/*   Updated: 2025/11/03 21:51:22 by maprunty         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void ft_parse_len(t_format *fmt)
{
	int n;

	n = 2;
	while (n-- && ft_strchr(LENMOD, *fmt->str))
	{
		fmt->str++;
		fmt->count++;
	}
}

void	ft_init_format(t_format *fmt, const char* f_str )
{
	//int i;

	//i = -1;
	fmt->str = ++f_str;
	ft_memset(fmt->flags, '\0', 5*sizeof(e_flag));
	//while (fmt->flags[++i])
	//	fmt->flags[i] = 0;
	fmt->width = 0;
	fmt->precision = -1;
	fmt->lenmod = 0;
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
	free(fmt);
	return (count);
}
