/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maprunty <maprunty@student.42heilbronn.de  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/15 22:38:15 by maprunty          #+#    #+#             */
/*   Updated: 2025/09/16 01:54:03 by maprunty         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H 
# define GET_NEXT_LINE_H

# define BUFFER_SIZE 10

#include "libft.h"
#include "ft_printf.h"
#include <stddef.h>
#include <unistd.h>

char *get_next_line(int fd);

#endif
