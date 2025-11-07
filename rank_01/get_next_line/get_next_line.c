/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maprunty <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/19 11:36:23 by maprunty          #+#    #+#             */
/*   Updated: 2025/11/08 00:26:37 by maprunty         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stddef.h>
#include <unistd.h>
#define CHUNK 1024

typedef struct	s_block
{
	struct s_block	*next;
	void	*ptr;
	size_t	size;
	int		marked;
}		t_block ;




void *mt_calloc(t_block **head, size_t nmemb, size_t size)
{
	void	*p;
	t_block *b;
	
	p =	ft_calloc(nmemb, size);
	b = ft_calloc(sizeof(t_block), 1);
	b->ptr = p;
	b->size = nmemb * size;
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

int	calloc_protect(t_block **head, char **to_calloc, size_t n)
{
	*to_calloc = mt_calloc(head, n, 1);
	return (*to_calloc != NULL);
}

t_block	*mt_free_block(t_block *block)
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
	t_block *tmp;
	t_block *prev;

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
	mt_free_block(tmp);
}

char	*clean_return(t_block **mt, char **ptr)
{
	char	*ptr_ret;
	char	*nl_ret;
	size_t	n[2];

	n[1] = ft_strlen(*ptr);
	n[0] = 0;
	ptr_ret = (char *)ft_memchr(*ptr, '\n', n[1]);
	if (ptr_ret)
		n[0] = (ptr_ret - *ptr + 1);
	ptr_ret = NULL;
	if (!n[0])
		n[0] = n[1];
	if (!calloc_protect(mt, &nl_ret, sizeof(char) * (n[0] + 1)))
		return (mt_free(mt, NULL), NULL);
	ft_memcpy(nl_ret, *ptr, n[0]);
	if (n[0] < n[1])
	{	
		if (!calloc_protect(mt, &ptr_ret, sizeof(char) * (n[1] - n[0] + 1)))
			return (mt_free(mt, NULL), NULL);
		ft_memcpy(ptr_ret, *ptr + n[0], n[1] - n[0]);
		ptr_ret[n[1] - n[0]] = '\0';
	}
	mt_free(mt, *ptr);
	(*mt)->ptr = ptr_ret; 
	if (*nl_ret)
		return (nl_ret);
	return (mt_free(mt, NULL) ,NULL);
}



int	add_to_stat(t_block **mt, char **ptr, char *buf, int *nread)
{
	size_t	cur_n;
	size_t	sz;
	size_t	n;
	char	*tmp;

	n = 0;
	if (*ptr)
		n = ft_strlen(*ptr);
	sz = n + *nread + 1;
	cur_n = (( n - 1 + CHUNK) / CHUNK);
	if (!*ptr || sz + 1 >= CHUNK * (cur_n ))
	{
		if (!calloc_protect(mt, &tmp, CHUNK * (cur_n + 1)))
		{
			*nread = -1;
			return (0);
		}
		if (*ptr && ft_memcpy(tmp, *ptr, n))
			mt_free(mt, ptr);
		*ptr = tmp;
	}
	ft_memcpy(*ptr + n, buf, *nread);
	return (1);
}

char	*get_next_line(int fd)
{
	static t_block	*mt; 
	char			**ptr;
	char			*buf;
	int				nread;

	nread = 1;
	ptr = (char **)mt_calloc(&mt, 1, sizeof(char *));
	buf = (char *)mt_calloc(&mt, BUFFER_SIZE + 1, sizeof(char));
	if (!buf || !ptr)
		return (mt_free(&mt, NULL), NULL);
	if (mt->ptr && *(char *)mt->ptr)
		*ptr = mt->ptr;
	else
		*ptr = (char *)mt_calloc(&mt, CHUNK, sizeof(char));
	while ((!ptr || !ft_memchr(buf, '\n', nread)) && nread)
	{
		ft_bzero(buf, BUFFER_SIZE + 1);
		nread = read(fd, buf, BUFFER_SIZE);
		if (nread >= 1 && add_to_stat(&mt, ptr, buf, &nread))
			;
		else if (nread < 0)
			return (mt_free(&mt, NULL), NULL);
	}
	if (buf)
		mt_free(&mt, buf);
	if (ptr || nread)
		return (clean_return(&mt, ptr));
	return (mt_free(&mt, NULL), NULL);
}

