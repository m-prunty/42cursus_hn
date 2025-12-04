/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   misc.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maprunty <maprunty@student.42heilbronn.de  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/02 16:50:53 by maprunty          #+#    #+#             */
/*   Updated: 2025/09/02 16:57:43 by maprunty         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_btree.h"

void	btree_pprint_help(void *item, int current_level,
				int is_first_elem, int n_levels)
{
	if (is_first_elem)
	{
		ft_putstr("\nLevel ");
		ft_putnbr(current_level);
		ft_putstr(": ");
		while (n_levels--)
			ft_putstr("    ");
		if (current_level % 2)
			ft_putstr("  ");
	}
	if (item)
		ft_putstr((char *)((t_btree *)item)->data);
	ft_putstr(",    ");
}

void	btree_level_list_null(t_btree *root, int level, t_list **lst)
{
	ft_list_push_back(&(lst[level]), root);
	if (!root)
		return ;
	btree_level_list_null(root->left, level + 1, lst);
	btree_level_list_null(root->right, level + 1, lst);
}

void	btree_pprint(t_btree *root)
{
	t_list	**lst;
	t_list	*cur;
	int		levels;
	int		i;
	int		is_first;

	levels = btree_level_count(root) + 1;
	lst = (t_list **)malloc(sizeof(t_list *) * (levels));
	if (!lst)
		return ;
	i = -1;
	while (++i < levels)
		lst[i] = NULL;
	btree_level_list(root, 0, lst);
	i = -1;
	while (lst[++i] && --levels)
	{
		cur = lst[i];
		is_first = 1;
		while (cur)
		{
			btree_pprint_help(((t_btree *)cur->data), i, is_first, levels);
			cur = cur->next;
			is_first = 0;
		}
	}
}

void	applyf(void *item, int level, int is_first)
{
	if (is_first)
	{
		ft_putstr("\nLevel ");
		ft_putnbr(level);
		ft_putstr(": ");
	}
	ft_putstr((char *)item);
	ft_putstr(",");
/*
	ft_putstr("Level "); 
	ft_putnbr(level);
	ft_putstr(": "); 
	ft_putnum(is_first); 
	ft_putstr(": "); 
	ft_putstr((char *)item);
	ft_putstr("\n"); 
*/
	//*(char *)item += level;
}
