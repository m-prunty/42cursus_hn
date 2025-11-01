/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maprunty <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/19 11:36:23 by maprunty          #+#    #+#             */
/*   Updated: 2025/10/29 20:18:00 by maprunty         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stddef.h>
#include <unistd.h>

void	*free_null(char **ptr)
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

int	calloc_protect(char **to_calloc, size_t n)
{
	*to_calloc = ft_calloc(n, 1);
	if (*to_calloc)
		return (1);
	return (0);
}



char	*clean_return(char **ptr)
{
	char	*ptr_ret;
	char	*nl_ret;
	size_t	n[2];


	n[1] = ft_strlen(*ptr);
	n[0] = 0;
	ptr_ret = (char *)ft_memchr(*ptr, '\n', n[1]);
	if (ptr_ret)
		n[0] = (ptr_ret + 1 - *ptr);
	//ptr = NULL;
	if (!n[0])
		n[0] = n[1];
	if (!calloc_protect(&nl_ret, sizeof(char) * (n[0] + 1)))
		return (free_null(&ptr_ret), NULL);
	ft_memcpy(nl_ret, *ptr, n[0] + 1);
	if (n[0] && n[0] < n[1])
	{	
		if (!calloc_protect(ptr, sizeof(char) * (n[1] - n[0] + 1)))
			return (free_null(&nl_ret), free_null(&ptr_ret), NULL);
		ft_memcpy(*ptr, ptr_ret + n[0], n[1] - n[0]);
		(*ptr)[n[1] - n[0]] = '\0';
	}
	return (nl_ret);
}

/*
void *subdup(char **ptr, char *src, size_t start, size_t len)
{
	char	*out;
	
	out = *ptr;
	if (!len)
		return (NULL);
	if (!calloc_protect(&out, sizeof(char) * (len + 1)))
		return (NULL);
	ft_memcpy(out, src + start, len);
	out[len] = '\0';
	return (out);
}
char	*clean_return(char **ptr)
{
	char    *tmp[2];
	size_t  n[2];

	tmp[0] = *ptr;
	n[1] = ft_strlen(tmp[0]);
	n[0] = 0;
	*ptr = (char *)ft_memchr(tmp[0], '\n', n[1]);
	if (*ptr)
		n[0] = (*ptr + 1 - tmp[0]);
	*ptr = NULL;
	if (!n[0])
		n[0] = n[1];
	if (!subdup(&tmp[1], tmp[0], 0, n[0]))
		return (free_null(&tmp[0]), NULL);
	if (n[0] && n[0] < n[1])
	{
		if (!subdup(ptr, tmp[0], 0, n[1]))
			return (free_null(&tmp[1]), free_null(&tmp[0]), NULL);
	}
	free(tmp[0]);
	return (tmp[1]);
}
*/



#define CHUNK 1024

int	add_to_stat(char **ptr, char *buf, int *nread)
{
	int		cur_n;
	int		n;
	char	*tmp;

	n = 0;
	tmp = *ptr;
	if (tmp)
		n = ft_strlen(*ptr);
	cur_n = ((n + *nread) / CHUNK) + 1;
	if ((!tmp || (n + *nread  >= CHUNK * cur_n)) &&
		 !calloc_protect(&tmp, CHUNK * (cur_n + 1)))
	{
		*nread = -1;
		return (0);
	}
	ft_memcpy(tmp + n, buf, *nread);
	tmp[n + *nread] = '\0';
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
		ft_bzero(buf, '\0');
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
