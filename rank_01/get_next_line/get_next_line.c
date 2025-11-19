/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maprunty <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/19 11:36:23 by maprunty          #+#    #+#             */
/*   Updated: 2025/11/19 14:10:02 by maprunty         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

//int calloc_help(char *str, )

void *free_null(char **ptr)
{
	free(*ptr);
	*ptr = NULL;
	return (NULL);
}

char	*clean_return(char **ptr)
{	char	*nl;
	char	*tmp;
	char	*sub;
	size_t	n;

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
