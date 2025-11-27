/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maprunty <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/19 11:36:23 by maprunty          #+#    #+#             */
/*   Updated: 2025/11/27 07:17:44 by maprunty         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

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

t_gnl	*ft_gnlnew(t_gnl **new, void *content)
{
	t_gnl *tmp;

	tmp = (t_gnl *)malloc(sizeof(t_gnl));
	tmp->n = 0;
	if (!(tmp))
		return (NULL);
	(tmp)->content = ft_calloc(CHUNK_SIZE, 1);
	if (!(tmp)->content)
		return (free(tmp), NULL);

	while (*(char *)(content + tmp->n))
		tmp->n++;
	ft_memcpy((tmp)->content, content, (tmp)->n);
	(tmp)->next = NULL;
	(tmp)->nl = 0;
	if ((tmp)->n && ft_memchr((tmp)->content , '\n', (tmp)->n))
		(tmp)->nl = ft_memchr((tmp)->content , '\n', (tmp)->n) - (tmp)->content + 1;
	*new = tmp;
	return (tmp);
}

void	fill_newline(t_gnl *tmp, char **nl, size_t *n)
{
	int		chunk_len;

	n[0] = 0;
	while (tmp && n[0] < n[1])
    {
		chunk_len = tmp->n;
        if (n[0] + chunk_len > n[1])
            chunk_len = n[1] - n[0];
		if (chunk_len >0)
		{
			ft_memcpy(*nl + n[0], tmp->content, chunk_len);
			n[0] += chunk_len;
		}
		tmp = tmp->next;
    }
}

char    *return_nl(t_gnl **gnlbuf, char ptr[])
{
    t_gnl   *tmp;
    char    *nl;
    size_t   n[2] = {0};

	n[1] = 0;
    tmp = *gnlbuf;
    while (tmp->next && !tmp->nl)
	{
		n[1] += tmp->n;
        tmp = tmp->next;
	}
	n[1] += tmp->n - (tmp->nl > 0) * (tmp->n - tmp->nl);
    ft_bzero(ptr, BUFFER_SIZE + 1);
	if (tmp->nl && tmp->nl < (int)tmp->n)
		ft_memcpy(ptr, tmp->content + tmp->nl, tmp->n - tmp->nl );
    nl = ft_calloc(n[1] + 1, 1);
    if (!nl)
        return (ft_gnlclear(gnlbuf), NULL);
    tmp = *gnlbuf;
	fill_newline(*gnlbuf, &nl, n);
	ft_gnlclear(gnlbuf);
    return (nl);
}

int	add_to_nl(t_gnl **buf, char *ptr, int fd, int nread)
{
	while (!(*buf)->nl)
	{
		ft_bzero(ptr, BUFFER_SIZE + 1);
		nread = read(fd, ptr, BUFFER_SIZE);
		if (nread > 0)
		{
			if ((*buf)->n + nread >= CHUNK_SIZE)
			{
				if (!ft_gnlnew(&((*buf)->next), ptr))
					return (0);
				*buf = (*buf)->next;
			}
			else
			{
				ft_memcpy((*buf)->content + (*buf)->n, ptr, nread);
				(*buf)->n += nread;
				if (ft_memchr(ptr, '\n', nread))
					(*buf)->nl = ft_memchr((*buf)->content + ((*buf)->n - nread), '\n', nread) - (*buf)->content + 1;
			}
		}
		else if (nread == 0)
			return ((*buf)->nl = (*buf)->n);
		else if (nread < 0)
			return (0);
	}
	return (1);
}

char	*get_next_line(int fd)
{
	static char	ptr[BUFFER_SIZE + 1] = {0};
	t_gnl		*gnlbuf;
	t_gnl		*tmp;

	gnlbuf = NULL;
	if ((fd < 0) || !ft_gnlnew(&gnlbuf, ptr))
		return (0);
	tmp = gnlbuf;
	if (!add_to_nl(&tmp, ptr, fd, tmp->n))
		return (ft_gnlclear(&gnlbuf), NULL);
	if (*(char *)(gnlbuf->content))
		return (return_nl(&gnlbuf, ptr));
	return (ft_gnlclear(&gnlbuf), NULL);
}
