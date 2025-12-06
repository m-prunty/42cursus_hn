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
	t_list	*head;
	t_list	*tail;
	t_btree *root;
	
}	t_stack;

typedef struct s_element
{
	int		value;
	int		sort;
}	t_element;


void	push_swap(int *iarr, int ac)
{
	int	i = 0;

	while (i < ac)
		ft_printf("%i", iarr[i++]);

}

t_element	*ps_elenew(int value)
{
	t_element *element;

	element = (t_element *)ft_calloc(1, sizeof(t_element));
	if (!element)
		return (NULL);
	element->value = value;
	return (element);
}

t_element		*ps_getelements(int *iarr, int n, char name)
{
	int			i;
	t_stack		*stk;
	t_element	*elements;

	stk = NULL;
	i = -1;
	elements = (t_element *)ft_calloc(n, sizeof(t_element *));
	while (iarr[++i])
		elements[i] = *ps_elenew(iarr[i]);
	return (elements);
}

int	ps_elecmp(void *str1, void *str2)
{
	int	s1;
	int	s2;
	
	s1 =((t_element *)str1)->value;
	s2 =((t_element *)str2)->value;
	return ((int)s1 - (int)s2);
}

void	ps_putnbr(t_element *ele)
{
	ft_putnbr_fd(ele->value, 1);
	ft_putstr_fd(", ", 1);
	ft_putnbr_fd(ele->sort, 1);
	ft_putstr_fd("\n", 1);
}

void ps_print(t_stack stk)
{
	ft_lstiter(stk.head, ps_putnbr);
	ft_putchar_fd('\n', 1);
	btree_apply_infix(stk.root, ps_putnbr);
	ft_putchar_fd('\n', 1);
}

int	ps_init_stacks(t_stack stks[2], t_element *elements, int n)
{
	//t_stack *tmp_a;
	t_list	*tmplst;
	int i;
	
	//*stks = (t_stack *)ft_calloc(sizeof(t_stack), 2);
	(stks)[0].name = 'a';
	(stks)[1].name = 'b';
	i = -1;
	while (++i < n)
	{
		tmplst = ft_lstnew(&elements[i]);
		ft_lstadd_back(&stks[0].head, tmplst);
		btree_insert_data(&stks[0].root, &elements[i], ps_elecmp);
	}
	stks[0].n = i;
}

int main(int ac, char **av)
{
	int			*iarr;
	t_stack		stks[2];
	t_element	*elements;

	ft_bzero(stks, sizeof(stks));
	if (ac > 1)
	{
		av++;
		if (ac == 2)
			av = ft_split(av[0], ' ');
		ac = chk_input(av);
		iarr = ft_strstoiarr(av, ac);
		if (iarr)
		{
			elements = ps_getelements(iarr, ac, 'a');
			if (!elements)
				return (free(av), 0);
		}
		else if (ac == -1)
			return (free(av), 0);
		if (!ps_init_stacks(stks, elements, ac))
			return (NULL);
	}
	ps_print(stks[0]);
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
