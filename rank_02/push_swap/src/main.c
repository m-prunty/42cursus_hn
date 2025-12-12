/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maprunty <maprunty@student.42heilbronn.de  +#+  +:+       +#+        */
	/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/02 16:50:45 by maprunty          #+#    #+#             */
/*   Updated: 2025/12/12 04:56:29 by maprunty         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	ft_isstr_numeric(char *str)
{
	if (*str == '-')
		str++;
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

int	ps_elecmp(void *ele1, void *ele2)
{
	int	i1;
	int	i2;
	
	i1 =((t_element *)ele1)->value;
	i2 =((t_element *)ele2)->value;
	return (i1 - i2);
}

void	ps_putnbr(t_element *ele)
{
	if (ele )
	{
	ft_putnbr_fd(ele->value, 1);
	ft_putstr_fd(", ", 1);
	ft_putnbr_fd(ele->sort, 1);
	ft_putstr_fd("\n", 1);
	}
}

void ps_print(t_stack stk)
{
	//if ()
	ft_printf("stack: %c\n", stk.name);
	ft_printf("disorder->>>%i\n", compute_disorder(&stk));
	ft_lstiter(stk.head, ps_putnbr);
	ft_putchar_fd('\n', 1);
	//btree_apply_infix(stk.root, ps_putnbr);
	ft_putchar_fd('\n', 1);
}

void	ps_apfcount(t_element *ele)
{
	static int	i = 0;

	i++;
	ele->sort = i;
}

int	ps_init_stacks(t_stack stks[2], t_element *elements, int n)
{
	t_list	*tmplst;
	int i;
	
	(stks)[a].name = 'a';
	(stks)[b].name = 'b';
	i = -1;
	while (++i < n)
	{
		tmplst = ft_lstnew(&elements[i]);
		ft_lstadd_back(&stks[a].head, tmplst);
		btree_insert_data(&stks[a].root, &elements[i], ps_elecmp);
	}
	btree_apply_infix(stks[a].root, ps_apfcount);
	stks[a].n = i;
}



int compute_disorder(t_stack *stk)
{
	t_list  *tmp;
	t_list  *nxt;
	int		mistakes;
	int		pairs;
	
	mistakes = 0;
	pairs = 0;
	tmp = stk->head;
	while (tmp)
	{
		nxt = tmp->next;
		while (nxt)
		{	
			pairs++;
			if (ps_elecmp(tmp->content, nxt->content) > 0)
				mistakes++;
			nxt = nxt->next;
		}
		tmp = tmp->next;
	}
	if (pairs)
		return ((mistakes * 100) / pairs);
	return (0);
}
int ps_issorted(t_stack *stk)
{	
	t_list	*lst;
	int		n;

	n = stk->n;
	lst = stk->head;
	while (lst && n--)
	{
		if (ps_lstcmp(lst, lst->next) > 0)
			return (0);
		lst = lst->next;
	}
	return (1);
		
}


t_list *get_max(t_stack *stk)
{
	t_list	*cur;
	t_list	*max;
	int		n;

	cur = stk->head;
	max = cur;
	n = stk->n;
	while (n)
	{
		if (ps_lstcmp(max, cur) > 0)
			max = cur;
		cur = cur->next;
	}
}
int		ps_lstcmp(t_list *lst1, t_list *lst2)
{
	if (lst1 && lst2)
		return (ps_elecmp(lst1->content, lst2->content));
}
/*
void	place_in_stk(t_stack *stk, t_list *to_place)
{
	t_list	*head;

	while (ps_lstcmp(ahead, bhead)  0)
}
*/
t_element *ps_lstele(t_list *lst)
{
	if (lst->content)
		return (lst->content);
	return (NULL);
}
int	n_sorted(t_stack stk)
{
	t_list	*lst;
	int		i;

	i = 0;
	lst = stk.head;
	while (lst)
	{
		if (ps_lstele(lst)->sorted)
			i++;
		lst = lst->next;
	}
	return (i);
}

void	bubble(t_stack **stks, int to)
{
	t_list	*s1;
	t_list	*s2;
	int		from;
	int		remain;

	from = (to + 1 ) % 2;
	s1 = (stks)[from]->head;

	s2 = NULL;
	if (*((stks)[to]))
		s2 = (stks)[to]->head;
	remain = (*stks)[from].n - n_sorted((*stks)[from]);
	while (s1 && remain > 0)
	{
		if (!(s2))
			p((*stks), to);
		else if (ps_lstele(s2)->sorted == 0)
		{
			if ((to % 2 && ps_lstcmp(s1, s2) >0 ))
			{
				p((*stks), to);
				r(&(*stks)[to]);
			}
			else if (!(to % 2) && ps_lstcmp(s1, s2) < 0 )
			{
						p((*stks), to);
						rr(&(*stks)[to]);
			}
			else
				p((*stks), to);
			}
		else
			r(&(*stks)[from]);
		remain = (*stks)[from].n - n_sorted((*stks)[from]);
		ft_printf(">>>%i %i \n", remain, 0-remain);
	}
	ps_lstele(s2)->sorted = ps_lstele(s2)->sort;
	//ft_printf("%i %i %n",(*stks)[from].n, (*stks)[to].n );	
	//p(stks, from);
	//r(&(*stks)[to % 2]);
}

void bubble_sort(t_stack *stks)
{
	int	n;
	int	i;
	int	to;


	n = (stks)[a].n;
	to = 0;
	while (++to < n )// && !ps_issorted(&(*stks)[a]))
	{
		bubble((&stks), to % 2);
		//r(&(*stks)[to % 2]);
		ps_print((stks)[a]);
		ps_print((stks)[b]);
	}

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
			return (0);
		ft_printf("disorder->>>%i\n", compute_disorder(&stks[a]));
	}
	ps_print(stks[a]);
	bubble_sort(&stks);
}
//ps_print(stks[a]);
//ps_print(stks[b]);
//	ft_lstrot(&stks[a].head, stks[a].n);
/*
   r(&stks[a]);
   ps_print(stks[a]);
   rr(&stks[a]);
   ps_print(stks[a]);
   r(&stks[a]);
   r(&stks[a]);
   r(&stks[a]);
   ps_print(stks[a]);
//rrs(&stks, 0);
//rrs(&stks, 1);
//ps_stkpop(&stks[a]);
ps_print(stks[a]);
p(stks, b);
p(stks, b);
p(stks, b);
ps_print(stks[b]);
ps_print(stks[a]);
p(stks, b);
p(stks, b);
p(stks, b);
ps_print(stks[b]);
ps_print(stks[a]);
s(&stks[b]);
ps_print(stks[b]);
p(stks, a);
p(stks, a);
s(&stks[a]);
ps_print(stks[b]);
ps_print(stks[a]);
return (1);
*/
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

