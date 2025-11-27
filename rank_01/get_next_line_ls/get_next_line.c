/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maprunty <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/19 11:36:23 by maprunty          #+#    #+#             */
/*   Updated: 2025/11/27 03:26:32 by maprunty         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

t_gnl	*ft_gnlnew(void *content)
{
	t_gnl	*new;

	new = (t_gnl *)malloc(sizeof(t_gnl));
	if (!new)
		return (NULL);
	new->content = ft_calloc(CHUNK_SIZE, 1);
	if (!new->content)
		return (free(new), NULL);
	new->n = ft_strlen((char *)content);
	ft_memcpy(new->content, content, new->n);
	new->next = NULL;
	new->nl = 0;
	if (new->n && ft_memchr(new->content , '\n', new->n))
		new->nl = ft_memchr(new->content , '\n', new->n) - new->content + 1;
	return (new);
}

void	ft_gnlclear(t_gnl **gnlbuf)
{
	t_gnl	*tmp;

	while (*gnlbuf)
	{
		tmp = ((*gnlbuf)->next);
		free((*gnlbuf)->content);
		(*gnlbuf)->content = NULL;
		free(*gnlbuf);
		*gnlbuf = tmp;
	}
}

char    *return_nl(t_gnl **gnlbuf, char ptr[])
{
    t_gnl   *tmp;
    size_t   n_nl;
    size_t   n;
    char    *nl;
	int		chunk_len;

    tmp = *gnlbuf;
    n_nl = 0;
    while (tmp->next && !tmp->nl )
	{
		n_nl += tmp->n;
        tmp = tmp->next;
	}
	n_nl += tmp->n - (tmp->nl > 0) * (tmp->n - tmp->nl);
    ft_bzero(ptr, BUFFER_SIZE + 1);
	if (tmp->nl && tmp->nl < (int)tmp->n)
		ft_memcpy(ptr, tmp->content + tmp->nl, tmp->n - tmp->nl );
    nl = ft_calloc(n_nl + 1, 1);
    if (!nl)
        return (ft_gnlclear(gnlbuf), NULL);
    tmp = *gnlbuf;
    n = 0;
    while (tmp && n < n_nl)
    {
		chunk_len = tmp->n;
        if (n + chunk_len > n_nl)
            chunk_len = n_nl - n;
		if (chunk_len >0)
		{
			ft_memcpy(nl + n, tmp->content, chunk_len);
			n += chunk_len;
		}
		tmp = tmp->next;
    }
    ft_gnlclear(gnlbuf);
    return (nl);
}

int	add_to_nl(t_gnl **gnlbuf, char *buf, int fd)
{
	t_gnl	*tmp;
	int		nread;

	*gnlbuf= ft_gnlnew(buf);
	if (!*gnlbuf)
		return (0);
	tmp = *gnlbuf;	
	nread = tmp->n;
	while (!tmp->nl)
	{
		ft_bzero(buf, BUFFER_SIZE + 1);
		nread = read(fd, buf, BUFFER_SIZE);
		if (nread == 0)
		{
			tmp->nl = tmp->n;
			return (1);
		}
		else if (nread < 0)
			return (0);
		if (tmp->n + nread >= CHUNK_SIZE)
		{
			tmp->next = ft_gnlnew(buf);
			if (!tmp->next)
				return (0);
			tmp = tmp->next;
		}
		else
		{
			ft_memcpy(tmp->content + tmp->n, buf, nread);
			tmp->n += nread;
			if (ft_memchr(buf, '\n', BUFFER_SIZE))
				tmp->nl = ft_memchr(tmp->content + (tmp->n - nread), '\n', nread) - tmp->content + 1;
		}
	}
	return (1);	
}

char *get_next_line(int fd)
{
	static char	ptr[BUFFER_SIZE + 1] = {0};
	t_gnl		*gnlbuf;

	if (fd < 0)
		return (NULL);
	if (!add_to_nl(&gnlbuf, ptr, fd))
		return (ft_gnlclear(&gnlbuf), NULL);
	if (*(char *)(gnlbuf->content))
		return (return_nl(&gnlbuf, ptr));
	return (ft_gnlclear(&gnlbuf), NULL);
}
