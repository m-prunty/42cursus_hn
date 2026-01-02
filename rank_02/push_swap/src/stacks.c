/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stacks.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maprunty <maprunty@student.42heilbron      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/20 14:42:35 by maprunty          #+#    #+#             */
/*   Updated: 2025/12/20 15:31:07 by maprunty         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	compute_disorder(t_stack *stk)
{
	t_list	*tmp;
	t_list	*nxt;
	int		mistakes;
	int		pairs;

	mistakes = 0;
	pairs = 0;
	tmp = stk->head;
	while (tmp)
	{
		nxt = tmp->next;
		while (nxt)
		{
			pairs++;
			if (ps_elecmp(tmp->content, nxt->content) > 0)
				mistakes++;
			nxt = nxt->next;
		}
		tmp = tmp->next;
	}
	if (pairs)
		return ((mistakes * 100) / pairs);
	return (0);
}

int	ps_issorted(t_stack *stk)
{
	t_list	*lst;
	int		n;

	n = stk->n;
	lst = stk->head;
	while (lst && n--)
	{
		if (ps_lstcmp(lst, lst->next) > 0)
			return (0);
		lst = lst->next;
	}
	return (1);
}

t_list	*get_max(t_stack *stk)
{
	t_list	*cur;
	t_list	*max;
	int		n;

	cur = stk->head;
	max = cur;
	n = stk->n;
	while (n--)
	{
		if (ps_lstcmp(cur, max) > 0)
			max = cur;
		cur = cur->next;
	}
	return (max);
}

t_list	*get_min(t_stack *stk)
{
	t_list	*cur;
	t_list	*min;
	int		n;

	cur = stk->head;
	min = cur;
	n = stk->n;
	while (n--)
	{
		if (ps_lstcmp(cur, min) < 0)
			min = cur;
		cur = cur->next;
	}
	return (min);
}

t_ps	*set_curstk(t_ps *ps, int stk)
{
	ps->curstk = stk;
	return (ps);
}
