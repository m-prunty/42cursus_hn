/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maprunty <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/19 11:36:23 by maprunty          #+#    #+#             */
/*   Updated: 2025/12/12 23:09:17 by maprunty         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

t_gnl	*ft_gnlnew(t_gnl **new, char *content, size_t chk_sz)
{
	t_gnl	*tmp;

	tmp = (t_gnl *)ft_calloc_gnl(sizeof(t_gnl), 1);
	if (!(tmp))
		return (NULL);
	tmp->chk_sz = chk_sz;
	if (BUFFER_SIZE >= tmp->chk_sz)
		tmp->chk_sz = BUFFER_SIZE + 1;
	(tmp)->content = ft_calloc_gnl(tmp->chk_sz, 1);
	if (!(tmp)->content)
		return (ft_gnlclear(&tmp, NULL), NULL);
	tmp->n = 0;
	while (*(content + tmp->n))
		tmp->n++;
	ft_memcpy_gnl((tmp)->content, content, (tmp)->n);
	(tmp)->next = NULL;
	(tmp)->nl = 0;
	if ((tmp)->n && ft_memchr_gnl((tmp)->content, '\n', (tmp)->n))
		(tmp)->nl = (char *)ft_memchr_gnl((tmp)->content, '\n', (tmp)->n)
			- (tmp)->content + 1;
	*new = tmp;
	return (tmp);
}

void	fill_newline(t_gnl *tmp, char **nl, size_t *n)
{
	int	chunk_len;

	n[0] = 0;
	while (tmp && n[0] < n[1])
	{
		chunk_len = tmp->n;
		if (n[0] + chunk_len > n[1])
			chunk_len = n[1] - n[0];
		if (chunk_len > 0)
		{
			ft_memcpy_gnl(*nl + n[0], tmp->content, chunk_len);
			n[0] += chunk_len;
		}
		tmp = tmp->next;
	}
}

char	*return_nl(t_gnl **gnlbuf, char *ptr[])
{
	t_gnl	*tmp;
	char	*nl;
	size_t	n[2];

	n[1] = 0;
	tmp = *gnlbuf;
	while (tmp->next && !tmp->nl)
	{
		n[1] += tmp->n;
		tmp = tmp->next;
	}
	n[1] += tmp->n - (tmp->nl > 0) * (tmp->n - tmp->nl);
	ft_bzero_gnl(*ptr, BUFFER_SIZE + 1);
	if (tmp->nl && tmp->nl < (int)tmp->n)
		ft_memcpy_gnl(*ptr, tmp->content + tmp->nl, tmp->n - tmp->nl);
	nl = ft_calloc_gnl(n[1] + 1, 1);
	if (!nl)
		return (ft_gnlclear(gnlbuf, ptr), NULL);
	fill_newline(*gnlbuf, &nl, n);
	ft_gnlclear(gnlbuf, NULL);
	return (nl);
}

int	add_to_nl(t_gnl *buf, char *ptr, int fd, int nread)
{
	while (!(buf)->nl)
	{
		ft_bzero_gnl(ptr, BUFFER_SIZE + 1);
		nread = read(fd, ptr, BUFFER_SIZE);
		if (nread == 0)
			return ((buf)->nl = (buf)->n, 1);
		else if (nread < 0)
			return (0);
		if ((buf)->n + nread >= buf->chk_sz)
		{
			if (!ft_gnlnew(&((buf)->next), ptr, buf->chk_sz))
				return (0);
			buf = (buf)->next;
		}
		else
		{
			ft_memcpy_gnl((buf)->content + (buf)->n, ptr, nread);
			(buf)->n += nread;
			if (ft_memchr_gnl(ptr, '\n', nread))
				buf->nl = (char *)ft_memchr_gnl(buf->content + (buf->n - nread),
						'\n', nread) - buf->content + 1;
		}
	}
	return (1);
}

char	*get_next_line(int fd)
{
	static char	*ptr[FD_MAX] = {0};
	t_gnl		*gnlbuf;

	gnlbuf = NULL;
	if ((fd < 0))
		return (ft_gnlclear(&gnlbuf, &ptr[fd]), NULL);
	if (!ptr[fd])
	{
		ptr[fd] = ft_calloc_gnl(BUFFER_SIZE + 1, 1);
		if (!ptr[fd])
			return (ft_gnlclear(&gnlbuf, &ptr[fd]), NULL);
	}
	if (!ft_gnlnew(&gnlbuf, ptr[fd], CHUNK_SIZE))
		return (ft_gnlclear(NULL, &ptr[fd]), NULL);
	if (!add_to_nl(gnlbuf, ptr[fd], fd, gnlbuf->n))
		return (ft_gnlclear(&gnlbuf, &ptr[fd]), NULL);
	if (gnlbuf->n && *(char *)(gnlbuf->content))
		return (return_nl(&gnlbuf, &ptr[fd]));
	return (ft_gnlclear(&gnlbuf, &ptr[fd]), NULL);
}
