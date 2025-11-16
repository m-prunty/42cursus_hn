/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maprunty <maprunty@student.42heilbronn.de  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/11 18:54:07 by maprunty          #+#    #+#             */
/*   Updated: 2025/11/16 01:06:14 by maprunty         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_putchar_fd_count(char c, int fd, int *count)
{
	*count += write(fd, &c, 1);
}

int	check_flags(t_format *fmt, e_flag f)
{
	int	i;

	i = -1;
	while (fmt->flags[++i])
		if (fmt->flags[i] == f)
			return (1);
	return (0);
}

int	print_space(int n, int *count)
{
	int	i;

	i = -1;
	while (++i < n)
		ft_putchar_fd_count(' ', FD, count);
	return (i);
}

void	ft_iter_up(unsigned int i, char *c)
{
	(void)i;
	if (ft_islower(*c))
		*c = *c - 32;
}
