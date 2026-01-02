/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   btree_insert_data.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maprunty <maprunty@student.42heilbronn.de  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/02 16:49:50 by maprunty          #+#    #+#             */
/*   Updated: 2025/09/02 18:17:31 by maprunty         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_btree.h"

void	btree_insert_data(t_btree **root, void *item,
			int (*cmpf)(void *, void *))
{
	if (!root || !*root || !item)
	{
		if (item && root)
			(*root) = btree_create_node(item);
		return ;
	}
	if (cmpf(item, (*root)->data) < 0)
	{
		if ((*root)->left)
			btree_insert_data(&(*root)->left, item, cmpf);
		else
			(*root)->left = btree_create_node(item);
	}
	else
	{
		if ((*root)->right)
			btree_insert_data(&(*root)->right, item, cmpf);
		else
			(*root)->right = btree_create_node(item);
	}
}
