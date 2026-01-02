/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   btree_create_node.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maprunty <maprunty@student.42heilbronn.de  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/02 16:49:11 by maprunty          #+#    #+#             */
/*   Updated: 2025/09/02 16:49:14 by maprunty         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_btree.h"

t_btree	*btree_create_node(void *item)
{
	t_btree	*bt;

	bt = (t_btree *)malloc(sizeof(t_btree));
	if (!bt || !item)
		return (NULL);
	bt->data = item;
	bt->left = NULL;
	bt->right = NULL;
	return (bt);
}
