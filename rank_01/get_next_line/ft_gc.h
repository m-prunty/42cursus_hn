/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_gc.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maprunty <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/07 19:28:41 by maprunty          #+#    #+#             */
/*   Updated: 2025/11/07 21:36:05 by maprunty         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

typedef struct	s_block
{
	t_block	*next;
	void	*ptr;
	size_t	size;
	int		marked;
}		t_block;

typedef struct	s_alloc
{
	t_block	*alloc;
	size_t	n;
}		s_alloc;



void *mt_calloc(t_block **head, size_t nmemb, size_t size)
{
	void	*p;
	t_block *b;
	size_t  n;

	n = nmemb * size;
	if (n <= PTRDIFF_MAX)
   		p = malloc(n);
	b = malloc(sizeof(t_block));
	if (!p || !b || n > PTRDIFF_MAX )
		return (NULL);
	ft_bzero(p, n);
	b->ptr = p;
	b->size = n;
	b->marked = 0;
	b->next = NULL;
	if (!*head)
		*head = b;
	else
	{
		t_block *tmp = *head;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = b;
	}
	return (p);
}

t_block	mt_free_block(t_block *block)
{
	t_block *tmp;

	tmp = block->next;
	free(block->ptr);
	free(block);
	block = NULL;
	return (tmp);
}


void	mt_free(t_block **head, void *ptr)
{
	t_block tmp;
	t_block prev;

	prev = NULL;
	tmp = *head;
	if (!ptr)
	{
		while (tmp)
			tmp = mt_free_block(prev);
		*head = NULL;
		return ;
	}
	while (tmp && tmp->ptr != ptr)
	{
		prev = tmp;
		tmp = tmp->next;
	}
	if (!tmp)
		return;
	if (prev)
		prev->next = tmp->next;
	else
		*head = tmp->next;
	mt_free_block(&tmp);
}

/*
void *mt_calloc(t_block *head, size_t nmemb, size_t size)
{
	void	*p;
	t_block	*b;
	int		n;

	n = nmemb * sz;
	if (n <= PTRDIFF_MAX)
		p = malloc(n);
	b = malloc(sizeof(t_block));
	if (n > PTRDIFF_MAX || !p || !b)
		return (NULL);
	ft_bzero((char *)p, n);
	b->ptr =  p;
	b->size = n;
	b->marked = 0;
	while (head->next)
		head = head->next;
	head->next = b;
	return (b->ptr)
}

void	mt_free(t_block head, void *ptr)
{
	t_block *tmp;

	if (ptr)
	{
		while (head->ptr != ptr)
			head = head->next;
		free(head->ptr);
		free(head);
	}
	else
	{
		while (head)
		{
			tmp = head;
			head = head->next;
			free(tmp->ptr);
			free(tmp);
		}
	}
}
