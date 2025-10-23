/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maprunty <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/19 11:36:23 by maprunty          #+#    #+#             */
/*   Updated: 2025/10/23 22:32:39 by maprunty         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*clean_return(char **ptr)
{
	char *nl;
	char *tmp;
	char *sub;

	nl = ft_strchr(*ptr, '\n') + 1;
	if (nl)
	{
		tmp = *ptr;
		sub = ft_substr(*ptr, 0, nl - *ptr);
		*ptr = ft_substr(*ptr, nl - *ptr, ft_strlen(*ptr) - (nl - *ptr));
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
	size_t		nread;

	nread = 1;
	ft_bzero(buf, BUFFER_SIZE);
	tmp = NULL;
	if (!*ptr)
		nread = read(fd, buf , BUFFER_SIZE);
	//buf[nread] = '\0';
	if (nread)
	{
		tmp = ptr;
		ptr = ft_strjoin(ptr, buf);
		if (*tmp)
			free(tmp);
	}
	if (*ptr)
		return (clean_return(&ptr));
	else
		return (NULL);
	return (get_next_line(fd));
}
