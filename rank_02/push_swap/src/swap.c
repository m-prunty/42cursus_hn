/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   swap.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maprunty <maprunty@student.42heilbronn.de  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/12 02:05:34 by maprunty          #+#    #+#             */
/*   Updated: 2025/12/14 11:01:03 by maprunty         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	ft_lstswap(t_list **lst)
{
	t_list	*next;

	if (*lst && (*lst)->next)
	{
		next = (*lst)->next;
		(*lst)->next = next->next;
		next->next = *lst;
		*lst = next;
		return (1);
	}
	return (0);
}

int	swap(t_stack *stk)
{
	if (stk)
		return (ft_lstswap(&stk->head));
	return (0);	
}

int	s(t_ps *ps)
{
	if (swap(&ps->stks[ps->curstk]))
	{
		ps->count.s[ps->curstk] += 1;
		ps->count.tot += 1;
		return (ft_printf_fd(ps->fd, "s%c\n", ps->stks->name));
	}
	ft_printf_fd(2, "error: s%c\n", ps->stks->name);
	return (0);
}
