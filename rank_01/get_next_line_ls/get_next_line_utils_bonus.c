/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maprunty <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/23 16:03:04 by maprunty          #+#    #+#             */
/*   Updated: 2025/11/27 16:01:32 by maprunty         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

void	ft_bzero(void *s, size_t n)
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

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	unsigned char		*d;
	const unsigned char	*s;

	if (!dest && !src)
		return (NULL);
	d = dest;
	s = src;
	while (n--)
		*d++ = *s++;
	return (dest);
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

void	ft_gnlclear(t_gnl **gnlbuf)
{
	t_gnl	*tmp;

	while (*gnlbuf)
	{
		tmp = ((*gnlbuf)->next);
		free((*gnlbuf)->content);
		(*gnlbuf)->content = NULL;
		free(*gnlbuf);
		*gnlbuf = tmp;
	}
}
