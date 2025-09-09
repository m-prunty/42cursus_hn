/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalpha.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maprunty <maprunty@student.42heilbronn.de  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/05 15:42:37 by maprunty          #+#    #+#             */
/*   Updated: 2025/09/05 15:44:36 by maprunty         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
Parameters 
s1: The string to be trimmed.
set: The reference set of characters to trim.
Return value The trimmed string.
NULL if the allocation fails.

Description 
Allocates (with malloc(3)) and returns a copy of
’s1’ with the characters specified in ’set’ removed
from the beginning and the end of the string.
 */
char	*ft_strtrim(char const *s1, char const *set)
{
	int	n;
	int	i;

	i = -1;
	n = ft_strlen(s1);
	while (ft_strchr(set, s1[++i]))
		;
	while (ft_strchr(set, s1[--n]))
		;
	if (n - i <= 0)
		return (NULL);
	return (ft_substr(s1, i, n - i + 1));
}
