/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   swap.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maprunty <maprunty@student.42heilbronn.de  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/12 02:05:34 by maprunty          #+#    #+#             */
/*   Updated: 2025/12/12 02:07:06 by maprunty         ###   ########.fr       */
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

int	s(t_stack *stk)
{
	if (swap(stk))
		return (ft_printf("s%c\n", (stk)->name));
	ft_printf("error: s%c\n", (stk)->name);
	return (0);
}
