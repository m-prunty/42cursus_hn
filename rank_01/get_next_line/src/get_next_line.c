/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maprunty <maprunty@student.42heilbronn.de  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/15 22:34:52 by maprunty          #+#    #+#             */
/*   Updated: 2025/09/16 02:13:13 by maprunty         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include "ft_printf.h"

char *ft_strldup(const char *s, size_t l)
{
	char	*dup;
	int		n;

	n = ft_strlen(s) + 1;
	if (n <= l)
		dup	= malloc(sizeof(char) * n);

	if (!dup)
		return (NULL);
	ft_strlcpy(dup, s, n);
	return (dup);
}

char *gnl_return(char *str, int n)
{
	ft_strjoin(const char *s1, const char *s2)	
}


char *get_next_line(int fd)
{
	static char *ptr;
	char	buf[BUFFER_SIZE + 1];
	char	*ret;
	int		i;
	//char *nl;
	i = 1;
	while (!ptr && i)
	{
		i = read(fd, buf, BUFFER_SIZE);
		buf[i] = 0;
		ptr = ft_strchr(buf, '\n');
		ret = gnl_return(buf, int n)
		ft_printf("\nbuf|%s|", buf);
	}
	if (ptr)
		ft_printf("\nptr|%s|", ptr);
	return (NULL);
}

