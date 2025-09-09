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

int	ft_isspace(int c)
{
	if (c == 32 || (c >= 9 && c <= 13))
		return (1);
	return (0);
}

int ft_atoi(const char *nptr)
{
	int	neg;
	int	res;

	neg = 1;
	res = 0;
	--nptr;
	while (ft_isspace(*++nptr))
		;
	if (*nptr == '+' || *nptr == '-' )
		if (*nptr++ == '-')
			neg *= -1;
	while (ft_isdigit(*nptr))
		res = res * 10 + (*nptr++ - '0');
	return (res * neg);
}


