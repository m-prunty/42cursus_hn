/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_list.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maprunty <maprunty@student.42heilbronn.de  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/02 17:01:12 by maprunty          #+#    #+#             */
/*   Updated: 2025/09/03 02:13:46 by maprunty         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "includes/ft.h"

typedef struct s_list
{
	struct s_list	*next;
	void			*data;
}				t_list;

t_list	*ft_create_elem(void *data);
void	ft_list_push_front(t_list **begin_list, void *data);
int		ft_list_size(t_list *begin_list);

t_list	*ft_list_last(t_list *begin_list);
void	ft_list_push_back(t_list **begin_list, void *data);
t_list	*ft_list_push_strs(int size, char **strs);
void	ft_list_clear(t_list *begin_list, void (*free_fct)(void *));
void	free_fct(void *t);
t_list	*ft_list_at(t_list *begin_list, unsigned int nbr);
void	ft_list_rm(t_list **begin_list, int pos);
void	ft_list_rm_last(t_list **begin_list, int n);
void	ft_list_add_back(t_list **begin_list, t_list *ele);
void	ft_list_add_front(t_list **begin_list, t_list *ele);

void	ft_list_reverse_rec(t_list **begin_list, unsigned int n);
void	ft_list_insert(t_list **begin_list, t_list *ele, int pos );
void	ft_list_swap(t_list **begin_list, int a, int b);
void	ft_list_reverse(t_list **begin_list);
int		ft_list_is(t_list **begin_list);
void	ft_list_foreach(t_list *begin_list, void (*f)(void *));
void	ft_list_foreach_if(t_list *begin_list, void (*f)(void *),
			void *data_ref, int (*cmp)(char *, char *));
t_list	*ft_list_find(t_list *begin_list, void *data_ref,
			int (*cmp)(char *, char *));
void	free_fct2(void *data);
void	ft_list_remove_if(t_list **begin_list, void *data_ref,
			int (*cmp)(char *, char *), void (*free_fct)(void *));
void	ft_list_merge(t_list **begin_list1, t_list *begin_list2);
int		ft_list_issorted(t_list *begin_list,
			int (*cmp)(char *, char *), int dir);
void	ft_list_sort_cmprec(t_list **begin_list, int (*cmp)(char *, char *));
void	ft_list_sort(t_list **begin_list, int (*cmp)(char *, char *));
t_list	*ft_list_find_prev(t_list *begin_list,
			void *data_ref, int (*cmp)(char *, char *));
void	ft_sorted_list_insert(t_list **begin_list, void *data, int (*cmp)());
void	ft_sorted_list_insert_ele(t_list **begin_list,
			t_list *data, int (*cmp)());
void	ft_sorted_list_merge(t_list **begin_list1,
			t_list *begin_list2, int (*cmp)());
void	ft_putstrv(void *str);
