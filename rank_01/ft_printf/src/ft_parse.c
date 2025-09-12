/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maprunty <maprunty@student.42heilbronn.de  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/11 18:42:37 by maprunty          #+#    #+#             */
/*   Updated: 2025/09/12 17:05:34 by maprunty         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void ft_parse_flags(t_format *fmt)
{
	int	i;

	i = -1;
	while (fmt->flags[++i])
		;
	fmt->flags[i]  = *fmt->str;
	fmt->str++;
	fmt->count++;
}

void ft_parse_width(t_format *fmt)
{
	while (ft_isdigit(*fmt->str))
	{
		fmt->width = fmt->width * 10 + (*fmt->str - '0');
		fmt->str++;
		fmt->count++;
	}
}

void ft_parse_precis(t_format *fmt)
{
	fmt->precision = 0;
	fmt->count++;
	while (ft_isdigit(*++fmt->str))
	{
		fmt->precision = fmt->precision * 10 + (*fmt->str - '0');
		fmt->str++;
		fmt->count++;
	}
}


void ft_parse_spec(t_format *fmt)
{
	fmt->spec = *fmt->str;
	fmt->str++;
	fmt->count += 2;
}


int	ft_parse(t_format *fmt)
{
//	int	i;

	//	i = fmt_spec - specifier;
	//	while (*fmt->str && !fmt->spec)
	//	{
	while (ft_strchr(FLAGS, *fmt->str))
		ft_parse_flags(fmt);
	if (*fmt->str != '0' && (ft_isdigit(*fmt->str) || *fmt->str == '*'))
		ft_parse_width(fmt);
	if (*fmt->str == '.')
		ft_parse_precis(fmt);
	if (ft_strchr(LENMOD, *fmt->str))
		ft_parse_len(fmt);
	if (ft_strchr(SPECIFIER, *fmt->str))
		ft_parse_spec(fmt);
	//fmt->str++;
	if (!fmt->spec)
		fmt->count = 0;
	//	}	
	return (0);
}
