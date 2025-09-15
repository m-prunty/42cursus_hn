/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maprunty <maprunty@student.42heilbronn.de  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/10 05:42:04 by maprunty          #+#    #+#             */
/*   Updated: 2025/09/15 07:39:28 by maprunty         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*

		##https://www.geeksforgeeks.org/c/printf-in-c/


1. Specifier
It is the character that denotes the type of data. Some commonly used specifiers are:

%d: for printing integers
%f: for printing floating-point numbers
%c: for printing characters
%s: for printing strings
%%: Prints '%' literal
2. Width
It is the sub-specifier that denotes the minimum number of characters that will be printed.

If the number of characters is less than the specified width, the white space will be used to fill the remaining characters' places.
But if the number of characters is greater than the specified width, all the characters will be still printed without cutting off any.
3. Precision
Precision sub specifier meaning differs for different data types it is being used with.

For Integral data(d, i, u, o, x, X): Specifies the minimum number of digits to be printed. But unlike the width sub-specifier, instead of white spaces, this sub-specifier adds leading zeroes to the number. If the number has more digits than the precision, the number is printed as it is.
For Float or Double Data(f, e, a, A): Specifies the number of digits to be printed after the decimal point.
For String (s): Specifies the length of the string to be printed.
4. Length
Specifies the length of the data type in the memory. It is used in correspondence with data type modifiers.

There are 3 length sub-specifiers:

h: With short int and unsigned short int
l: With long int and unsigned long int.
L: With long double

 */

/*
    	##	man 3  printf

	Flag characters
       The character % is followed by zero or more of the following flags:

       #      The value should be converted to an "alternate form".  For o conversions, the
              first character of the output string is made zero (by prefixing a 0 if it was
              not zero already).  For x and X conversions, a nonzero result has the  string
              "0x"  (or  "0X" for X conversions) prepended to it.  For a, A, e, E, f, F, g,
              and G conversions, the result will always contain a decimal point, even if no
              digits follow it (normally, a decimal point appears in the results  of  those
              conversions  only if a digit follows).  For g and G conversions, trailing ze‐
              ros are not removed from the result as they would otherwise be.   For  m,  if
              errno  contains  a  valid error code, the output of strerrorname_np(errno) is
              printed; otherwise, the value stored in errno is printed as a decimal number.
              For other conversions, the result is undefined.

       0      The value should be zero padded.  For d, i, o, u, x, X, a, A, e, E, f, F,  g,
              and  G  conversions,  the  converted  value  is padded on the left with zeros
              rather than blanks.  If the 0 and - flags both appear, the 0 flag is ignored.
              If a precision is given with an integer conversion (d, i, o, u,  x,  and  X),
              the 0 flag is ignored.  For other conversions, the behavior is undefined.

       -      The  converted  value is to be left adjusted on the field boundary.  (The de‐
              fault is right justification.)  The converted value is padded  on  the  right
              with blanks, rather than on the left with blanks or zeros.  A - overrides a 0
              if both are given.

       ' '    (a  space)  A blank should be left before a positive number (or empty string)
              produced by a signed conversion.

       +      A sign (+ or -) should always be placed before a number produced by a  signed
              conversion.  By default, a sign is used only for negative numbers.  A + over‐
              rides a space if both are used.

       The  five  flag  characters  above are defined in the C99 standard.   The Single UNIX
       Specification specifies one further flag character.

       '      For decimal conversion (i, d, u, f, F, g, G) the output is to be grouped with
              thousands' grouping characters if the locale information indicates any.  (See
              setlocale(3).)  Note that many versions of gcc(1) cannot  parse  this  option
              and  will  issue a warning.  (SUSv2 did not include %'F, but SUSv3 added it.)
              Note also that the default locale of a C program is "C" whose locale informa‐
              tion indicates no thousands' grouping character.  Therefore, without a  prior
              call to setlocale(3), no thousands' grouping characters will be printed.

       glibc 2.2 adds one further flag character.

       I      For  decimal integer conversion (i, d, u) the output uses the locale's alter‐
              native output digits, if any.  For example, since glibc 2.2.3 this will  give
              Arabic-Indic digits in the Persian ("fa_IR") locale.

   Field width
       An  optional  decimal  digit  string (with nonzero first digit) specifying a minimum
       field width.  If the converted value has fewer characters than the field  width,  it
       will  be  padded  with spaces on the left (or right, if the left-adjustment flag has
       been given).  Instead of a decimal digit string one may write "*" or "*m$" (for some
       decimal integer m) to specify that the field width is given in the next argument, or
       in the m-th argument, respectively, which must be of type  int.   A  negative  field
       width  is taken as a '-' flag followed by a positive field width.  In no case does a
       nonexistent or small field width cause truncation of a field; if  the  result  of  a
       conversion  is wider than the field width, the field is expanded to contain the con‐
       version result.

   Precision
       An optional precision, in the form of a period ('.')  followed by an optional  deci‐
       mal digit string.  Instead of a decimal digit string one may write "*" or "*m$" (for
       some decimal integer m) to specify that the precision is given in the next argument,
       or  in the m-th argument, respectively, which must be of type int.  If the precision
       is given as just '.', the precision is taken to be zero.  A  negative  precision  is
       taken  as if the precision were omitted.  This gives the minimum number of digits to
       appear for d, i, o, u, x, and X conversions, the number of digits  to  appear  after
       the radix character for a, A, e, E, f, and F conversions, the maximum number of sig‐
       nificant  digits  for g and G conversions, or the maximum number of characters to be
       printed from a string for s and S conversions.


 */
/*
	## ft_printf subject

• %c Prints a single character.
• %s Prints a string (as defined by the common C convention).
• %p The void * pointer argument has to be printed in hexadecimal format.
• %d Prints a decimal (base 10) number.
• %i Prints an integer in base 10.
• %u Prints an unsigned decimal (base 10) number.
• %x Prints a number in hexadecimal (base 16) lowercase format.
• %X Prints a number in hexadecimal (base 16) uppercase format.
• %% Prints a percent sign.

 */
/* 
		##	man va_arg

 DESCRIPTION
       A  function  may be called with a varying number of arguments of varying types.  The
       include file <stdarg.h> declares a type va_list and defines three macros  for  step‐
       ping  through a list of arguments whose number and types are not known to the called
       function.

       The called function must declare an object of type va_list  which  is  used  by  the
       macros va_start(), va_arg(), and va_end().

   va_start()
       The va_start() macro initializes ap for subsequent use by va_arg() and va_end(), and
       must be called first.

       The  argument  last  is  the  name of the last argument before the variable argument
       list, that is, the last argument of which the calling function knows the type.

       Because the address of this argument may be used in the va_start() macro, it  should
       not be declared as a register variable, or as a function or an array type.

   va_arg()
       The  va_arg() macro expands to an expression that has the type and value of the next
       argument in the call.  The argument ap is the va_list ap initialized by  va_start().
       Each  call  to va_arg() modifies ap so that the next call returns the next argument.
       The argument type is a type name specified so that the type of a pointer to  an  ob‐
       ject that has the specified type can be obtained simply by adding a * to type.

       The  first  use of the va_arg() macro after that of the va_start() macro returns the
       argument after last.  Successive invocations return the values of the remaining  ar‐
       guments.

       If  there is no next argument, or if type is not compatible with the type of the ac‐
       tual next argument (as promoted according to the default argument promotions),  ran‐
       dom errors will occur.

       If ap is passed to a function that uses va_arg(ap,type), then the value of ap is un‐
       defined after the return of that function.

   va_end()
       Each  invocation  of  va_start()  must  be  matched by a corresponding invocation of
       va_end() in the same function.  After the call va_end(ap) the variable ap  is  unde‐
       fined.   Multiple  traversals of the list, each bracketed by va_start() and va_end()
       are possible.  va_end() may be a macro or a function.

 */


//%[flags][width][.precision][length]specifier
#ifndef FT_PRINTF_H 
# define FT_PRINTF_H 

#include <unistd.h>
#include <stdarg.h>
#include <stddef.h>
#include "libft.h"

#  define SPECIFIER "cspdiuxX%"
#  define	FLAGS "-0# +"
#  define LENMOD	"hlqLjzZt"
#  define BASE	"0123456789abcdef"

#  ifndef FD
#   define FD 1 
#  endif

typedef enum	e_flag
{
	NONE = 0,
	MINUS = 45,
	ZERO = 48,
	HASH = 35,
	SPACE = 32,
	PLUS = 43,
}	e_flag;

typedef struct	s_format
{
	const char	*str;
	size_t	n;
	va_list	ap;
	//flag
	e_flag	flags[5];
	//width
	int		width;
	//precision
	int		precision;
	//len
	int		lenmod;
	//spec
	char	spec;
	//bytecount
	int		count;

}	t_format ;


char	*ft_strchrstr(const char *s, const char *chrs);
void	ft_parse_len(t_format *fmt);

void	ft_parse_flags(t_format *fmt);
void	ft_parse_width(t_format *fmt);
void	ft_parse_precis(t_format *fmt);
void	ft_parse_spec(t_format *fmt);
int		ft_parse(t_format *fmt);

int		ft_render(t_format *fmt);

void	ft_init_format(t_format *fmt, const char* f_str );
int		ft_printf(const char *f_str, ...);

int	ft_atoi_base(char *str, char *base);
int	ft_isvalid_base(char *base);
int	ft_convert_charbase(char c, int *val, char *base);
void	ft_putnbr_base(int nbr, char *base);

void	ft_putnbr_base_fd(long int n, int fd, char *base);

#endif // !
