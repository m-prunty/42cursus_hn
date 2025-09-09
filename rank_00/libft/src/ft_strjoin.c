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
s1: The prefix string.
s2: The suffix string.

Return value The new string. NULL if the allocation fails.

Description Allocates (with malloc(3)) and returns a new
string, which is the result of the concatenation
of ’s1’ and ’s2’.
 */
char *ft_strjoin(char const *s1, char const *s2)
{
	char	*joint;
	int		n1;
	int		n2;

	n1 = ft_strlen(s1); 
	n2 = ft_strlen(s2);
	joint = (char *)malloc(sizeof(char) * (n1 + n2 + 1));
	ft_strlcpy(joint, s1, n1 + 1);
	ft_strlcat(joint, s2, n1 + n2 + 1);
	return (joint);
}
