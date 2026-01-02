/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_render_chars.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maprunty <maprunty@student.42heilbron      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/16 00:55:12 by maprunty          #+#    #+#             */
/*   Updated: 2025/12/14 09:57:41 by maprunty         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_putstr_n_fd(char *s, int n, int fd, int *count)
{
	int	i;

	i = -1;
	while (++i < n)
		ft_putchar_fd_count(s[i], fd, count);
	return (i);
}

void	ft_putstr_fd_count(char *s, int fd, int *count)
{
	while (*s)
		ft_putchar_fd_count(*s++, fd, count);
}

size_t	ft_strlen_safe(const char *s)
{
	size_t	i;

	i = 0;
	while (s && *s++)
		i++;
	return (i);
}

int	ft_render_chars(t_format *fmt, unsigned char *s, unsigned char c[2])
{
	fmt->n = 1;
	if (fmt->spec == 'c')
	{
		c[0] = (unsigned char)va_arg(fmt->ap, int);
		s = c;
	}
	else if (fmt->spec == 's')
	{
		s = (unsigned char *)va_arg(fmt->ap, char *);
		if (!s && !check_flags(fmt, SPACE) && if_apple(fmt))
			s = (unsigned char *)"(null)";
		fmt->n = ft_strlen_safe((char *)s);
	}
	else if (fmt->spec == 'p')
	{
		s = (unsigned char *)"(nil)";
		fmt->n = ft_strlen_safe((char *)s);
		fmt->spec = 's';
	}
	else if (fmt->spec == '%')
		s = (unsigned char *)"%";
	handle_precis(fmt, 0);
	handle_width(fmt, !check_flags(fmt, MINUS));
	ft_putstr_n_fd((char *)s, fmt->n, fmt->fd, &fmt->count);
	return (handle_width(fmt, check_flags(fmt, MINUS)), 1);
}
