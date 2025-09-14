/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_render.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maprunty <maprunty@student.42heilbronn.de  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/11 18:54:21 by maprunty          #+#    #+#             */
/*   Updated: 2025/09/14 09:59:47 by maprunty         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */



#include "ft_printf.h"
/*
 *        c      If no l modifier is present, the int argument is converted to an
              unsigned  char, and the resulting character is written.  If an l
              modifier is present, the wint_t  (wide  character)  argument  is
              converted  to  a  multibyte sequence by a call to the wcrtomb(3)
              function, with a conversion state starting in the initial state,
              and the resulting multibyte string is written.

       s      If no l modifier is present: the const char *  argument  is  ex‐
              pected to be a pointer to an array of character type (pointer to
              a string).  Characters from the array are written up to (but not
              including)  a  terminating  null  byte ('\0'); if a precision is
              specified, no more than the number specified are written.  If  a
              precision  is given, no null byte need be present; if the preci‐
              sion is not specified, or is greater than the size of the array,
              the array must contain a terminating null byte.

              If an l modifier is present: the const wchar_t * argument is ex‐
              pected to be a pointer to an array  of  wide  characters.   Wide
              characters  from the array are converted to multibyte characters
              (each by a call to the wcrtomb(3) function,  with  a  conversion
              state  starting in the initial state before the first wide char‐
              acter), up to and including a terminating null  wide  character.
              The  resulting  multibyte  characters are written up to (but not
              including) the terminating null byte.  If a precision is  speci‐
              fied,  no  more bytes than the number specified are written, but
              no partial multibyte characters are written.  Note that the pre‐
              cision determines the number of bytes written, not the number of
              wide characters or screen positions.  The array must  contain  a
              terminating null wide character, unless a precision is given and
              it  is  so small that the number of bytes written exceeds it be‐
              fore the end of the array is reached.

 */

/*
 * for 'c' sapecifier only meaningful modifiers are width and negative width 
 * e.g %5c and %-5c 
 * all others are ignored
 *
 * 
 * for 's' specifier only meaningful modifiers are width, negative width, and precision(truncates) 
 * e.g %5s and %-5s %.5s
 * all others are ignored
 *
 */
int	check_flags(t_format *fmt, e_flag f)
{
	int i;

	i = -1;
	while (fmt->flags[++i])
		if (fmt->flags[i] == f)
			return (1);
	return (0);
}

int	print_space(int n)
{
	int	i;

	i = -1;
	while (++i < n)
		ft_putchar_fd(' ', FD);
	return (i);
}

int ft_putstr_n_fd(char *s, int n, int fd)
{
	int i;

	i = -1;
	while (++i < n && s[i])
		ft_putchar_fd(s[i], fd);
	return (i);
}

		



int	ft_render_chars(t_format *fmt)
{
	char	*s;
	char	c;
	int		slen;

	if (fmt->spec == 'c')
	{
		c = (char)va_arg(fmt->ap, int);
		s = (char *)&c;
		slen = 1;
	}
	else
	{
		s = (char *)va_arg(fmt->ap, char *);
		slen = ft_strlen(s);
	}
	if (fmt->precision >= 0 && fmt->spec == 's')
		slen = fmt->precision;
	if (fmt->width && !check_flags(fmt, MINUS))
		print_space(fmt->width - slen);
	ft_putstr_n_fd(s, slen, FD);
	if (fmt->width && check_flags(fmt, MINUS))
		print_space(fmt->width - slen);
	return (1); 
}


void	ft_iter_up(unsigned int i, char *c)
{
	(void)i;
	if (ft_islower(*c))
		*c = *c - 32;
}
char *get_base(t_format *fmt, char *base_s)
{
//	char base_s[16];
	
	if (ft_strchr("id", fmt->spec))
		ft_strlcpy(base_s, BASE, 11);
	else if (ft_strchr("uxXp", fmt->spec))
		ft_strlcpy(base_s, BASE, 17);
	if (ft_isupper(fmt->spec))
		ft_striteri(base_s, ft_iter_up);
	return (base_s); 
}

int	ft_render_nums(t_format *fmt)
{
	int res;
	char base_s[17];
	res = (int)va_arg(fmt->ap, int);
	//res = ft_atoi_base((char *)fmt->str, "01");
	get_base(fmt, base_s);
	ft_putnbr_base(res, base_s);
	//free(base_s);
	return (1);
}

int	ft_render(t_format *fmt)
{
	//	int	n;

	if (ft_strchr("cs", fmt->spec))
		ft_render_chars(fmt);
	else if (ft_strchr("pdiuxX", fmt->spec))
		ft_render_nums(fmt);	
	//n = fmt.

	return (0);
}

