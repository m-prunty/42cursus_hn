/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   platform_dependent.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maprunty <maprunty@student.42heilbron      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/15 23:35:33 by maprunty          #+#    #+#             */
/*   Updated: 2025/11/15 23:36:24 by maprunty         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

#if __APPLE__

unsigned long long	get_value(t_format *fmt)
{
	unsigned long long	res;

	if (ft_strchr("id", fmt->spec))
		res = va_arg(fmt->ap, int);
	else if (ft_strchr("uxX", fmt->spec))
		res = va_arg(fmt->ap, unsigned int);
	if (fmt->spec == 'p')
	{
		res = (unsigned long long)va_arg(fmt->ap, void *);
	}
	return (res);
}

int	if_apple(t_format *fmt)
{
	return (1);
}

#else

unsigned long long	get_value(t_format *fmt)
{
	unsigned long long	res;

	if (ft_strchr("id", fmt->spec))
		res = va_arg(fmt->ap, int);
	else if (ft_strchr("uxX", fmt->spec))
		res = va_arg(fmt->ap, unsigned int);
	if (fmt->spec == 'p')
	{
		res = (unsigned long long)va_arg(fmt->ap, void *);
		if (!res)
			return (ft_render_chars(fmt), 0);
	}
	return (res);
}

int	if_apple(t_format *fmt)
{
	if (fmt->precision < 0 || fmt->precision >= 6)
		return (1);
	return (0);
}

#endif
