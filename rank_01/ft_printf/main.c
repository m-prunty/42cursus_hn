/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maprunty <maprunty@student.42heilbronn.de  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/12 17:04:10 by maprunty          #+#    #+#             */
/*   Updated: 2025/11/02 03:54:53 by maprunty         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/ft_printf.h"

#include <stdio.h>
#include <limits.h>
#include <stdint.h>

void test_edge_cases(void) {
    int si = -12345;
    int pi = 12345;
    unsigned int ui = 4294967295u;
    long long lli = LLONG_MIN;
    unsigned long long ull = ULLONG_MAX;
    void *ptr = (void*)0x1234abcd;

	puts("===== printf =====");
    puts("===== BASIC SIGNED INT (%d / %i) =====");
    printf("%%d basic          : [%d]\n", pi);
    printf("%%i negative       : [%i]\n", si);
    printf("%%+d sign always   : [%+d]\n", pi);
    printf("%% d space sign    : [% d]\n", pi);
    printf("%%+ d plus beats sp: [%+ d]\n", pi);
    printf("%%06d zero pad     : [%06d]\n", pi);
    printf("%%-6d left justify : [%-6d]\n", pi);
    printf("%%6.4d width+prec  : [%6.4d]\n", pi);
    printf("%%.0d prec=0 val=0 : [%.0d]\n", 0);

    puts("\n===== LENGTH MODIFIERS =====");
    printf("%%hd  short        : [%hd]\n", (short)-32768);
    printf("%%hhd signed char  : [%hhd]\n", (signed char)-128);
    printf("%%ld  long         : [%ld]\n", (long)-1234567890);
    printf("%%lld long long    : [%lld]\n", lli);
    printf("%%jd  intmax_t     : [%jd]\n", (intmax_t)LLONG_MAX);
    printf("%%zd  size_t->signed: [%zd]\n", (ssize_t)-1);

    puts("\n===== UNSIGNED DECIMAL (%u) =====");
    printf("%%u basic          : [%u]\n", ui);
    printf("%%#u alt form      : [%#u]\n", ui);   // # ignorend
    printf("%%012u zero pad     : [%012u]\n", ui);
    printf("%%-10.8u left/prec : [%-10.8u]\n", ui);

    puts("\n===== HEX LOWER (%x) =====");
    printf("%%x basic          : [%x]\n", ui);
    printf("%%#x alternate     : [%#x]\n", ui);
    printf("%%08x zero padded  : [%08x]\n", 42);
    printf("%%-10.8x left/prec : [%-10.8x]\n", ui);

    puts("\n===== HEX UPPER (%X) =====");
    printf("%%X basic          : [%X]\n", ui);
    printf("%%#X alternate     : [%#X]\n", ui);
    printf("%%08X zero padded  : [%08X]\n", 42);
    printf("%%-10.8X left/prec : [%-10.8X]\n", ui);

    puts("\n===== POINTER (%p) =====");
    printf("%%p basic          : [%p]\n", ptr);
    printf("%%20p width        : [%20p]\n", ptr);
    printf("%%020p zero padded : [%020p]\n", ptr);

    puts("\n===== EXTREME WIDTH/PRECISION =====");
    printf("INT_MAX width     : [%*d]\n", INT_MAX > 20 ? 20 : INT_MAX, 42);
    printf("INT_MAX precision : [%.*d]\n", INT_MAX > 20 ? 20 : INT_MAX, 42);
    

	puts("===== ft_printf =====");
	puts("===== BASIC SIGNED INT (%d / %i) =====");
    ft_printf("%%d basic          : [%d]\n", pi);
    ft_printf("%%i negative       : [%i]\n", si);
    ft_printf("%%+d sign always   : [%+d]\n", pi);
    ft_printf("%% d space sign    : [% d]\n", pi);
    ft_printf("%%+ d plus beats sp: [%+ d]\n", pi);
    ft_printf("%%06d zero pad     : [%06d]\n", pi);
    ft_printf("%%-6d left justify : [%-6d]\n", pi);
    ft_printf("%%6.4d width+prec  : [%6.4d]\n", pi);
    ft_printf("%%.0d prec=0 val=0 : [%.0d]\n", 0);

    puts("\n===== LENGTH MODIFIERS =====");
    ft_printf("%%hd  short        : [%hd]\n", (short)-32768);
    ft_printf("%%hhd signed char  : [%hhd]\n", (signed char)-128);
    ft_printf("%%ld  long         : [%ld]\n", (long)-1234567890);
    ft_printf("%%lld long long    : [%lld]\n", lli);
    ft_printf("%%jd  intmax_t     : [%jd]\n", (intmax_t)LLONG_MAX);
    ft_printf("%%zd  size_t->signed: [%zd]\n", (ssize_t)-1);

    puts("\n===== UNSIGNED DECIMAL (%u) =====");
    ft_printf("%%u basic          : [%u]\n", ui);
    ft_printf("%%#u alt form      : [%#u]\n", ui);   // # ignored
    ft_printf("%%012u zero pad     : [%012u]\n", ui);
    ft_printf("%%-10.8u left/prec : [%-10.8u]\n", ui);

    puts("\n===== HEX LOWER (%x) =====");
    ft_printf("%%x basic          : [%x]\n", ui);
    ft_printf("%%#x alternate     : [%#x]\n", ui);
    ft_printf("%%08x zero padded  : [%08x]\n", 42);
    ft_printf("%%-10.8x left/prec : [%-10.8x]\n", ui);

    puts("\n===== HEX UPPER (%X) =====");
    ft_printf("%%X basic          : [%X]\n", ui);
    ft_printf("%%#X alternate     : [%#X]\n", ui);
    ft_printf("%%08X zero padded  : [%08X]\n", 42);
    ft_printf("%%-10.8X left/prec : [%-10.8X]\n", ui);

    puts("\n===== POINTER (%p) =====");
    ft_printf("%%p basic          : [%p]\n", ptr);
    ft_printf("%%20p width        : [%20p]\n", ptr);
    ft_printf("%%020p zero padded : [%020p]\n", ptr);

    puts("\n===== EXTREME WIDTH/PRECISION =====");
    ft_printf("INT_MAX width     : [%*d]\n", INT_MAX > 20 ? 20 : INT_MAX, 42);
    ft_printf("INT_MAX precision : [%.*d]\n", INT_MAX > 20 ? 20 : INT_MAX, 42);
}



int main()
{
	char	*str = "This is my test";
	int		i = 42;
	char *beg = "one", *mid = "two", *end = "three";
	
//	ft_printf("Here char; |%#0c|\nstr; |%10.4s|\nint; |%i|\nnospec; |%#.*X|\n", 'a',  str, i, 15,15);
//	ft_printf("Here char; |%x|\nstr; |%5X|\nint; |%p|\nnospec; |%#034|\n", 42, -42,"two" );
//	printf("Here char; |%x|\nstr; |%5X|\nint; |%p|\nnospec; |%#034|\n", 42, -42,"two" );
    //test_edge_cases();
	//printf("%i",ft_printf(" %c ", '0'));   
	ft_printf("%i:\n", ft_printf("|%c", '0'));
	ft_printf("%i:\n", ft_printf("| %c", '0' - 256));
	ft_printf("%i:\n", ft_printf("| %c %c %c ", '0', 0, '1'));
	ft_printf("%i:\n", ft_printf("| %c %c %c ", '2', '1', 0));
	ft_printf("%i:\n", ft_printf("| %c %c %c ", 0, '1', '2'));
	
}
