/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maprunty <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/19 11:36:23 by maprunty          #+#    #+#             */
/*   Updated: 2025/11/21 21:27:52 by maprunty         ###   ########.fr       */
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
char *clean_return(char ptr[], char **tmp)
{
    char    *nl;
    char    *line;
    size_t  len;
    size_t  tail_len;

    nl = ft_memchr(*tmp, '\n', ft_strlen(*tmp));
    if (nl)
        len = (nl - *tmp) + 1;
    else
        len = ft_strlen(*tmp);

    line = malloc(len + 1);
    if (!line)
        return (NULL);

    ft_memcpy(line, *tmp, len);
    line[len] = '\0';
    tail_len = ft_strlen(*tmp + len);
    ft_memmove(ptr, *tmp + len, tail_len);
    ptr[tail_len] = '\0';
	free_null(tmp);
    return (line);
}

int add_to_stat(char **tmpbuf, char *buf, int *nread)
{
    size_t	n;
	char	*tmp;
	
	n = 0;
	if (*tmpbuf)
		n = ft_strlen(*tmpbuf);
	tmp = ft_calloc(n + *nread + 1, sizeof(char));
	if (!tmp)
	{
		*nread = 0;
		return (0);
	}
	ft_memcpy(tmp, *tmpbuf, n);
    ft_memcpy(tmp + n, buf, *nread);
    tmp[n + *nread] = '\0';
	if (n)
		free_null(tmpbuf);
	*tmpbuf = tmp;
    return (1);
}

char *get_next_line(int fd)
{
	static char ptr[BUFFER_SIZE + 1] = {0};
	char        *buf;
	char        *tmpbuf;
	int         nread;

	buf = (char *)ft_calloc(BUFFER_SIZE + 1, sizeof(char));
	if (!buf)
		return (NULL);
	tmpbuf = "";//ft_calloc(ft_strlen(ptr) + 1, sizeof(char));
	nread = 1;
	if (ptr[0])
	{
		nread = ft_strlen(ptr);
		ft_memcpy(buf, ptr, ft_strlen(ptr));
	}
	while ((!ft_memchr(tmpbuf, '\n', ft_strlen(tmpbuf)) && nread > 0) || ptr[0])
	{ 
		if (!ptr[0])
		{
			ft_bzero(buf, BUFFER_SIZE + 1);
			nread = read(fd, buf, BUFFER_SIZE);
		}
		else
			ft_bzero(ptr, BUFFER_SIZE + 1);
		if (nread > 0 && add_to_stat(&tmpbuf, buf, &nread))
			;
		else if (nread < 0)
			return (free_null(&buf), NULL);
	}
	free_null(&buf);
	if (*tmpbuf)
		return ( clean_return(ptr, &tmpbuf));
	return ( NULL);
}


/*
   char	*clean_return(char ptr[], char *buf)
   {	char	*nl;
   char	*sub;
   size_t	n;

   nl = ft_strchr(buf, '\n');
   if (nl)
   n = nl - buf + 1;
   else
   n = ft_strlen(buf);
   sub = ft_calloc(sizeof(char), n  + 1);
   if (!sub)
   return (NULL);
   ft_memcpy(sub, buf, n);
   ft_memmove(ptr, buf + n, ft_strlen(buf + n));		
   ptr[ft_strlen(buf + n)] = '\0';
   free(buf);
   return (sub);
   }

   int	add_to_stat(char **tmpbuf, char **buf, int *nread)
   {
   int		n;
   char	*tmp;

   n = 0;
   if (*tmpbuf != *buf)
   n = ft_strlen(*tmpbuf);
   tmp = (char *)ft_calloc((n + *nread + 1), sizeof(char));
   if (!tmp)
   {
 *nread = -1;
 return (0);
 }

 ft_memcpy(tmp, *tmpbuf, n);
 ft_memcpy(tmp + n, *buf, *nread);
 tmp[n + *nread] = '\0';

 if (*tmpbuf != *buf)
 free(*tmpbuf);
 *tmpbuf = tmp;
 return (1);
 }

 char	*get_next_line(int fd)
 {
 static char	ptr[BUFFER_SIZE + 1] = {0};
 char		*buf;
 char		*tmpbuf;
 int			nread;

 nread = -1;
 tmpbuf = NULL;
 buf = (char *)ft_calloc(BUFFER_SIZE + 1, sizeof(char));
 if (!buf)
 return (NULL);
 while ((!ptr[0] && !ft_strchr(buf, '\n')) || ft_strchr(ptr ) && nread)
 {
 ft_bzero(buf, BUFFER_SIZE);
 nread = read(fd, buf, BUFFER_SIZE);
 if (!tmpbuf)
 tmpbuf = buf;
 if (nread >= 1 && add_to_stat(&tmpbuf, &buf, &nread))
 ;
 else if (nread < 0)
 return (free_null(&buf),  NULL);
 }
 if (!buf[0] && ptr[0])
 {
tmpbuf = buf;
ft_memcpy(tmpbuf, ptr, ft_strlen(ptr));
}
return (clean_return(ptr, tmpbuf));
}*/
