/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maprunty <maprunty@student.42heilbronn.de  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/15 22:38:15 by maprunty          #+#    #+#             */
/*   Updated: 2025/11/27 16:53:28 by maprunty         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H

# ifndef FD_MAX
#  define FD_MAX 1024
# endif

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 10
# endif

# ifndef CHUNK
#  define CHUNK 1024
# endif

# ifndef CHUNK_SIZE
#  if CHUNK > BUFFER_SIZE
#   define CHUNK_SIZE CHUNK
#  else
#   define CHUNK_SIZE (BUFFER_SIZE + 1)
#  endif
# endif

# include <stddef.h>
# include <stdlib.h>
# include <stdint.h>
# include <unistd.h>
# include <fcntl.h>

typedef struct s_gnl
{
	struct s_gnl	*next;
	char			*content;
	size_t			n;
	int				nl;
}	t_gnl;

char	*get_next_line(int fd);

void	ft_gnlclear(t_gnl **gnlbuf);
void	ft_bzero(void *s, size_t n);
void	*ft_calloc(size_t nmemb, size_t size);
void	*ft_memchr(const void *s, int c, size_t n);
void	*ft_memcpy(void *dest, const void *src, size_t n);

#endif
