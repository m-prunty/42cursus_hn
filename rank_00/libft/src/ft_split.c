/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maprunty <maprunty@student.42heilbronn.de  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/05 15:42:37 by maprunty          #+#    #+#             */
/*   Updated: 2025/10/14 16:38:21 by maprunty         ###   ########.fr       */
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

//static void	_help_split(char **s, char **res, char c)
//{
//	int	n;
//
//	if (!ft_strchr(*s, c))
//		n = ft_strlen(*s);
//	else
//		n = ft_strchr(*s, c) - *s;
//	res[i++] = ft_substr(*s, 0, n);
//	*s += n;
//}
/*
void *_chk_res(char **res, int n)
{
	int i;

	i = -1;
	while (++i < n)
	{
		if (!res[i])
		{
			i = -1; 
			while(res[++i])
				free(res[i]);
		}
	}
	return (NULL);
}
*/
void	ft_for_sarr(char** sarr, int length)
{
	while (length--)
		free(sarr++);
}

char	*_assign_sub(char **res, int i, char *sub)
{
	if (!sub)
		ft_for_sarr(res, i);
	return (sub);
}

char	**ft_split(char const *s, char c)
{
	char	**res;
	int		i;
	int		n;

	i = 0;
	res = (char **)malloc(sizeof(char *) * ((ft_count(s, c)) + 1));
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
			s += n;
			i++;
		}
	}
	res[i] = NULL;
	return (res);
}
