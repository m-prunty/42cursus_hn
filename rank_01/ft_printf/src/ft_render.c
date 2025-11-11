/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_render.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maprunty <maprunty@student.42heilbronn.de  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/11 18:54:21 by maprunty          #+#    #+#             */
/*   Updated: 2025/11/11 09:13:05 by maprunty         ###   ########.fr       */
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

int	print_space(int n, int *count)
{
	int	i;

	i = -1;
	while (++i < n)
		ft_putchar_fd_count(' ', FD, count);
	return (i);
}

int ft_putstr_n_fd(char *s, int n, int fd, int *count)
{
	int i;

	i = -1;
	while (++i < n)
		ft_putchar_fd_count(s[i], fd, count);
	return (i);
}

void    ft_putstr_fd_count(char *s, int fd, int *count)
{
	while (*s)
		ft_putchar_fd_count(*s++, fd, count);
}

size_t	ft_strlen_safe(const char *s)
{
	size_t	i;

	i = 0;
	while (s && *s++)
		i++;
	return (i);
}

int	ft_render_chars(t_format *fmt)
{
	unsigned char	*s;
	unsigned char	c;

	if (fmt->spec == 'c')
	{
		c = (unsigned char)va_arg(fmt->ap, int);
		s = (unsigned char *)&c;
		fmt->n = 1;
	}
	else
	{
		s = (unsigned char *)va_arg(fmt->ap, char *);
		if (!s && !check_flags(fmt, SPACE) && (fmt->precision < 0 || fmt->precision >= 6))
			s = (unsigned char *)"(null)";
		fmt->n = ft_strlen_safe((char *)s);
	}
	if (fmt->precision >= 0 && fmt->precision < fmt->n && fmt->spec == 's')
		fmt->n = fmt->precision;
	if (fmt->width && fmt->width > fmt->n && !check_flags(fmt, MINUS))
		print_space(fmt->width - fmt->n, &fmt->count);
	ft_putstr_n_fd((char *)s, fmt->n, FD, &fmt->count);
	if (fmt->width && check_flags(fmt, MINUS))
		print_space(fmt->width - fmt->n, &fmt->count);
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

	if (ft_strchr("idu", fmt->spec))
		ft_strlcpy(base_s, BASE, 11);
	else if (ft_strchr("xXp", fmt->spec))
		ft_strlcpy(base_s, BASE, 17);
	if (ft_isupper(fmt->spec))
		ft_striteri(base_s, ft_iter_up);
	return (base_s); 
}

/*
 *        d, i   The  int argument is converted to signed decimal notation.  The precision, if
 any, gives the minimum number of digits that must appear;  if  the  converted
 value  requires  fewer  digits, it is padded on the left with zeros.  The de‐
 fault precision is 1.  When 0 is printed with an explicit  precision  0,  the
 output is empty.

 o, u, x, X
 The  unsigned int argument is converted to unsigned octal (o), unsigned deci‐
 mal (u), or unsigned hexadecimal (x and X) notation.  The letters abcdef  are
 used  for  x conversions; the letters ABCDEF are used for X conversions.  The
 precision, if any, gives the minimum number of digits that  must  appear;  if
 the  converted value requires fewer digits, it is padded on the left with ze‐
 ros.  The default precision is 1.  When 0 is printed with an explicit  preci‐
 sion 0, the output is empty.

*/


int ft_iputnum_ptr(size_t n, t_format *fmt)
{   
	size_t  base;
	char    *symbols;

	symbols = "0123456789abcdef";
	base = 16;
	if (n < base)
		(ft_putchar_fd_count(symbols[n], FD, &fmt->count));
	else
	{
		ft_iputnum_ptr(n / base, fmt);
		ft_iputnum_ptr(n % base, fmt);
	}
	return (1);
}



int		ft_count_digits_base(unsigned long long n, int base, t_format *fmt)
{
	int base_len;

	base_len = 0;
	if (!n)
		return (1);
	if (ft_strchr("id", fmt->spec) )
	{
		if ((int)n < 0)
		{
			n *= -1;
			base_len += 1;
			if (fmt->precision > 0)
				base_len--;
		}
		while ((int)n)
		{
			n =	(int)n / base;
			base_len += 1;
		}
	}
	while (n)
	{
		n /= base;
		base_len += 1;
	}
	return (base_len);
}

void handle_zero(t_format *fmt)
{
	static int i = 0;

	if (fmt->precision < 0 && !check_flags(fmt, MINUS) && check_flags(fmt, ZERO) )
	{
		if (!i && fmt->width > fmt->n)
			i = (fmt->width - fmt->n);
		else if (i)
		{ 
			while (i-- > 0)
				ft_putchar_fd_count('0', FD, &fmt->count);
			i = 0;
		}
	}
}

void handle_precis(t_format *fmt, int res)
{
	static int i = 0;

	if (fmt->precision >= 0 )
	{ 
		if (!i && (fmt->precision > fmt->n || !res))
		{
			i = fmt->precision - fmt->n;
			fmt->n = fmt->precision;
			if (fmt->isneg)
				fmt->n++;
		}
		else
		{ 
			while (i-- > 0)
				ft_putchar_fd_count('0', FD, &fmt->count);
			i = 0;
		}
	}
}

void handle_hash(t_format *fmt, unsigned long long res)
{
	static int i = 0;

	if (ft_strchr("p", fmt->spec) || (ft_strchr("xX", fmt->spec) && check_flags(fmt, HASH)))
	{ 
		if (!i && res)
		{
			i = 2;
			fmt->n += i;
		}
		else if (i == 2)
		{
			if (ft_islower(fmt->spec))
				ft_putstr_fd_count("0x", FD, &fmt->count);
			else
				ft_putstr_fd_count("0X", FD, &fmt->count);
			i = 0;
		}
	}
}


void handle_space(t_format *fmt)
{
	if (check_flags(fmt, SPACE) && !check_flags(fmt, PLUS) && !fmt->isneg)
		fmt->n += print_space(1, &fmt->count);
}

void handle_sym(t_format *fmt)
{
	if (!fmt->isneg)
	{	
		if (check_flags(fmt, PLUS) && ft_strchr("id", fmt->spec))
			ft_putchar_fd_count('+', FD, &fmt->count);
	}
	else
	{
		if ((check_flags(fmt, ZERO)  || fmt->precision > 0 ) && ft_strchr("id", fmt->spec))
			ft_putchar_fd_count('-', FD, &fmt->count);
	}
}

void handle_width(t_format *fmt)
{
	if (fmt->width && !check_flags(fmt, MINUS) && !check_flags(fmt, ZERO))
		print_space(fmt->width - fmt->n - fmt->isneg, &fmt->count);
}

int	ft_render_nums(t_format *fmt)
{
	char	base_s[17];
	unsigned long long res;

	if (ft_strchr("id", fmt->spec))
		res = va_arg(fmt->ap, int);
	else if (ft_strchr("uxX", fmt->spec))
		res = va_arg(fmt->ap, unsigned int);
	if (fmt->spec == 'p')
	{
		res = (unsigned long long)va_arg(fmt->ap, void *);
		if (!res)
			return (ft_putstr_n_fd("(nil)", 5, FD, &fmt->count));
	}
	if (ft_strchr("id", fmt->spec) && (int)res < 0)
		fmt->isneg = 1;
	get_base(fmt, base_s);
	fmt->n = ft_count_digits_base(res, ft_strlen(base_s), fmt);
	handle_space(fmt);
	handle_hash(fmt, res);
	handle_zero(fmt);
	handle_precis(fmt, res);
	handle_width(fmt);
	handle_sym(fmt);
	handle_hash(fmt, res);
	handle_zero(fmt);
	handle_precis(fmt, (int)res);
	if (fmt->spec == 'p')
		ft_iputnum_ptr(res, fmt);
	else if (fmt->n)
		ft_putnbr_base_fmt(res, base_s, &fmt->count, check_flags(fmt, ZERO) || fmt->precision > 0 || fmt->spec == 'u');
	if (fmt->width && check_flags(fmt, MINUS))
		print_space(fmt->width - fmt->n - fmt->isneg, &fmt->count);
	return (1);
}

int	ft_render(t_format *fmt)
{
	//	int	n;
	if (fmt->spec == '%')
		ft_putchar_fd_count('%', FD, &fmt->count);
	if (ft_strchr("cs", fmt->spec))
		ft_render_chars(fmt);
	else if (ft_strchr("pdiuxX", fmt->spec))
		ft_render_nums(fmt);	
	//n = fmt.

	return (0);
}
