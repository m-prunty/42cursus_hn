/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotate.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maprunty <maprunty@student.42heilbronn.de  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/12 01:25:13 by maprunty          #+#    #+#             */
/*   Updated: 2025/12/12 01:25:52 by maprunty         ###   ########.fr       */
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

int rotate(t_stack *stk, int rev)
{
	if (!rev)
		return (ft_lstrot(&stk->head, stk->n));
	return (ft_lstrrot(&stk->head, stk->n));
}

int	r(t_stack *stk)
{
	if (rotate(stk, 0))
		return (ft_printf("r%c\n", (stk)->name));
	ft_printf("error; r%c\n", (stk)->name);
	return (0);
}


int	rr(t_stack *stk)
{
	if (rotate(stk, 1))
		return (ft_printf("rr%c\n", (stk)->name));
	ft_printf("error; rr%c\n", (stk)->name);
	return (0);
}
int	rrs(t_stack *stks, int rev)
{
	if (rotate(&stks[a], rev)  && rotate(&stks[b], rev))
		return (ft_printf("r%c%c\n", 'r' * rev, 'r'));
	ft_printf("error; r%c%c\n", 'r' * rev, 'r');
	return (0);
}
