/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maprunty <maprunty@student.42heilbronn.de  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/02 16:50:45 by maprunty          #+#    #+#             */
/*   Updated: 2025/12/05 06:04:41 by maprunty         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	ft_isstr_numeric(char *str)
{
	while (*str)
	{
		if (ft_isdigit(*str))
			str++;
		else
			return (0);
	}
	return (1);
}

int	chk_input(char **strs)
{
	int i;

	i = 0;
	while (strs[i])
	{
		if (ft_isstr_numeric(strs[i]))
			i++;
		else
			return (-1);
	}
	return (i);
}

int	*ft_strstoiarr(char **strs,  int n)
{
	int	i;
	int *iarr;

	iarr = NULL;
	if (n >= 2)
	{
		iarr = (int *)ft_calloc(n, sizeof(int));
		if (!iarr)
			return (NULL);
		i = -1;
		while (++i < n)
			iarr[i] = ft_atoi(strs[i]); 
	}
	return (iarr);
}

typedef struct s_stack
{
	char	name;
	int		n;
	t_list	head;
	t_list	tail;
	t_btree root;
	
}	t_stack;

typedef struct s_element
{
	int		value;
	int		sort_loc;
}	t_element;


void	push_swap(int *iarr, int ac)
{
	int	i = 0;

	while (i < ac)
		ft_printf("%i", iarr[i++]);

}

t_stack		*init_stack(int *iarr, int n, char name)
{
	t_stack  stk;

	stk = NULL;
	while (*iarr)
}

int main(int ac, char **av)
{
	int	*iarr;

	if (ac > 1)
	{
		av++;
		if (ac == 2)
			av = ft_split(av[0], ' ');
		ac = chk_input(av);
		iarr = ft_strstoiarr(av, ac);
		if (iarr)
			push_swap(iarr, ac);
		else if (ac == -1)
			return (free(av), 0);
	}
	return (1);

}
/*
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
   btree_pprint(root);
   */
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
/*
   btree_apply_prefix(root, ft_putstr);
   ft_printf("\n");
   btree_apply_infix(root, ft_putstr);
   ft_printf("\n");
   btree_apply_suffix(root, ft_putstr);
   btree_insert_data(&node5, "4", ft_strcmp);
   btree_insert_data(&node5, "1", ft_strcmp);
   btree_insert_data(&node5, "9", ft_strcmp);
   btree_insert_data(&node5, "1", ft_strcmp);
   btree_insert_data(&node5, "6", ft_strcmp);
   btree_insert_data(&node5, "4", ft_strcmp);
   btree_insert_data(&node5, "4", ft_strcmp);
   btree_insert_data(&node5, "9", ft_strcmp);
   btree_insert_data(&node5, "4", ft_strcmp);
   btree_insert_data(&node5, "1", ft_strcmp);
   btree_insert_data(&node5, "7", ft_strcmp);
   btree_insert_data(&node5, "-9", ft_strcmp);
   btree_insert_data(&node5, "1", ft_strcmp);
   btree_insert_data(&node5, "1", ft_strcmp);
   btree_insert_data(&node5, "1", ft_strcmp);
   btree_insert_data(&node5, "1", ft_strcmp);
   btree_insert_data(&node5, "0", ft_strcmp);
   btree_insert_data(&node5, "7", ft_strcmp);
   btree_insert_data(&node5, "0", ft_strcmp);
   ft_printf("\n");
   btree_apply_infix(node5, ft_putstr);
   ft_printf("\n");
   btree_apply_infix((btree_search_item(node5, "6", ft_strcmp)), ft_putstr);
   ft_printf("\n");
   t_list *lst;
   lst = ft_lstnew(node1);
//ft_printf("%i", btree_level_count(node5));
btree_apply_by_level(node5, applyf);
//	btree_pprint(node5);
}
*/
