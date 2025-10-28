/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maprunty <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/23 16:03:04 by maprunty          #+#    #+#             */
/*   Updated: 2025/10/28 11:41:59 by maprunty         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

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

char    *ft_strchr(const char *s, int c)
{
    int i;
    int n;

    i = 0;
    n = ft_strlen(s);
    while (i <= n)
    {   
        if (*(s + i) == (char)c)
            return ((char *)s + i); 
        i++;
    }   
    return (NULL);
}

size_t  ft_strlcat(char *dst, const char *src, size_t size)
{
    size_t  nsrc;
    size_t  ndst;
    size_t  cpy;

    nsrc = ft_strlen(src);
    ndst = ft_strlen(dst);
    if (ndst >= size)
        return (nsrc + size);
    if (nsrc + ndst >= size)
        cpy = size - ndst - 1;
    else
        cpy = nsrc;
    if (size > 0)
    {
        ft_memcpy(dst + ndst, src, cpy);
        dst[ndst + cpy] = '\0';
    }
    return (nsrc + ndst);
}   
size_t  ft_strlcpy(char *dst, const char *src, size_t size)
{
    size_t  n;
    size_t  cpy;
    
    n = ft_strlen(src);
    if (n >= size)
        cpy = size - 1;
    else
        cpy = n;
    if (size > 0)
    {
        ft_memcpy(dst, src, cpy);
        dst[cpy] = '\0';
    }
    return (n);
} 
char    *ft_strjoin(char const *s1, char const *s2)
{
    char    *joint;
    int     n1;
    int     n2;

    n1 = ft_strlen(s1);
    n2 = ft_strlen(s2);
    joint = (char *)malloc(sizeof(char) * (n1 + n2 + 1));
    if (!joint)
        return (NULL);
    ft_strlcpy(joint, s1, n1 + 1);
    ft_strlcat(joint, s2, n1 + n2 + 1);
    return (joint);
}


char    *ft_substr(char const *s, unsigned int start, size_t len)
{
    char    *sub;
    size_t  n;

    n = ft_strlen(s);
    if (start >= n || len == 0)
	{
		sub = (char *)malloc(sizeof(char));
		if (!sub)
			return (NULL);
		ft_strlcpy(sub, "", 1);
        return (sub);
	}
	if (start + len > n)
        len = n - start;
    sub = (char *)malloc(sizeof(char) * (len + 1));
    if (!sub)
        return (NULL);
    ft_strlcpy(sub, s + start, len + 1);
    return (sub);
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
void	*ft_memchr(const void *s, int c, size_t n)
{
	const unsigned char	*us;
	unsigned char		uc;

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
