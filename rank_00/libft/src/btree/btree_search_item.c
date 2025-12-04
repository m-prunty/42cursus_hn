/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   btree_search_item.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maprunty <maprunty@student.42heilbronn.de  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/02 16:50:04 by maprunty          #+#    #+#             */
/*   Updated: 2025/09/02 18:15:35 by maprunty         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_btree.h"

void	*btree_search_item(t_btree *root, void *data_ref,
			int (*cmpf)(void *, void *))
{
	int	cmp;

	cmp = cmpf(data_ref, (root)->data);
	if (!root || cmp == 0)
		return (root);
	else if (cmp > 0)
		return (btree_search_item(root->right, data_ref, cmpf));
	else if (cmp < 0)
		return (btree_search_item(root->left, data_ref, cmpf));
	return (NULL);
}
