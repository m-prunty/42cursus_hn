/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maprunty <maprunty@student.42heilbronn.de  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/05 15:42:37 by maprunty          #+#    #+#             */
/*   Updated: 2025/09/10 02:31:44 by maprunty         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/* 

Parameters
n: The integer to output.
fd: The file descriptor on which to write.
Return value None

Description
Outputs the integer ’n’ to the given file
descriptor.
*/
void ft_putnbr_fd(int n, int fd)
{
	if (n <= (1 << 31))
	{
		ft_putchar_fd('-', fd);
		ft_putnbr_fd((~(long)(1 << 31) + 1) / 10 , fd);
		n = (n % 10) * -1;
	}
	else
	{
		if (n < 0)
		{
			ft_putchar_fd('-', fd);
			n *=-1;
		}
		if (n >= 10)
		{
			ft_putnbr_fd(n / 10, fd);
			n %= 10;
		}
	}
	if (n < 10)
		ft_putchar_fd(n + '0', fd);
}
