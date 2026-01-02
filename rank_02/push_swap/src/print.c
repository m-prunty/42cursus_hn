/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maprunty <maprunty@student.42heilbron      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/20 14:42:35 by maprunty          #+#    #+#             */
/*   Updated: 2025/12/20 16:34:53 by maprunty         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	ps_putele(void *e)
{
	t_element	*ele;

	ele = (t_element *)e;
	if (ele)
		ft_printf_fd(2, "%i, %i, %i\n", ele->value, ele->sort, ele->idx);
}

void	ps_putnbr(void *e)
{
	t_element	*ele;

	ele = (t_element *)e;
	if (ele)
		ft_printf_fd(2, "%i ", ele->value);
}

void	ps_print(t_ps *ps)
{
	t_stack	stk;
	int		i;

	i = -1;
	while (++i < 2)
	{
		stk = ps->stks[i];
		if (stk.n)
		{
			ft_printf_fd(2, "stack: %c\n", stk.name);
			ft_lstiter(stk.head, ps_putele);
			ft_printf_fd(2, "disorder->>>%i\n", compute_disorder(&stk));
		}
	}
}

void	ps_bench(t_ps *ps)
{
	t_count	c;
	int		n;

	if (ps->flags[1] == BENCH)
	{
		ps_print(ps);
		c = ps->count;
		n = ps->stks[A].n;
		ft_printf_fd(2, "[bench]\tdisorder:\t%i%%\n", ps->disorder);
		ft_printf_fd(2, "[bench]\tstrategy:\t%c\n", ps->flags[0]);
		ft_printf_fd(2, "[bench]\ttotal_ops:\t%i\n", c.tot);
		ft_printf_fd(2, "[bench]\tsa:\t%i\tsb:\t%i\tss:\t%i\tpa:\t%i\tpb:\t%i\n",
			c.s[A], c.s[B], c.ss[0], c.p[A], c.p[B]);
		ft_printf_fd(2, "[bench]\tra:\t%i\trb:\t%i\trr:\t%i\trra:\t%i\trrb:\t%i\n",
			c.r[A], c.r[B], c.rrs[0], c.rr[A], c.rr[B], c.rrs[1]);
		ft_printf_fd(2, "[bench]\tops/n:\t%i ops/nlogn:\t%i\n",
			c.tot / n, c.tot / n_log_n(n));
	}
}
