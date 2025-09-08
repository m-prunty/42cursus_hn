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

int ft_memcmp(const void *s1, const void *s2, size_t n)
{
	int	cmp;

	cmp =  *(const unsigned char *)s1 - *(const unsigned char *)s2; 
	if (!(cmp) && n)
		return (ft_strncmp(++s1, ++s2, --n)); 	
	else if (!n)
		return (0);
	return (cmp);
}
