/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   btree_level_count.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maprunty <maprunty@student.42heilbronn.de  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/02 16:50:25 by maprunty          #+#    #+#             */
/*   Updated: 2025/09/02 16:50:28 by maprunty         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_btree.h"

int	btree_level_count(t_btree *root)
{
	int		li;
	int		ri;

	if (!root)
		return (0);
	li = btree_level_count(root->left);
	ri = btree_level_count(root->right);
	if (ri > li)
		return (++ri);
	return (++li);
}
