/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotate.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maprunty <maprunty@student.42heilbronn.de  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/12 01:25:13 by maprunty          #+#    #+#             */
/*   Updated: 2025/12/18 20:09:44 by maprunty         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	ft_lstrrot(t_list **lst, int n)
{	
	t_list	*newtail;
	t_list	*newhead;

	if (lst && n > 2)
	{
		newtail = ft_lstgoto(*lst, n - 2);
		newhead = newtail->next;
		newtail->next = NULL;
		newhead->next = *lst;
		*lst = newhead;
		if (ft_lstsize(*lst) == n)
			return (1);
	}
	return (0);
}

int	ft_lstrot(t_list **lst, int n)
{	
	t_list	*newtail;
	t_list	*newhead;

	if (*lst && n >= 2)
	{
		newtail = *lst;
		newhead = newtail->next;
		ft_lstgoto(*lst, n - 1)->next = newtail;
		newtail->next = NULL;
		*lst = newhead;
		if (ft_lstsize(*lst) == n)
			return (1);
	}
	return (0);
}

int	rotate(t_stack *stk, int rev)
{
	if (!rev)
		return (ft_lstrot(&stk->head, stk->n));
	return (ft_lstrrot(&stk->head, stk->n));
}

int	r(t_ps *ps)
{
	if (rotate(&ps->stks[ps->curstk], 0))
	{
		ps->count.r[ps->curstk] += 1;
		ps->count.tot += 1;
		return (ft_printf_fd(ps->fd, "r%c\n", ps->stks[ps->curstk].name));
	}
	ft_printf_fd(2, "error; r%c\n", ps->stks->name);
	return (0);
}

int	rr(t_ps *ps)
{
	if (rotate(&ps->stks[ps->curstk], 1))
	{
		ps->count.rr[ps->curstk] += 1;
		ps->count.tot += 1;
		return (ft_printf_fd(ps->fd, "rr%c\n", ps->stks[ps->curstk].name));
	}
	ft_printf_fd(2, "error; rr%c\n", ps->stks->name);
	return (0);
}

int	rrs(t_ps *ps, int rev)
{
	if (rotate(&ps->stks[ps->curstk], rev)
		&& rotate(&ps->stks[ps->curstk], rev))
	{
		ps->count.rrs[rev] += 1;
		ps->count.tot += 1;
		return (ft_printf_fd(ps->fd, "r%c%c\n", 'r' * rev, 'r'));
	}
	ft_printf_fd(2, "error; r%c%c\n", 'r' * rev, 'r');
	return (0);
}
