/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maprunty <maprunty@student.42heilbronn.de  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/02 16:50:45 by maprunty          #+#    #+#             */
/*   Updated: 2025/12/16 02:50:12 by maprunty         ###   ########.fr       */
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
	int	j;
	int	tmp;
	int *iarr;

	iarr = NULL;
	j = 0;
	tmp = 0;
	if (n >= 2)
	{
		iarr = (int *)ft_calloc(n, sizeof(int));
		if (!iarr)
			return (NULL);
		i = -1;
		while (++i < n)
		{
			tmp = ft_atoi(strs[i]);
			j = 0;
			while (j < i)
				if (iarr[j++] == tmp)
					return (NULL);
			iarr[i] = tmp;
		}
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
	while (++i < n)
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

void	ps_putele(t_element *ele)
{
	if (ele)
		ft_printf_fd(2, "%i, %i, %i\n", ele->value, ele->sort, ele->idx);
}

void	ps_putnbr(t_element *ele)
{
	if (ele)
		ft_printf_fd(2, "%i ", ele->value);
}

void ps_print(t_ps *ps)
{
	int i;
	t_stack stk;

	i = -1;
	while (++i < 2)
	{
		stk = ps->stks[i];
		if (stk.n)
		{
			ft_printf_fd(2, "stack: %c\n", stk.name);
			ft_lstiter(stk.head, ps_putele);
			//ft_lstiter(stk.head, ps_putnbr);
			ft_printf_fd(2, "disorder->>>%i\n", compute_disorder(&stk));
		}
	}
	//ft_putchar_fd('\n', 1);
	//btree_apply_infix(stk.root, ps_putnbr);
	//ft_putchar_fd('\n', 1);
}

void	ps_apfcount(t_element *ele)
{
	static int	i = 0;

	i++;
	ele->sort = i;
}

int	ps_init_stacks(t_ps *ps, int n)
{
	t_list	*tmplst;
	int i;

	ps->stks[A].name = 'a';
	ps->stks[B].name = 'b';
	i = -1;
	while (++i < n)
	{
		tmplst = ft_lstnew(&ps->elements[i]);
		ft_lstadd_back(&ps->stks[A].head, tmplst);
		btree_insert_data(&ps->stks[A].root, &ps->elements[i], ps_elecmp);
	}
	btree_apply_infix(ps->stks[A].root, ps_apfcount);
	ft_lstiter(ps->stks[A].head, ps_putnbr);
	ft_printf_fd(2, "\n");
	ps->stks[A].n = i;
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
	while (n--)
	{
		if (ps_lstcmp(cur, max) > 0)
			max = cur;
		cur = cur->next;
	}
	return (max);
}

t_list *get_min(t_stack *stk)
{
	t_list	*cur;
	t_list	*min;
	int		n;

	cur = stk->head;
	min = cur;
	n = stk->n;
	while (n--)
	{
		if (ps_lstcmp(cur, min) < 0)
			min = cur;
		cur = cur->next;
	}
	return (min);
}

int		ps_lstcmp(t_list *lst1, t_list *lst2)
{
	if (lst1 && lst2)
		return (ps_elecmp(lst1->content, lst2->content));
}

t_ps	*set_curstk(t_ps *ps, int stk)
{
	ps->curstk = stk;
	return (ps);
}

t_element *ps_lstele(t_list *lst)
{
	if (lst->content)
		return ((t_element *)lst->content);
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

void bubble_sort(t_ps *ps)
{
	int	n;
	t_list	**lst;

	lst = &ps->stks[A].head;
	while (ps->stks[A].n)
	{
		n = ps->stks[A].n;
		while (n-- > 1)
		{
			if (( ps_lstcmp(*lst, (*lst)->next) < 0 ) )
			{
				s(set_curstk(ps, A));
				r(set_curstk(ps, A));
			}
			else
				r(set_curstk(ps, A));
		}
		p(ps, B);

	}
	while(ps->stks[B].n)
		p(ps, A);

}


void	ps_update_idx(t_stack *stk)
{
	t_list	*lst;
	int		i;

	i = 0; 
	lst = stk->head;
	while (lst )
	{
		if (i > stk->n / 2)
			ps_lstele(lst)->idx = i - stk->n;
		else
			ps_lstele(lst)->idx = i;
		lst = lst->next;
		i++;
	}


}


void	ps_three_sort(t_ps *ps)
{
	t_list	**lst;

	lst = &ps->stks->head;
	if (ps_lstcmp(*lst, get_max(ps->stks)) == 0)
		r(ps);
	else if (ps_lstcmp((*lst)->next, get_max(ps->stks)) == 0)
		rr(ps);
	if (ps_lstcmp(*lst, (*lst)->next) > 0)
		s(ps);
	return (0);
}

t_list	*rotate_help(t_ps *ps, int n)
{

	if (n > 0)
		while (n--)
			r(ps);
	else
		while (n++)
			rr(ps);
	return (ps->stks->head);
}

void	ps_five_sort(t_ps *ps)
{
	t_list	**lst1;
	t_list	**lst2;
	int		from;
	int		pushed;

	from = ps->curstk;
	pushed = 0;
	lst1 = &ps->stks[from].head;
	lst2 = &ps->stks[(from+1) % 2].head;
	while (ps->stks[from].n > 3 && ++pushed)
	{
		ps_update_idx(&ps->stks[from]);
		rotate_help(set_curstk(ps, from), ps_lstele(get_min(&ps->stks[from]))->idx);
		p(ps, (from + 1) % 2);
	}
	ps_three_sort(set_curstk(ps, from));
	while (pushed--)
		p(ps, from);
}

void bubble_sort_opt(t_ps *ps)
{
	int	n;
	int min;
	int max;
	t_list	**lst;

	lst = &ps->stks[A].head;
	while (ps->stks[A].n)
	{
		n = ps->stks[A].n;
		ps_update_idx(&ps->stks[A]);
		max = ps_lstele(get_max(&ps->stks[A]))->idx;
		min = ps_lstele(get_min(&ps->stks[A]))->idx;
		if (max < min)
		{
			rotate_help(set_curstk(ps, A), max);
			p(ps, B);
			r(set_curstk(ps, B));
		}
		else
		{
			rotate_help(set_curstk(ps, A), min);
			p(ps, B);
		}
	}
	ps_update_idx(&ps->stks[B]);
	rotate_help(set_curstk(ps, B), ps_lstele(get_max(&ps->stks[B]))->idx );
	while(ps->stks[B].n)
	{
		p(ps, A);
	}
}

int	log2n(int n)
{
	if (n > 1)
		return (1 + log2n(n / 2));
	return (0); 
}

long	n_log_n(int n)
{
	if (n <= 1)
		return (0);
	return ((long)n * log2n(n));
}

void	ps_bench(t_ps *ps)
{
	t_count c;
	int		n;

	c = ps->count;
	n = ps->stks[A].n;
	ft_printf_fd(2,"[bench]\tdisorder:\t%i%%\n", ps->disorder);
	ft_printf_fd(2,"[bench]\tstrategy:\t%s\n", ps->strat);
	ft_printf_fd(2,"[bench]\ttotal_ops:\t%i\n", c.tot);
	ft_printf_fd(2,"[bench]\tsa:\t%i\tsb:\t%i\tss:\t%i\tpa:\t%i\tpb:\t%i\n", c.s[A], c.s[B], c.ss[0], c.p[A], c.p[B]);
	ft_printf_fd(2,"[bench]\tra:\t%i\trb:\t%i\trr:\t%i\trra:\t%i\trrb:\t%i\n", c.r[A], c.r[B], c.rrs[0], c.rr[A], c.rr[B], c.rrs[1]);
	ft_printf_fd(2,"[bench]\tops/n:\t%i ops/nlogn:\t%i\n", c.tot / n , c.tot / n_log_n(n) );
}

void	radix_sort(t_ps *ps)
{
	int max;
	int nbit;
	int n;
	int i;
	
	max = ps_lstele(get_max(&ps->stks[A]))->sort;
	nbit = 0;
	n = ps->stks[A].n;
	i = 0;
	while (max >> nbit)
		nbit++;
	while (nbit--)
	{
		n = ps->stks[A].n;
		while (n--)
		{
			if ((ps_lstele(ps->stks[A].head)->sort >> i) & 1)
				r(set_curstk(ps, A));
			else
				p(ps, B);
		}
		while (ps->stks[B].n)
				p(ps, A);
		i++;
	}

}

int	ft_sqrt(int nb)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	if (nb == 1)
		return (1);
	if (nb > 2)
	{
		while (nb > 0 && (j++ + ++i))
			nb -= (i++);
	//	if (nb < 0)
//			return (0);
	}	
	return (j);
}

#include <math.h>
void	k_sort(t_ps *ps)
{
	int current_cap;
	t_list	**lst;

	lst = &ps->stks[A].head;
	current_cap = ft_sqrt(ps->stks[A].n) * 1;
	while (ps->stks[A].n)
	{
		ps_update_idx(&ps->stks[A]);
		if (ps_lstele(ps->stks[A].head)->sort <= ps->stks[B].n)
		{
			p(ps, B);
			r(set_curstk(ps, B));
		}
		else if(ps_lstele(ps->stks[A].head)->sort <= ps->stks[B].n + current_cap)
			p(ps, B);
		else 
			r(set_curstk(ps, A));
	}
	while (ps->stks[B].n)
	{
		ps_update_idx(&ps->stks[B]);
		rotate_help(set_curstk(ps, B), ps_lstele(get_max(&ps->stks[B]))->idx );
		p(ps, A);
	}
	ps_update_idx(&ps->stks[A]);
}
/*
void	check_flags(t_ps *ps)
{

}
*/
char	**handle_input(int *ac, char **av, t_ps *ps)
{
	int i;

	i = 0;
	while ( av[i] && *(av[i]) == '-' && !ft_isdigit(*av[i] + 1))
		i++;
	ps->flags = (char **)ft_calloc(i, sizeof(char *));
	while (i && (*ac)--)
		ps->flags[--i] = ft_strdup(*av++);
	if (*ac == 2)
		av = ft_split(av[0], ' ');
	else
		while (--*ac)
			av[i] = ft_strdup(av[i]);
	*ac = chk_input(av);
	return (av);
}

int main(int ac, char **av)
{
	int			*iarr;
	char		**flags;
	t_ps		ps[1];
	t_stack		stks[2];
	t_element	*elements;

	ft_bzero(ps, sizeof(ps));
	ps->fd = 1;
	if (ac > 1)
	{
		av = handle_input(&ac, ++av, ps);
		iarr = ft_strstoiarr(av, ac);
		if (iarr)
		{
			ps->elements = ps_getelements(iarr, ac, 'a');
			//free(iarr);
			if (!ps->elements)
				return ( free(av), 0);
		}
		else if (ac == -1 || !iarr)
			return (free(*av), 0);
		if (!ps_init_stacks(ps, ac))
			return (0);
		ps->disorder = compute_disorder(&ps->stks[A]);
	}
	//	ps_print(ps);
	//ps_five_sort(set_curstk(ps, A));
	//bubble_sort(ps);
	//bubble_sort_opt(ps);
	//radix_sort(ps);
	k_sort(ps);
	ps_print(ps);
	ps_bench(ps);
}
