/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maprunty <maprunty@student.42heilbronn.de  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/05 15:42:37 by maprunty          #+#    #+#             */
/*   Updated: 2025/09/06 20:22:20 by maprunty         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	n;
	size_t	ndst;
	size_t	cpy;

	n = ft_strlen(src);
	ndst = ft_strlen(dst);
	
	if (ndst >= size)
		return (n + size);
	if (n >= size)
		cpy = size - ndst - 1;
	else
		cpy = n;
	if (size > 0)
	{
		ft_memcpy(dst + ndst, src, cpy);
		dst[ndst + cpy] = '\0';
	}
	return (n + ndst);

}
