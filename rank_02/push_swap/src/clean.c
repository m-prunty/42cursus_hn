/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maprunty <maprunty@student.42heilbron      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/20 14:42:35 by maprunty          #+#    #+#             */
/*   Updated: 2026/01/01 23:15:58 by maprunty         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	ft_free_list(t_list *lst)
{
	t_list	*tmp;

	while (lst)
	{
		tmp = lst->next;
		free(lst);
		lst = tmp;
	}
}

void	ft_free_btree(t_btree *root)
{
	if (!root)
		return ;
	ft_free_btree(root->right);
	ft_free_btree(root->left);
	free(root);
}

void	ft_free_strs(char **strs)
{
	int	i;

	if (!strs)
		return ;
	i = 0;
	while (strs[i])
		free(strs[i++]);
	free(strs);
}

void	ft_free_stack(t_stack *stk)
{
	if (!stk)
		return ;
	if (stk->head)
	{
		ft_free_list(stk->head);
		stk->head = NULL;
	}
	if (stk->root)
	{
		ft_free_btree(stk->root);
		stk->root = NULL;
	}
}

void	close_ps(t_ps *ps, int err)
{
	int	i;

	i = 0;
	while (i <= B)
		ft_free_stack(&ps->stks[i++]);
	if (ps->elements)
	{
		free(ps->elements);
		ps->elements = NULL;
	}
	if (err)
		ft_printf("error");
}
