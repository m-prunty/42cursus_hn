/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maprunty <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/19 11:36:23 by maprunty          #+#    #+#             */
/*   Updated: 2025/11/06 06:17:21 by maprunty         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stddef.h>
#include <unistd.h>
#define CHUNK 1024

char	*clean_return(char **ptr)
{
	char	*ptr_ret;
	char	*nl_ret;
	size_t	n[2];

	n[1] = ft_strlen(*ptr);
	n[0] = 0;
	ptr_ret = (char *)ft_memchr(*ptr, '\n', n[1]);
	if (ptr_ret)
		n[0] = (ptr_ret - *ptr + 1);
	ptr_ret = NULL;
	if (!n[0])
		n[0] = n[1];
	if (!calloc_protect(&nl_ret, sizeof(char) * (n[0] + 1)))
		return (free_null(&ptr_ret), NULL);
	ft_memcpy(nl_ret, *ptr, n[0]);
	if (n[0] < n[1])
	{	
		if (!calloc_protect(&ptr_ret, sizeof(char) * (n[1] - n[0] + 1)))
			return (free_null(&nl_ret), free_null(ptr), NULL);
		ft_memcpy(ptr_ret, *ptr + n[0], n[1] - n[0]);
		ptr_ret[n[1] - n[0]] = '\0';
	}
	free(*ptr);
	*ptr = ptr_ret; 
	return (nl_ret);
}



int	add_to_stat(char **ptr, char *buf, int *nread)
{
	size_t	cur_n;
	size_t	sz;
	size_t	n;
	char	*tmp;

	n = 0;
	if (*ptr)
		n = ft_strlen(*ptr);
	sz = n + *nread + 1;
	cur_n = (( n - 1 + CHUNK) / CHUNK);
	if (!*ptr || sz + 1 >= CHUNK * (cur_n ))
	{
		if (!calloc_protect(&tmp, CHUNK * (cur_n + 1)))
		{
			*nread = -1;
			return (0);
		}
		if (*ptr && ft_memcpy(tmp, *ptr, n))
			free(*ptr);
		*ptr = tmp;
	}
	ft_memcpy(*ptr + n, buf, *nread);
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
		ft_bzero(buf, BUFFER_SIZE + 1);
		nread = read(fd, buf, BUFFER_SIZE);
		if (nread >= 1 && add_to_stat(&ptr, buf, &nread))
			;
		else if (nread < 0)
			return (free_null(&buf), free_null(&ptr), NULL);
	}
	if (buf)
		free_null(&buf);
	if (ptr || nread)
		return (clean_return(&ptr));
	return (NULL);
}
