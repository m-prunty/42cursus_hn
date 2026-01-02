/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maprunty <maprunty@student.42heilbron      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/20 14:42:35 by maprunty          #+#    #+#             */
/*   Updated: 2026/01/02 01:07:22 by maprunty         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	push_swap(t_ps *ps)
{
	if (ps->stks[A].n <= 5)
		ps_five_sort(set_curstk(ps, A));
	else if (ps->flags[0] == BUBBLE)
		bubble_sort_opt(ps);
	else if (ps->flags[0] == RADIX)
		radix_sort(ps);
	else
		k_sort(ps);
	ps_bench(ps);
}

int	ps_init_stacks(t_ps *ps, int n)
{
	t_list	*tmplst;
	int		i;

	ps->stks[A].name = 'a';
	ps->stks[B].name = 'b';
	ps->fd = 1;
	i = -1;
	while (++i < n)
	{
		tmplst = ft_lstnew(&ps->elements[i]);
		ft_lstadd_back(&ps->stks[A].head, tmplst);
		btree_insert_data(&ps->stks[A].root, &ps->elements[i], ps_elecmp);
	}
	btree_apply_infix(ps->stks[A].root, ps_apfcount);
	ps->stks[A].n = i;
	return (1);
}

char	**handle_input(int *ac, char **av, t_ps *ps)
{
	char	**out;
	int		i;

	i = 0;
	while (av[i] && *(av[i]) == '-' && ft_isalpha(*(av[i] + 1)))
		i++;
	while (i-- && (*ac)--)
		process_flag(ps, *av++);
	if (*ac == 2)
		out = ft_split(av[0], ' ');
	else
	{
		i = -1;
		out = (char **)ft_calloc(*ac + 1, sizeof(char *));
		while (--*ac && ++i + 1)
			out[i] = ft_strdup(av[i]);
	}
	*ac = chk_input(out);
	return (out);
}

int	*ft_strstoiarr(char **strs, int n)
{
	int		i;
	int		j;
	long	tmp;
	int		*iarr;

	iarr = NULL;
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
			while (j <= i)
				if (iarr[j++] == tmp || tmp < (1 << 31) || tmp > ~(1 << 31))
					return (free(iarr), NULL);
			iarr[i] = tmp;
		}
	}
	return (iarr);
}

int	main(int ac, char **av)
{
	int		*iarr;
	t_ps	ps[1];

	ft_bzero(ps, sizeof(ps));
	if (ac > 1)
	{
		av = handle_input(&ac, ++av, ps);
		iarr = ft_strstoiarr(av, ac);
		ft_free_strs(av);
		if (iarr)
		{
			ps->elements = ps_getelements(iarr, ac);
			if (!ps->elements)
				return (0);
			free(iarr);
		}
		else if (ac == -1 || !iarr)
			return (close_ps(ps, 1), 1);
		if (!ps_init_stacks(ps, ac))
			return (close_ps(ps, 1), 1);
		ps->disorder = compute_disorder(&ps->stks[A]);
		if (ps->disorder)
			push_swap(ps);
	}
	return (close_ps(ps, 0), 0);
}
