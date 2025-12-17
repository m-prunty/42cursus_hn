/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maprunty <maprunty@student.42heilbronn.de  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/05 15:42:37 by maprunty          #+#    #+#             */
/*   Updated: 2025/12/17 22:20:00 by maprunty         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

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

char	*_assign_sub(char **res, int n, char *sub)
{
	if (!sub)
	{
		while (n > 0)
			free(res[--n]);
		free(res);
		return (NULL);
	}
	return (sub);
}

char	**ft_split(char const *s, char c)
{
	char	**res;
	int		i;
	int		n;
	
	i = 0;
	res = (char **)ft_calloc(((ft_count(s, c)) + 1),sizeof(char *));
	if (!res || !s)
		return (NULL);
	while (*s)
	{
		while (*s == c && *s)
			s++;
		if (*s && *s != c)
		{
			if (!ft_strchr(s, c))
				n = ft_strlen(s);
			else
				n = ft_strchr(s, c) - s;
			res[i] = _assign_sub(res, i, ft_substr(s, 0, n));
			if (!res[i])
				return(NULL);
			s += n;
			i++;
		}
	}
	return (res);
 }
