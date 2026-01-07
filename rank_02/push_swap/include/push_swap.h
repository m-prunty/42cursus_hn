/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maprunty <maprunty@student.42heilbron      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/05 00:57:54 by maprunty          #+#    #+#             */
/*   Updated: 2026/01/07 15:26:40 by maprunty         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H

# include "libft.h"
# include "ft_printf.h"
# include "ft_btree.h"
# include "get_next_line.h"

# define A 0
# define B 1

typedef enum e_psflag
{
	BENCH	= 'B',
	BUBBLE	= 'b',
	RADIX	= 'r',
	K_SORT	= 'k',
}	t_psflag;

typedef struct s_stack
{
	char	name;
	int		n;
	t_list	*head;
	t_btree	*root;
}	t_stack;

typedef struct s_element
{
	int		value;
	int		idx;
	int		sort;
}	t_element;

typedef struct s_count
{
	int	tot;
	int	p[2];
	int	s[2];
	int	ss[1];
	int	r[2];
	int	rr[2];
	int	rrs[2];
}	t_count;

typedef struct s_ps
{
	t_stack		stks[2];
	int			curstk;
	t_psflag	flags[2];
	t_element	*elements;
	t_count		count;
	int			disorder;
	int			fd;
}	t_ps;

// push_swap.c
void		push_swap(t_ps *ps);
int			ps_init_stacks(t_ps *ps, int n);
char		**handle_input(int *ac, char **av, t_ps *ps);
int			*ft_strstoiarr(char **strs, int n);

// parse.c
void		process_flag(t_ps *ps, char *flag);
int			chk_input(char **strs);
int			ft_isstr_numeric(char *str);

// elements.c
t_element	ps_elenew(int value);
t_element	*ps_getelements(int *iarr, int n);
long		ps_elecmp(void *ele1, void *ele2);
void		ps_apfcount(void *e);

// print.c
void		ps_putele(void *e);
void		ps_putnbr(void *e);
void		ps_print(t_ps *ps);
void		ps_bench(t_ps *ps);

// stacks.c
int			compute_disorder(t_stack *stk);
int			ps_issorted(t_stack *stk);
t_ps		*set_curstk(t_ps *ps, int stk);
t_list		*get_max(t_stack *stk);
t_list		*get_min(t_stack *stk);

// lists.c
int			ps_lstcmp(t_list *lst1, t_list *lst2);
t_element	*ps_lstele(t_list *lst);

// algos.c
void		bubble_sort(t_ps *ps);
void		bubble_sort_opt(t_ps *ps);
void		radix_sort(t_ps *ps);
void		k_sort(t_ps *ps);

// helpers.c
t_list		*rotate_help(t_ps *ps, int n);
void		ps_update_idx(t_stack *stk);
void		ps_three_sort(t_ps *ps);
void		ps_five_sort(t_ps *ps);

// clean.c
void		ft_free_list(t_list *lst);
void		ft_free_btree(t_btree *root);
void		ft_free_strs(char **strs);
void		ft_free_stack(t_stack *stk);
void		close_ps(t_ps *ps, int err);

// maths.c
int			log2n(int n);
long		n_log_n(int n);
int			ft_sqrt(int nb);

// rot.c
int			ft_lstrot(t_list **lst, int n);
int			rotate(t_stack *stk, int rev);
int			r(t_ps *ps);
int			rrs(t_ps *ps, int rev);

// rrot.c
t_list		*ft_lstgoto(t_list *lst, int idx);
int			ft_lstrrot(t_list **lst, int n);
int			rr(t_ps *ps);

// push.c
t_list		*ft_lstpop(t_list **list);
t_list		*ps_stkpop(t_stack *stk);
int			ps_stkpush(t_stack *stk, t_list *lst);
int			push(t_stack *stks, int stk_to);
int			p(t_ps *ps, int stk_to);

// swap.c
int			ft_lstswap(t_list **lst);
int			swap(t_stack *stk);
int			s(t_ps *ps);
#endif
