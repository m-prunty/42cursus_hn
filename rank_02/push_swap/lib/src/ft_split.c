/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maprunty <maprunty@student.42heilbronn.de  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/05 15:42:37 by maprunty          #+#    #+#             */
/*   Updated: 2026/01/02 00:09:34 by maprunty         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
Parameters 
s: The string to be split.
c: The delimiter character.

Return value The array of new strings resulting from the split.
NULL if the allocation fails.

External functs. malloc, free

Description Allocates (with malloc(3)) and returns an array
of strings obtained by splitting ’s’ using the
character ’c’ as a delimiter. The array must end
with a NULL pointer.
*/

int	ft_count(char const *s, char c)
{
	char	*tmp;
	int		i;

	tmp = (char *)s;
	if (!*s)
		return (0);
	i = 0;
	while (*tmp)
	{
		while (*tmp == c)
			tmp++;
		if (*tmp)
			i++;
		while (*tmp && *tmp != c)
			tmp++;
	}
	return (i);
}

static int	_iter_c(const char *s, char c)
{
	int	i;

	i = 0;
	while (*s == c && *s && i++)
		s++;
	return (i);
}

static int	_assign_sub(char **res, int i, char *sub)
{
	if (!sub)
	{
		while (i > 0)
			free(res[--i]);
		free(res);
		return (0);
	}
	res[i] = sub;
	return (1);
}

char	**ft_split(char const *s, char c)
{
	char	**res;
	int		i;
	int		n;

	i = 0;
	res = (char **)ft_calloc((ft_count(s, c) + 1), sizeof(char *));
	if (!res || !s)
		return (NULL);
	while (*s)
	{
		s += _iter_c(s, c);
		if (*s && *s != c)
		{
			if (!ft_strchr(s, c))
				n = ft_strlen(s);
			else
				n = ft_strchr(s, c) - s;
			if (!_assign_sub(res, i, ft_substr(s, 0, n)))
				return (NULL);
			s += n;
			i++;
		}
	}
	res[i] = NULL;
	return (res);
}
