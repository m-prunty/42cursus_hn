/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maprunty <maprunty@student.42heilbron      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/05 00:57:54 by maprunty          #+#    #+#             */
/*   Updated: 2025/12/14 12:14:47 by maprunty         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ft_printf.h"
#include "ft_btree.h"
#include "get_next_line.h"

# define A 0
# define B 1


typedef struct s_stack
{
	char	name;
	int		n;
	t_list	*head;
	t_btree *root;
	
}	t_stack;

typedef struct s_element
{
	int		value;
	int		idx;
	int		sort;
	int		sorted;
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
	char		curstk;
	char		**flags;
	char		*strat;
	t_element	*elements;
	t_count		count;
	int			disorder;
	int			fd;
}	t_ps;


int			*ft_strstoiarr(char **strs,  int n);
t_element	*ps_elenew(int value);
t_element	*ps_getelements(int *iarr, int n, char name);
t_list		*get_max(t_stack *stk);
t_element	*ps_lstele(t_list *lst);

int		ft_isstr_numeric(char *str);
int		chk_input(char **strs);

void	push_swap(int *iarr, int ac);

int		ps_elecmp(void *ele1, void *ele2);
void	ps_putnbr(t_element *ele);
void	ps_print(t_ps *ps);
void	ps_apfcount(t_element *ele);

int		ps_init_stacks(t_ps *ps, int n);

int		ft_lstrrot(t_list **lst, int n);
int		ft_lstrot(t_list **lst, int n);
int		rotate(t_stack *stk, int rev);
int		r(t_ps *ps);
int		rr(t_ps *ps);
int		rrs(t_ps *ps, int rev);

t_list	*ft_lstgoto(t_list *lst, int idx);
t_list	*ft_lstpop(t_list **list);
t_list	*ps_stkpop(t_stack *stk);
int		ps_stkpush(t_stack *stk, t_list *lst);
int		push(t_stack *stks, int stk_to);
int		p(t_ps *ps, int stk_to);

int		ft_lstswap(t_list **lst);
int		swap(t_stack *stk);
int		s(t_ps *ps);

int		compute_disorder(t_stack *stk);
int		ps_issorted(t_stack *stk);

int		ps_lstcmp(t_list *lst1, t_list *lst2);
void	place_in_stk(t_stack *stk, t_list *to_place);
int		n_sorted(t_stack stk);

void	bubble(t_ps *ps, int to);
void	bubble_sort(t_ps *ps);
