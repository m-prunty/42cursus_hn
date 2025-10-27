/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maprunty <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/19 11:36:23 by maprunty          #+#    #+#             */
/*   Updated: 2025/10/27 20:08:06 by maprunty         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*clean_return(char **ptr)
{	char	*nl;
	char	*tmp;
	char	*sub;
	size_t	n;

	tmp = *ptr;
	*ptr = NULL;
	nl = ft_strchr(tmp, '\n');
	n = ft_strlen(tmp);
	if (nl)
	{
		sub = ft_substr(tmp, 0, nl + 1 - tmp);
		if (!sub)
			return (free(tmp), NULL);
		if (ft_strlen(sub) < n)
		{
			*ptr = ft_substr(tmp, nl + 1 - tmp, ft_strlen(tmp) - (nl + 1 - tmp));
			if (!tmp)
				return (free(tmp), NULL);
		}
		else
			tmp = NULL;
		free(tmp);
	}
	else
	{
		sub = malloc(sizeof(char) * n + 1);
		if (!sub)
			return (free(tmp), NULL);
		ft_memcpy(sub, tmp, n);
		sub[n] = '\0';
		free(tmp);
		*ptr = NULL;
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
		free(*ptr);
		*ptr = NULL;
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
		return (NULL);
	while ((!ptr || !ft_strchr(ptr, '\n')) && nread)
	{
		nread = read(fd, buf, BUFFER_SIZE);
		if (nread >= 1 && add_to_stat(&ptr, buf, &nread))
			;
		else if (nread < 0)
		{
			free(ptr);
			ptr = NULL;
			return (free(buf), NULL);
		}
	}
	if (buf)
		free(buf);
	if (ptr || nread)
		return (clean_return(&ptr));
	return (NULL);
}
