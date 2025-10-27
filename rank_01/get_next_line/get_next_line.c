/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maprunty <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/19 11:36:23 by maprunty          #+#    #+#             */
/*   Updated: 2025/10/27 17:27:59 by maprunty         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*clean_return(char **ptr)
{
	char *nl;
	char *tmp;
	char *sub;
	int	n;

	nl = ft_strchr(*ptr, '\n');
	if (nl)
	{
		tmp = *ptr;
		sub = ft_substr(*ptr, 0, nl + 1 - *ptr);
		if (ft_strlen(sub) < ft_strlen(*ptr))
			*ptr = ft_substr(*ptr, nl + 1 - *ptr, ft_strlen(*ptr) - (nl + 1 - *ptr));
		else
			*ptr = NULL;
		free(tmp);
	}
	else
	{
		n = ft_strlen(*ptr);
		sub = malloc(sizeof(char) * n + 1);
		ft_memcpy(sub, *ptr, n);
		sub[n] = '\0';
		free(*ptr);
		*ptr = NULL;
	}
	return (sub);
}

void	add_to_stat(char **ptr, char *buf, int nread)
{
	int n;
	char	*tmp;

	n = 0;
	if (*ptr)
		n = ft_strlen(*ptr);
	tmp = (char *)malloc(sizeof(char) * (n + nread + 1));
	ft_memcpy(tmp, *ptr, n);
	ft_memcpy(tmp + n, buf, nread);
	tmp[n + nread] = '\0';
	free(*ptr);
	*ptr = tmp;
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
		if (nread >= 1)
			add_to_stat(&ptr, buf, nread);
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
