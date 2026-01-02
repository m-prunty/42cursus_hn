/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rrot.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maprunty <maprunty@student.42heilbron      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/20 14:13:13 by maprunty          #+#    #+#             */
/*   Updated: 2025/12/20 14:13:47 by maprunty         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

t_list	*ft_lstgoto(t_list *lst, int idx)
{
	if (idx < 0 || !lst)
		return (NULL);
	if (idx)
		return (ft_lstgoto(lst->next, --idx));
	return (lst);
}

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
