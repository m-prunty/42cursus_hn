/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_help.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maprunty <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/01 10:28:09 by maprunty          #+#    #+#             */
/*   Updated: 2025/12/05 01:00:17 by maprunty         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	ft_putchar(char c)
{
	write(1, &c, 1);
}

void	ft_putstr(char *str)
{
	while (*str)
		ft_putchar_fd(*str++, 1);
}


int	ft_strcmp(void *str1, void *str2)
{
	char *s1;
	char *s2;
	int	i;

	s1 =(char *)str1;
	s2 =(char *)str2;
	i = -1;
	while (s1[++i] || s2[i])
		if (s1[i] != s2[i])
			return ((int)s1[i] - (int)s2[i]);
	return (0);
}
