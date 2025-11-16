/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maprunty <maprunty@student.42heilbronn.de  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/05 15:42:37 by maprunty          #+#    #+#             */
/*   Updated: 2025/10/10 20:18:14 by maprunty         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	while ((s1[0] || s2[0]) && n--)
	{
		if (s1[0] - s2[0])
			return (*(unsigned char *)s1 - *(unsigned char *)s2);
		s1++;
		s2++;
	}
	return (0);
}
/*
{
	int	cmp;

	cmp = *(const unsigned char *)s1 - *(const unsigned char *)s2;
	if (!(cmp) && n && *s1 && *s2)
		return (ft_strncmp(++s1, ++s2, --n));
	else //if (!n)
		return (0);
	return (cmp);
}
*/
