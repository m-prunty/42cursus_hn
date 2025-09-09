/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maprunty <maprunty@student.42heilbronn.de  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/05 15:42:37 by maprunty          #+#    #+#             */
/*   Updated: 2025/09/09 08:00:31 by maprunty         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>
/*
 *

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
	i = 0;
	while (tmp)
	{
		if (*tmp !=c)
			i++;
		while (*tmp == c)
			tmp++;
		tmp = ft_strchr(tmp, c);
		if (tmp)
			i++;
	}
	return (i);
}

char	**ft_split(char const *s, char c)
{
	char const	*tmp;
	char		**res;
	int			n;
	int			i;

	i = 0;
	n = ft_count(s, c);
	res = (char **)malloc(sizeof(char *) * (n + 1));
	tmp = s;
	while (tmp && *s)
 	{
		while(*tmp == c)
			tmp++;
		if (*tmp != c)
		{
			s = tmp;
			tmp = ft_strchr(s, c);
			if (!tmp)
				res[i++] = ft_strdup(s);
			else
				res[i++] = ft_substr(s, 0, tmp - s);
		}
	}
	res[n] = NULL;
	return (res);
}
