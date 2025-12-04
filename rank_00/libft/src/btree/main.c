/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maprunty <maprunty@student.42heilbronn.de  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/02 16:50:45 by maprunty          #+#    #+#             */
/*   Updated: 2025/09/02 17:00:05 by maprunty         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_btree.h"

int	main()
{
	t_btree *node1 = btree_create_node("1");
	t_btree *node2 = btree_create_node("2");
	t_btree	*node3 = btree_create_node("3");
	t_btree *node4 = btree_create_node("4");
	t_btree *node5 = btree_create_node("5");
	t_btree *node6 = btree_create_node("6");
	t_btree *node7 = btree_create_node("7");
	t_btree *node8 = btree_create_node("8");

	t_btree	*root = btree_create_node("1");
	root->left = btree_create_node("2");
	root->right = btree_create_node("3");
	root->left->left = btree_create_node("4");
	root->left->right = btree_create_node("5");
	root->right->right = btree_create_node("6");
	/*
	node1->left = node2;
	node1->right = node3;

	node2->left = node4;
	node2->right = node5;

	node3->left = node6;
	node3->right = node7;

	node4->left = node8;
	node4->right = NULL;
*/
	btree_apply_prefix(root, ft_putstr);
	ft_putstr("\n");
	btree_apply_infix(root, ft_putstr);
	ft_putstr("\n");
	btree_apply_suffix(root, ft_putstr);
	/*
		char i;

		i = 47;
		while (++i < '9')
		{

			btree_insert_data(&node5, (char *)&i, ft_strcmp);
		}
*/
	btree_insert_data(&node5, "1", ft_strcmp);
	btree_insert_data(&node5, "4", ft_strcmp);
	btree_insert_data(&node5, "1", ft_strcmp);
	btree_insert_data(&node5, "1", ft_strcmp);
	btree_insert_data(&node5, "6", ft_strcmp);
	btree_insert_data(&node5, "4", ft_strcmp);
	btree_insert_data(&node5, "4", ft_strcmp);
	btree_insert_data(&node5, "9", ft_strcmp);
	btree_insert_data(&node5, "4", ft_strcmp);
	btree_insert_data(&node5, "9", ft_strcmp);
	btree_insert_data(&node5, "7", ft_strcmp);
	ft_putstr("\n");
	btree_apply_infix(node5, ft_putstr);
	ft_putstr("\n");
	btree_apply_infix((btree_search_item(node5, "6", ft_strcmp)), ft_putstr);
	ft_putstr("\n");
	t_list *lst;
	lst = ft_create_elem(node1);
	ft_putnbr(btree_level_count(node5));
	btree_apply_by_level(node5, applyf);
	btree_pprint(node5);
}
