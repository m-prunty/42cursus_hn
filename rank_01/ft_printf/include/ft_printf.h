/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maprunty <maprunty@student.42heilbronn.de  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/10 05:42:04 by maprunty          #+#    #+#             */
/*   Updated: 2025/12/14 10:06:57 by maprunty         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <unistd.h>
# include <stdarg.h>
# include <stddef.h>
# include "libft.h"

# define SPECIFIER	"cspdiuxX%"
# define FLAGS		"-0# +"
# define LENMOD		"hlqLjzZt"
# define BASE		"0123456789abcdef"
# define FD			1

# if __APPLE__
#  define APPLE 1
# else
#  define APPLE 0
# endif

typedef enum e_flag
{
	NONE	= 0,
	MINUS	= 45,
	ZERO	= 48,
	HASH	= 35,
	SPACE	= 32,
	PLUS	= 43,
}	t_flag;

typedef struct s_format
{
	const char	*str;
	t_flag		flags[5];
	int			fd;
	int			n;
	int			len;
	int			isneg;
	va_list		ap;
	int			width;
	int			precision;
	char		spec;
	int			count;
}	t_format;

void				ft_parse_flags(t_format *fmt);
void				ft_parse_width(t_format *fmt);
void				ft_parse_precis(t_format *fmt);
void				ft_parse_spec(t_format *fmt);
int					ft_parse(t_format *fmt);

int					ft_render(t_format *fmt);
void				ft_init_format(t_format *fmt, const char *f_str);
int					ft_printf(const char *f_str, ...);
int					ft_printf_fd(int fd, const char *f_str, ...);

int					ft_isvalid_base(char *base);
void				ft_putnbr_base_fmt(long int n, char *base, t_format *fmt);
void				ft_putnbr_ptr(size_t n, t_format *fmt);

int					check_flags(t_format *fmt, t_flag f);
int					print_space(int n, int *count, int fd);
int					ft_putstr_n_fd(char *s, int n, int fd, int *count);
void				ft_putstr_fd_count(char *s, int fd, int *count);
void				ft_putchar_fd_count(char c, int fd, int *count);
size_t				ft_strlen_safe(const char *s);

int					ft_render_chars(t_format *fmt,
						unsigned char *s, unsigned char c[2]);
void				ft_iter_up(unsigned int i, char *c);
int					ft_count_digits_base(unsigned long long n,
						int base, t_format *fmt);

void				handle_zero(t_format *fmt, int res);
void				handle_precis(t_format *fmt, int res);
void				handle_prefix(t_format *fmt, unsigned long long res);
void				handle_width(t_format *fmt, int print);

void				just_left(unsigned long long res,
						char *base_s, t_format *fmt);
void				just_right(unsigned long long res,
						char *base_s, t_format *fmt);
int					ft_render_nums(t_format *fmt);

unsigned long long	get_value(t_format *fmt);
int					if_apple(t_format *fmt);

#endif
