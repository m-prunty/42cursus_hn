/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maprunty <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/19 11:36:23 by maprunty          #+#    #+#             */
/*   Updated: 2025/10/24 23:25:13 by maprunty         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*clean_return(char **ptr)
{
	char *nl;
	char *tmp;
	char *sub;

	nl = ft_strchr(*ptr, '\n');
	if (nl)
	{
		tmp = *ptr;
		sub = ft_substr(*ptr, 0, nl + 1 - *ptr);
		if (ft_strlen(sub) < ft_strlen(*ptr))
			*ptr = ft_substr(*ptr, nl + 1 - *ptr, ft_strlen(*ptr) - (nl + 1 - *ptr));
		else
			*ptr = "";
		free(tmp);
		return (sub);
	}
	return (*ptr);
}

char	*get_next_line(int fd)
{
	static char	*ptr = "";
	char		buf[BUFFER_SIZE];
	char		*tmp;
	int			nread;

	nread = 1;
	ft_bzero(buf, BUFFER_SIZE);
	tmp = NULL;
	while ((!*ptr || !ft_strchr(ptr, '\n')) && nread)
	{
		nread = read(fd, buf, BUFFER_SIZE);
		if (nread >= 1)
		{
			tmp = ptr;
			ptr = ft_strjoin(ptr, buf);
			if (*tmp)
				free(tmp);
		}
		else if (nread < 0)
			return (free(ptr), NULL);
	}
	if (*ptr)
		return (clean_return(&ptr));
	return (NULL);
}
