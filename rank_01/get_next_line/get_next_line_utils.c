/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maprunty <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/23 16:03:04 by maprunty          #+#    #+#             */
/*   Updated: 2025/11/05 23:38:23 by maprunty         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"


void	*ft_calloc(size_t n, size_t size)
{
	void	*p;

	p = malloc(n * size);
	if (!p)
		return (NULL);
	ft_bzero(p, n * size);
	return (p);
}

int	calloc_protect(char **to_calloc, size_t n)
{
	*to_calloc = ft_calloc(n, 1);
	return (*to_calloc != NULL);
}

void	ft_bzero(void *s, size_t n)
{
	size_t			i;
	unsigned char	*p;

	p = (unsigned char *)s;
	i = 0;
	while (i < n)
		p[i++] = 0;
}

size_t	ft_strlen(const char *s)
{
	size_t	i = 0;

	if (!s)
		return (0);
	while (s[i])
		i++;
	return (i);
}

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	size_t			i;
	unsigned char	*d;
	const unsigned char	*s;

	if (!dst && !src)
		return (NULL);
	d = (unsigned char *)dst;
	s = (const unsigned char *)src;
	i = 0;
	while (i < n)
	{
		d[i] = s[i];
		i++;
	}
	return (dst);
}

void	*free_null(char **p)
{
	if (p && *p)
	{
		free(*p);
		*p = NULL;
	}
	return (NULL);
}
void	*ft_memchr(const void *s, int c, size_t n)
{
	const unsigned char	*us;
	unsigned char		uc;

	if (!s)
		return (NULL);
	us = (const unsigned char *)--s;
	uc = (unsigned char)c;
	if (n)
	{
		while (n-- && uc != *++us)
			;
		if (uc == *us)
			return ((void *)us);
	}
	return (NULL);
}


/* 
size_t  ft_strlen(const char *s)
{
    size_t  i;

    i = 0;
    while (*s++)
        i++;
    return (i);
}

void    *ft_memcpy(void *dest, const void *src, size_t n)
{
    unsigned char       *d;
    const unsigned char *s;

    if (!dest && !src)
        return (NULL);
    d = dest;
    s = src;
    while (n--)
        *d++ = *s++;
    return (dest);
}

void    ft_bzero(void *s, size_t n)
{
	while (n--)
		*(char *)s++ = '\0';
}   

void	*ft_calloc(size_t nmemb, size_t size)
{
	void		*p;
	long int	n;

	n = nmemb * size;
	if (n <= PTRDIFF_MAX)
		p = malloc(n);
	if (n > PTRDIFF_MAX || !p)
		return (NULL);
	ft_bzero((char *)p, n);
	return (p);
}


*/
