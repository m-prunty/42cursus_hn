/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maprunty <maprunty@student.42heilbronn.de  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/11 18:26:36 by maprunty          #+#    #+#             */
/*   Updated: 2025/09/13 21:11:03 by maprunty         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void ft_parse_len(t_format *fmt)
{
	fmt->str++;
	fmt->count++;
}

void	ft_init_format(t_format *fmt, const char* f_str )
{
	int i;
	//	char *spec;
	//	char *nxt_pcent;

	i = -1;
	fmt->str = ++f_str;
	/*
		* spec = ft_strchrstr(f_str, SPECIFIER);
	nxt_pcent = ft_strchr(f_str, '%');
	if (!spec || nxt_pcent < spec)
		fmt->spec = '\0';
	else
		fmt->spec = *spec;
	*/
	while (fmt->flags[++i])
		fmt->flags[i] = 0;
	fmt->width = 0;
	fmt->precision = -1;
	fmt->lenmod = 0;
	fmt->count = 0;
	fmt->spec = '\0';
	//if (fmt->spec)
	//		fmt->count += 2;

}

int	ft_printf(const char *f_str, ...)
{
	//va_list		ap;
	int			count;
	t_format	*fmt;

	count = 0;
	fmt = (t_format *)malloc(sizeof(t_format));
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
		}	
		//else
		ft_putchar_fd(*f_str++, FD);
		//f_str++;
	}
	va_end(fmt->ap);
	return (count);
}
