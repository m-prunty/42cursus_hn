/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maprunty <maprunty@student.42heilbron      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/20 14:42:35 by maprunty          #+#    #+#             */
/*   Updated: 2025/12/20 15:32:36 by maprunty         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	process_flag(t_ps *ps, char *flag)
{
	while (*flag == '-')
		++flag;
	if (!ps->flags[0] && (*flag == BUBBLE || *flag == RADIX || *flag == K_SORT))
		ps->flags[0] = *flag;
	else if (!ps->flags[1] && *flag == BENCH)
		ps->flags[1] = *flag;
}

int	chk_input(char **strs)
{
	int	i;

	i = 0;
	while (strs[i])
	{
		if (ft_isstr_numeric(strs[i]))
			i++;
		else
			return (-1);
	}
	return (i);
}

int	ft_isstr_numeric(char *str)
{
	if (*str == '-')
		str++;
	while (*str)
	{
		if (ft_isdigit(*str))
			str++;
		else
			return (0);
	}
	return (1);
}
