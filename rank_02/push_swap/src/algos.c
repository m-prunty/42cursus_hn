/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algos.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maprunty <maprunty@student.42heilbron      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/20 14:42:35 by maprunty          #+#    #+#             */
/*   Updated: 2026/01/07 14:40:25 by maprunty         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	bubble_sort(t_ps *ps)
{
	int		n;
	t_list	**lst;

	lst = &ps->stks[A].head;
	while (ps->stks[A].n)
	{
		n = ps->stks[A].n;
		while (n-- > 1)
		{
			if ((ps_lstcmp(*lst, (*lst)->next) < 0))
			{
				s(set_curstk(ps, A));
				r(set_curstk(ps, A));
			}
			else
				r(set_curstk(ps, A));
		}
		p(ps, B);
	}
	while (ps->stks[B].n)
		p(ps, A);
}

void	bubble_sort_opt(t_ps *ps)
{
	int	min;
	int	max;

	while (ps->stks[A].n)
	{
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
	rotate_help(set_curstk(ps, B), ps_lstele(get_max(&ps->stks[B]))->idx);
	while (ps->stks[B].n)
		p(ps, A);
}

void	radix_sort(t_ps *ps)
{
	int	max;
	int	nbit;
	int	n;
	int	i;

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


void	k_sort(t_ps *ps)
{
	int	range;

	range = ft_sqrt(ps->stks[A].n) * 1;
	while (ps->stks[A].n)
	{
		ps_update_idx(&ps->stks[A]);
		if (ps_lstele(ps->stks[A].head)->sort <= ps->stks[B].n)
		{
			p(ps, B);
			r(set_curstk(ps, B));
		}
		else if (ps_lstele(ps->stks[A].head)->sort <= ps->stks[B].n + range)
			p(ps, B);
		else
			r(set_curstk(ps, A));
	}
	while (ps->stks[B].n)
	{
		ps_update_idx(&ps->stks[B]);
		rotate_help(set_curstk(ps, B), ps_lstele(get_max(&ps->stks[B]))->idx);
		p(ps, A);
	}
	ps_update_idx(&ps->stks[A]);
}
