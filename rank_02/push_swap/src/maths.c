/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   maths.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maprunty <maprunty@student.42heilbron      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/20 14:42:35 by maprunty          #+#    #+#             */
/*   Updated: 2025/12/20 15:27:10 by maprunty         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	log2n(int n)
{
	if (n > 1)
		return (1 + log2n(n / 2));
	return (0);
}

long	n_log_n(int n)
{
	if (n <= 1)
		return (0);
	return ((long)n * log2n(n));
}

int	ft_sqrt(int nb)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	if (nb == 1)
		return (1);
	if (nb > 2)
	{
		while (nb > 0 && (j++ + ++i))
			nb -= (i++);
	}
	return (j);
}
