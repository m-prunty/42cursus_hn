/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maprunty <maprunty@student.42heilbronn.de  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/15 22:34:52 by maprunty          #+#    #+#             */
/*   Updated: 2025/09/16 08:21:24 by maprunty         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include "ft_printf.h"
#include <stddef.h>
#include <string.h>

typedef struct s_gnl
{
	struct s_gnl	*next;
	char	*buf;
}	t_gnl;

char *ft_strldup(const char *s, size_t l)
{
	char	*dup;
	size_t	n;

	n = ft_strlen(s) + 1;
	if (n < l)
		l = n;
	dup	= malloc(sizeof(char) * l);

	if (!dup)
		return (NULL);
	ft_strlcpy(dup, s, l);
	return (dup);
}
/*
char *gnl_return(char *str, int n)
{
	ft_strjoin(str, const char *s2);	
}
 */
char	*gnl_strcat(char *ptr, char *src )
{
	char *tmp;
	int n_ptr;
	int n_src;

	n_ptr = 0;
	n_src = 0;
	if (ptr)
		n_ptr = ft_strlen(ptr);
	n_src = ft_strlen(src);
	tmp = ptr;
	ptr = malloc(sizeof(char) * (n_ptr + n_src + 1));
	if (tmp)
	{
		ft_strlcat(ptr, tmp, n_ptr + 1);
		free(tmp);
	}
	ft_strlcat(ptr, src, n_ptr + n_src + 1);
	return (ptr);
}

char	*gnl_handle_return(char **ptr, char *nl)
{
	char *tmp;
	int		d;

	if (!nl)
		nl = strchr(*ptr, '\n');
	d = (nl - *ptr) + 1;
	nl = ft_substr(*ptr, 0, d);
	tmp = *ptr;
	if (tmp && ft_strlen(*ptr + d))
		*ptr = ft_substr(*ptr, d, ft_strlen(*ptr));
	else
		*ptr = NULL;
	free(tmp);
	return (nl);	

}

char *get_next_line(int fd)
{
	static char *ptr;
	char	buf[BUFFER_SIZE + 1];
	char	*nl;
	int		n;
	//char *nl;
	
	ft_bzero(buf, BUFFER_SIZE);
	nl = NULL;
	if (ptr)
		nl = strchr(ptr, '\n');
	if (!nl)
	{
		while (!ft_strchr(buf, '\n'))
		{
			n = read(fd, buf, BUFFER_SIZE);
			buf[n] = 0;
			ptr = gnl_strcat(ptr, buf );
			//ft_memcpy(ret, buf, i);
			//ft_printf("\nbuf|%s|", ptr);
		}
	}
	nl = gnl_handle_return(&ptr, nl);
/*	else
	{
		if ((ptr - nl))
		ft_printf("\nbuf2|%s|", ptr);
	}	
*/
//	if (ptr)
	//ft_printf("\nnl|%s|", nl);
	return (nl);
}

