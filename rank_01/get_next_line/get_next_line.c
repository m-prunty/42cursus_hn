/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maprunty <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/19 11:36:23 by maprunty          #+#    #+#             */
/*   Updated: 2025/10/28 20:43:35 by maprunty         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <unistd.h>

void *free_null(char **ptr)
{
	free(*ptr);
	*ptr = NULL;
	return (NULL);
}
/*
 *char	*clean_return(char **ptr)
{
	char	*tmp;
	char	*sub;
	size_t	nl;
	size_t	nptr;

	if (!*ptr)
		return (NULL);
	tmp = *ptr;
	nptr = ft_strlen(tmp);
	*ptr = (char *)ft_memchr(tmp, '\n', nptr);
	nl = 0;
	if (*ptr)
		nl = (*ptr + 1  - tmp);
	*ptr = NULL;
	if (nl)
	{
		sub = malloc(sizeof(char) * (nl + 1));
		if (!sub)
			return (free_null(&tmp), NULL);
		ft_memcpy(sub, tmp, nl);
		sub[nl] = '\0';
		if (nl < nptr)
		{
			*ptr = malloc(sizeof(char) * (nptr + 1));
			if (!*ptr)
				return (free_null(&sub), free_null(&tmp), NULL);
			ft_memcpy(*ptr, tmp + nl, nptr);
			(*ptr)[nptr] = '\0';
		}
		free(tmp);
	}
	else
	{
		sub = malloc(sizeof(char) * (nptr + 1));
		if (!sub)
			return (free_null(&tmp), NULL);
		ft_memcpy(sub, tmp, nptr);
		sub[nptr] = '\0';
		free(tmp);
	}
	return (sub);
}


 * */
char	*clean_return(char **ptr)
{
	char	*tmp;
	char	*sub;
	size_t	nl;
	size_t	nptr;

	tmp = *ptr;
	nptr = ft_strlen(tmp);
	*ptr = (char *)ft_memchr(tmp, '\n', nptr);
	nl = 0;
	if (*ptr)
		nl = (*ptr + 1  - tmp);
	*ptr = NULL;
	if (nl)
		sub = malloc(sizeof(char) * (nl + 1));
	else
	{
		sub = malloc(sizeof(char) * (nptr + 1));
		nl = nptr;
	}
	if (!sub)
		return (free_null(&tmp), NULL);
	ft_memcpy(sub, tmp, nl);
	sub[nl] = '\0';
	if (nl && nl < nptr)
	{
		*ptr = malloc(sizeof(char) * (nptr - nl + 1));
		if (!*ptr)
			return (free_null(&sub), free_null(&tmp), NULL);
		ft_memcpy(*ptr, tmp + nl, nptr - nl);
		(*ptr)[nptr - nl] = '\0';
	}
	free(tmp);
	return (sub);
}

int	add_to_stat(char **ptr, char *buf, int *nread)
{
	int		n;
	char	*tmp;

	n = 0;
	if (*ptr)
		n = ft_strlen(*ptr);
	tmp = (char *)malloc(sizeof(char) * (n + *nread + 1));
	if (!tmp)
	{
		*nread = -1;
		return (0);
	}
	ft_memcpy(tmp, *ptr, n);
	ft_memcpy(tmp + n, buf, *nread);
	tmp[n + *nread] = '\0';
	free(*ptr);
	*ptr = tmp;
	return (1);
}

char	*get_next_line(int fd)
{
	static char	*ptr = NULL;
	char		*buf;
	int			nread;

	nread = 1;
	buf = (char *)ft_calloc(BUFFER_SIZE + 1, sizeof(char));
	if (!buf)
		return (free_null(&ptr), NULL);
	while ((!ptr || !ft_memchr(buf, '\n', nread)) && nread)
	{
		nread = read(fd, buf, BUFFER_SIZE);
		if (nread >= 1 && add_to_stat(&ptr, buf, &nread))
			;
			else if (nread < 0)
			return (free_null(&buf), free_null(&ptr),  NULL);
	}
	if (buf)
		free_null(&buf);
	if (ptr || nread)
		return (clean_return(&ptr));
	return (NULL);
}
