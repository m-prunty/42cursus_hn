/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   btree_apply_by_level.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maprunty <maprunty@student.42heilbronn.de  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/02 16:50:34 by maprunty          #+#    #+#             */
/*   Updated: 2025/09/03 00:56:30 by maprunty         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_btree.h" 

void	ft_list_push_back(t_list **begin_list, void *data)
{
	if (*begin_list)
		ft_lstlast(*begin_list)->next = ft_lstnew(data);
	else
		*begin_list = ft_lstnew(data);
}

void	btree_level_list(t_btree *root, int level, t_list **lst)
{
	if (!root)
		return ;
	ft_list_push_back(&(lst[level]), root);
	btree_level_list(root->left, level + 1, lst);
	btree_level_list(root->right, level + 1, lst);
}

void	ft_list_foreach_level(t_list *begin_list, int level,
		void (*applyf)(void *data, int level, int is_first_elem ))
{
	int		is_first;

	is_first = 1;
	while (begin_list)
	{
		applyf(((t_btree *)begin_list->content)->data, level, is_first);
		begin_list = begin_list->next;
		is_first = 0;
	}
}

void	btree_apply_by_level(t_btree *root,
		void (*applyf)(void *item, int current_level, int is_first_elem))
{
	t_list	**lst;
	int		levels;
	int		i;

	levels = btree_level_count(root);
	lst = (t_list **)malloc(sizeof(t_list *) * (levels + 1));
	if (!lst)
		return ;
	i = -1;
	while (++i < levels)
		lst[i] = NULL;
	btree_level_list(root, 0, lst);
	i = -1;
	while (lst[++i])
	{
		ft_list_foreach_level(lst[i], i, applyf);
	}
}
