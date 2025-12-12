/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maprunty <maprunty@student.42heilbronn.de  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/12 01:27:02 by maprunty          #+#    #+#             */
/*   Updated: 2025/12/12 03:15:57 by maprunty         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

t_list *ft_lstgoto(t_list *lst, int idx)
{
	if (idx < 0 || !lst)
		return (NULL);
	if (idx)
		return (ft_lstgoto(lst->next, --idx));
	return (lst);
}


t_list	*ft_lstpop(t_list **list)
{
	t_list	*next;
	t_list	*popd;

	popd = *list;
	if (popd) 
	{
		next = popd->next;
		popd->next = NULL;
		*list = next;
		return (popd);
	}
	return (NULL);
}

t_list	*ps_stkpop(t_stack *stk)
{
	t_list *popd;
	
	if (stk && stk->head)
	{
		if (stk->n--)
		{
			popd = ft_lstpop(&stk->head);
			if (!stk->n)
				stk->head = NULL;
			return (popd);
		}
	}
	return (NULL);
}

int	ps_stkpush(t_stack *stk, t_list *lst)
{
	if (stk && lst)
	{
		(ft_lstadd_front(&stk->head, lst));
		stk->n++;
		return (1);
	}
	return (0);
}

int	push(t_stack *stks, int stk_to)
{
	t_list *from;


	from = ps_stkpop(&stks[(stk_to + 1) % 2]);
	if (from)
		return (ps_stkpush(&stks[stk_to], from));
	return (0);
}

int	p(t_stack *stks, int stk_to)
{
	if (push(stks, stk_to))
		return (ft_printf("p%c\n", (stks)[stk_to].name));
	ft_printf("error: p%c\n", (stks)[stk_to].name);
	return (0);
}
