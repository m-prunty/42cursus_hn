/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalpha.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maprunty <maprunty@student.42heilbronn.de  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/05 15:42:37 by maprunty          #+#    #+#             */
/*   Updated: 2025/09/05 18:35:08 by maprunty         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
int ft_isupper(int c)
{
	if (c >= 'A' && c <= 'Z' )
		return (1<<8);
	return (0);
}

int ft_islower(int c)
{
	if (c >= 'a' && c <= 'z' )
		return (1<<9);
	return (0);
}

int ft_isalpha(int c)
{
	if (ft_islower(c) || ft_isupper(c))
		return (1<<10);
	return (0);
}
