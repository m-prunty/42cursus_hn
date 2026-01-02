/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   elements.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maprunty <maprunty@student.42heilbron      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/20 14:42:35 by maprunty          #+#    #+#             */
/*   Updated: 2026/01/02 02:03:00 by maprunty         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

t_element	ps_elenew(int value)
{
	t_element	element;

	element.value = value;
	return (element);
}

t_element	*ps_getelements(int *iarr, int n)
{
	int			i;
	t_element	*elements;

	i = -1;
	elements = (t_element *)ft_calloc(n, sizeof(t_element));
	if (!elements)
		return (NULL);
	while (++i < n)
		elements[i] = ps_elenew(iarr[i]);
	return (elements);
}

int	ps_elecmp(void *ele1, void *ele2)
{
	int	i1;
	int	i2;

	i1 = ((t_element *)ele1)->value;
	i2 = ((t_element *)ele2)->value;
	return (i1 - i2);
}

void	ps_apfcount(void *e)
{
	t_element	*ele;
	static int	i = 0;

	ele = (t_element *)e;
	i++;
	ele->sort = i;
}
