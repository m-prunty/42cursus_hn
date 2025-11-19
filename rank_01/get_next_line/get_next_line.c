/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maprunty <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/19 11:36:23 by maprunty          #+#    #+#             */
/*   Updated: 2025/11/19 20:06:24 by maprunty         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

//int calloc_help(char *str, )

void *free_null(char **buf)
{
	free(*buf);
	*buf = NULL;
	return (NULL);
}

char	*clean_return(char ptr[], char *tmpbuf)
{	char	*nl;
	char	*sub;
	size_t	n;

	nl = ft_strchr(tmpbuf, '\n');
	if (nl)
		n = nl - tmpbuf + 1;
	else
		n = ft_strlen(tmpbuf);
	sub = ft_calloc(sizeof(char), n  + 1);
	if (!sub)
		return (NULL);
	ft_memcpy(sub, tmpbuf, n);
	ft_memmove(ptr, tmpbuf + n, ft_strlen(tmpbuf + n));		
	ptr[ft_strlen(tmpbuf + n)] = '\0';
	free(tmpbuf);
	return (sub);
	/*
	tmp = *ptr;
	*ptr = NULL;
	n = ft_strlen(tmp);
	nl = ft_memchr(tmp, '\n', n);
	if (nl)
	{
		sub = ft_substr(tmp, 0, nl + 1 - tmp);
		if (!sub)
			return (free_null(&tmp), NULL);
		if (ft_strlen(sub) < n)
		{
			*ptr = ft_substr(tmp, nl + 1 - tmp, ft_strlen(tmp) - (nl + 1 - tmp));
			if (!*ptr)
				return (free_null(&sub), free_null(&tmp),  NULL);
		}
		free(tmp);
	}
	else
	{
		sub = malloc(sizeof(char) * n + 1);
		if (!sub)
			return (free_null(&tmp), NULL);
		ft_memcpy(sub, tmp, n);
		sub[n] = '\0';
		free(tmp);
		tmp = NULL;
	}
	return (sub);*/
}

int	add_to_stat(char ptr[], char **tmpbuf, int *nread)
{
	int		n;
	char	*tmp;

	n = ft_strlen(ptr);
	tmp = (char *)ft_calloc((n + *nread + 1), sizeof(char));
	if (!tmp)
	{
		*nread = -1;
		return (0);
	}
	ft_memcpy(tmp, ptr, n);
	ft_memcpy(tmp + n, *tmpbuf, *nread);
	tmp[n + *nread] = '\0';
	free(*tmpbuf);
	*tmpbuf = tmp;
	return (1);
}

char	*get_next_line(int fd)
{
	static char	ptr[BUFFER_SIZE + 1] = {0};
	char		*tmpbuf;
	int			nread;

	nread = -1;
	tmpbuf = (char *)ft_calloc(BUFFER_SIZE + 1, sizeof(char));
	if (!tmpbuf)
		return (NULL);
	while ((!ptr[0] && !ft_memchr(tmpbuf, '\n', BUFFER_SIZE)) && nread)
	{
		if (nread < 0)
			nread = 0;
		nread = read(fd, tmpbuf + nread, BUFFER_SIZE);
		if (nread >= 1 && add_to_stat(ptr, &tmpbuf, &nread))
			;
		else if (nread < 0)
			return (free_null(&tmpbuf),  NULL);
	}
	if (!tmpbuf[0] && ptr[0])
		ft_memcpy(tmpbuf, ptr, ft_strlen(ptr));
	return (clean_return(ptr, tmpbuf));
}
