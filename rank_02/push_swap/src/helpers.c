/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maprunty <maprunty@student.42heilbron      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/20 14:42:35 by maprunty          #+#    #+#             */
/*   Updated: 2025/12/20 15:30:18 by maprunty         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	ps_update_idx(t_stack *stk)
{
	t_list	*lst;
	int		i;

	i = 0;
	lst = stk->head;
	while (lst)
	{
		if (i > stk->n / 2)
			ps_lstele(lst)->idx = i - stk->n;
		else
			ps_lstele(lst)->idx = i;
		lst = lst->next;
		i++;
	}
}

void	ps_three_sort(t_ps *ps)
{
	t_list	**lst;

	lst = &ps->stks->head;
	if (ps_lstcmp(*lst, get_max(ps->stks)) == 0)
		r(ps);
	else if (ps_lstcmp((*lst)->next, get_max(ps->stks)) == 0)
		rr(ps);
	if (ps_lstcmp(*lst, (*lst)->next) > 0)
		s(ps);
}

t_list	*rotate_help(t_ps *ps, int n)
{
	if (n > 0)
		while (n--)
			r(ps);
	else
		while (n++)
			rr(ps);
	return (ps->stks->head);
}

void	ps_five_sort(t_ps *ps)
{
	int		from;
	int		pushed;

	from = ps->curstk;
	pushed = 0;
	while (ps->stks[from].n > 3 && ++pushed)
	{
		ps_update_idx(&ps->stks[from]);
		rotate_help(set_curstk(ps, from),
			ps_lstele(get_min(&ps->stks[from]))->idx);
		p(ps, (from + 1) % 2);
	}
	ps_three_sort(set_curstk(ps, from));
	while (pushed--)
		p(ps, from);
}
