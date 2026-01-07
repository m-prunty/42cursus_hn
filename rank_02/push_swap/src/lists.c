/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lists.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maprunty <maprunty@student.42heilbron      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/20 14:42:35 by maprunty          #+#    #+#             */
/*   Updated: 2026/01/07 15:20:12 by maprunty         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	ps_lstcmp(t_list *lst1, t_list *lst2)
{

	return (ps_lstele(lst1)->sort - ps_lstele(lst2)->sort);
	// if (lst1 && lst2)
	//	return (ps_elecmp(lst1->content, lst2->content));
	// return (0);
}

t_element	*ps_lstele(t_list *lst)
{
	if (lst->content)
		return ((t_element *)lst->content);
	return (NULL);
}
