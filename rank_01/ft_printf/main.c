/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maprunty <maprunty@student.42heilbronn.de  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/12 17:04:10 by maprunty          #+#    #+#             */
/*   Updated: 2025/11/17 14:33:06 by maprunty         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/ft_printf.h"

#include <stdio.h>
#include <limits.h>
#include <stdint.h>

void	test_print_noarg(char *format)
{
   	printf("\nog_printf>> ");	
	fflush(stdout);	
    printf(format);

   	printf("\nmy_printf>> ");	
	fflush(stdout);	
    ft_printf(format);
}

void	test_print_chars(char *format, int a, int b, int c)
{
   	printf("\nog_printf>> ");	
	fflush(stdout);	
    printf(format, a, b, c);

   	printf("\nmy_printf>> ");	
	fflush(stdout);	
    ft_printf(format, a, b, c);
}

void	test_print_ptrs(char *format, int a, int b)
{
	int i, j = 0;

   	printf("\nog_printf>>|");	
	fflush(stdout);	
    i = printf(format, a, b);
   	printf("|\tnchars>>: %i", i);	

   	printf("\nmy_printf>>|");	
	fflush(stdout);	
    j = ft_printf(format, a, b);
   	printf("|\tnchars>>: %i", j);	
}

void	test_print_pcent(char *format )
{
	int i, j = 0;

   	printf("\nog_printf>>|");	
	fflush(stdout);	
    i = printf(format);
   	printf("|\tnchars>>: %i", i);	

   	printf("\nmy_printf>>|");	
	fflush(stdout);	
    j = ft_printf(format);
   	printf("|\tnchars>>: %i", j);	
}

void	test_print_int(char *format, int a )
{
	int i, j = 0;

   	printf("\nformat >>|%s| int>>|%i|", format, a );	
   	printf("\nog_printf>>\t|");	
	fflush(stdout);	
    i = printf(format, a);
   	printf("|\tnchars>>: %i", i);	

   	printf("\nmy_printf>>\t|");	
	fflush(stdout);	
    j = ft_printf(format, a);
   	printf("|\tnchars>>: %i", j);	
}

void	test_print_ints(char *format, int a , int b)
{
	int i, j = 0;

   	printf("\nformat >>|%s| int>>|%i| int>>|%i| ", format, a, b);	
   	printf("\nog_printf>>\t|");	
	fflush(stdout);	
    i = printf(format, a, b);
   	printf("|\tnchars>>: %i", i);	

   	printf("\nmy_printf>>\t|");	
	fflush(stdout);	
    j = ft_printf(format, a, b);
   	printf("|\tnchars>>: %i", j);	
}

void	test_print_int_eight(char *format, int a , int b, int c, int d, int e, int f, int g, int h)
{
	int i, j = 0;

   	printf("\nformat >>|%s| int>>|%i| int>>|%i| int>>|%i| int>>|%i| int>>|%i| int>>|%i| int>>|%i| int>>|%i|",
		 format, a, b, c, d, e, f, g, h);	
   	printf("\nog_printf>>\t|");	
	fflush(stdout);	
    i = printf(format, a, b, c, d, e, f, g, h);
   	printf("|\tnchars>>: %i", i);	

   	printf("\nmy_printf>>\t|");	
	fflush(stdout);	
	j = ft_printf(format, a, b, c, d, e, f, g, h);
   	printf("|\tnchars>>: %i", j);	
}

void	test_print_int_ten(char *format, int a , int b, int c, int d, int e, int f, int g, int h, int k, int l)
{
	int i, j = 0;

   	printf("\nformat >>|%s| int>>|%i| int>>|%i| int>>|%i| int>>|%i| int>>|%i| int>>|%i| int>>|%i| int>>|%i|",
		 format, a, b, c, d, e, f, g, h, k, l);	
   	printf("\nog_printf>>\t|");	
	fflush(stdout);	
    i = printf(format, a, b, c, d, e, f, g, h ,k, l);
   	printf("|\tnchars>>: %i", i);	

   	printf("\nmy_printf>>\t|");	
	fflush(stdout);	
	j = ft_printf(format, a, b, c, d, e, f, g, h, k, l);
   	printf("|\tnchars>>: %i", j);	
}

void	test_print_str(char *format, char *a)
{
	int i, j = 0;

   	printf("\nog_printf>>|");	
	fflush(stdout);	
    i = printf(format, a);
   	printf("|\tnchars>>: %i", i);	

   	printf("\nmy_printf>>|");	
	fflush(stdout);	
    j = ft_printf(format, a);
   	printf("|\tnchars>>: %i", j);	
}

void	test_print_strs(char *format, char *a, char *b)
{
	int i, j = 0;

   	printf("\nog_printf>>|");	
	fflush(stdout);	
    i = printf(format, a, b);
   	printf("|\tnchars>>: %i", i);	

   	printf("\nmy_printf>>|");	
	fflush(stdout);	
    j = ft_printf(format, a, b);
   	printf("|\tnchars>>: %i", j);	
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
	
/*
	ft_printf("%i:", ft_printf("|%c %c", '0', 65));
	printf("\n");
	ft_printf("%i:", ft_printf("| %c ", '0' - 256));
	printf("\n");
	ft_printf("%i:", ft_printf("| %c %c %c ", '0', 65, '1'));
	printf("\n");
	ft_printf("%i:", ft_printf("| %c %c %c ", '2', '1', 0));
	printf("\n");
	ft_printf("%i:", ft_printf("| %c %c %c ", 0, '1', '2'));
	printf("\n");
	ft_printf("%i",ft_printf(" NULL %s NULL ", NULL));

	printf("\n\n");
	printf("%i:", printf("|%c %c", '0', 65));
	printf("\n");
	printf("%i:", printf("| %c ", '0' - 256));
	printf("\n");
	printf("%i:", printf("| %c %c %c ", '0', 65, '1'));
	printf("\n");
	printf("%i:", printf("| %c %c %c ", '2', '1', 0));
	printf("\n");
	printf("%i:", printf("| %c %c %c ", 0, '1', '2'));
	printf("\n");
	printf("%i",printf(" NULL %s NULL ", NULL));
*/
/*
	test_print_ptrs(" %p ", -1, 0);
	test_print_ptrs(" %p %p ", (void *)LONG_MIN, (void *)LONG_MAX);
	test_print_ptrs(" %p %p ", (void *)ULONG_MAX, (void *)-ULONG_MAX);
	test_print_ptrs(" %2p ", -1, 0);
	test_print_pcent(" %%%% ");
	test_print_int(" %-1d ", 0);
	test_print_int(" %-4d ", -14);
	test_print_int(" %-5d ", 15);
	test_print_int(" %-6d ", -16);
	test_print_int(" %-11d ", LONG_MAX);
	test_print_int(" %-12d ", LONG_MIN);
	test_print_int(" %-13d ", UINT_MAX);
	test_print_int(" %-14d ", ULONG_MAX);
	test_print_int(" %-15d ", 9223372036854775807LL);
	test_print_chars("| %c %c %c |", 65, '1', '2');
	test_print_strs("%7.7s%7.7s", "hello", "world");
	test_print_strs("%3.7s%7.7s", "hello", "world");
	test_print_strs("%7.7s%3.7s", "hello", "world");
		

	test_print_int(" %04d ", -14);                                                                 
	test_print_int(" %05d ", -15);                                                                 
	test_print_int(" %06d ", -16);                                                                 
	test_print_int(" %011d ", LONG_MAX);                                                           
	test_print_int(" %013d ", UINT_MAX);                                                           
	test_print_int(" %014d ", ULONG_MAX);                                                          
	test_print_int(" %015d ", 9223372036854775807LL);    

	
	test_print_int(" %-10d ", INT_MIN);      
	test_print_int(" %-11i ", LONG_MAX);                                                           
	test_print_int(" %-1u ", 0);  
	
	test_print_int(" %02d ", -1);                                                                   
	test_print_int(" %01d ", -9);                                                                  
	test_print_int(" %02d ", -10);                                                                 
	test_print_int(" %03d ", -11);                                                                 
	test_print_int(" %01d ", -99);                                                                 
	test_print_int(" %02d ", -100);                                                                
	test_print_int(" %03d ", -101);          	
	test_print_ptrs(" %-9p %-10p ", LONG_MIN, LONG_MAX);
	test_print_int(" %010d ", INT_MIN);      
	test_print_int(" %011i ", LONG_MAX);                                                           
	test_print_int(" %01u ", 0);  
	test_print_int(" %.2u ", -1);                                                                                                                                                       
	test_print_int(" %.2u ", 1);                                                                                                                                                        
	test_print_int(" %.3u ", 11);
	test_print_int(" %.3u ", -99);                                                                                                                                                      
	test_print_int(" %.4u ", -101);                                                                                                                                                     
	test_print_int(" %.10u ", LONG_MAX);                                                                                                                                                
	test_print_int(" %.12u ", UINT_MAX); 
	test_print_int(" %#x ", 0);                                                                                                                                                          
	test_print_int(" %#x ", LONG_MIN);                                                                                                                                                  

	test_print_int(" %#X ", 0);                                                                                                                                                         
	test_print_int(" %#X ", LONG_MIN);


	test_print_int(" % d ", 0);
	test_print_int(" % d ", 1);
	test_print_int(" % d ", 9);
	test_print_int(" % d ", 10);
	test_print_int(" % d ", 11);
	test_print_int(" % d ", 15);
	test_print_int(" % d ", 16);
	test_print_int(" % d ", 17);
	test_print_int(" % d ", 99);
	test_print_int(" % d ", 100);
	test_print_int(" % d ", 101);
	test_print_int(" % d ", INT_MAX);
	test_print_int(" % d ", LONG_MIN);
	test_print_int(" % d ", -1);                                                                                                                                                        
	test_print_int(" % d ", -9);                                                                                                                                                        
	test_print_int(" % d ", -10);                                                                                                                                                       
	test_print_int(" % d ", -11);                                                                                                                                                       
	test_print_int(" % d ", -14);                                                                                                                                                       
	test_print_int(" % d ", -15);                                                                                                                                                       
	test_print_int(" % d ", -16);                                                                                                                                                       
	test_print_int(" % d ", -99);                                                                                                                                                       
	test_print_int(" % d ", -100);                                                                                                                                                      
	test_print_int(" % d ", -101);                                                                                                                                                      
	test_print_int(" % d ", INT_MIN);                                                                                                                                                   
	test_print_int(" % d ", LONG_MAX);                                                                                                                                                  
	test_print_int(" % d ", UINT_MAX);  
	
	test_print_int(" %+d ", 0);
	test_print_int(" %+d ", -1);
	test_print_int(" %+d ", -9);
	test_print_int(" %+d ", -10);
	test_print_int(" %+d ", -11);
	test_print_int(" %+d ", -14);
	test_print_int(" %+d ", -15);
	test_print_int(" %+d ", -16);
	test_print_int(" %+d ", -99);
	test_print_int(" %+d ", -100);
	test_print_int(" %+d ", -101);

	test_print_int("%.03s", NULL);
	test_print_int("%3.1s", NULL);
	test_print_int("%9.1s", NULL);
	test_print_int("%-3.1s", NULL);
	test_print_int("%-9.1s", NULL);
	test_print_int("%8.5i", 34);

*/

/*
	test_print_str("%23s", NULL);
	test_print_str("%32s", "abc");
	test_print_str("%16s", "nark nark");
	test_print_str("%-32s", "abc");
	test_print_str("%-16s", "nark nark");
	test_print_strs("%.5s%7s", "yo", "boi");
	test_print_str("%7.5s", "yolo");
	test_print_str("%7.5s", "bombastic");
	test_print_str("%-7.5s", "yolo");
	test_print_str("%-7.5s", "tubular");
	test_print_strs("%7.7s%7.7s", "hello", "world");
	test_print_strs("%3.7s%7.7s", "hello", "world");
	test_print_strs("%7.7s%3.7s", "hello", "world");
	test_print_strs("%7.3s%7.7s", "hello", "world");
	test_print_strs("%3.3s%7.7s", "hello", "world");
	test_print_strs("%7.3s%3.7s", "hello", "world");
	test_print_strs("%7.7s%7.3s", "hello", "world");
	test_print_strs("%3.7s%7.3s", "hello", "world");
	test_print_strs("%7.7s%3.3s", "hello", "world");
	test_print_strs("%7.3s%7.3s", "hello", "world");
	
	test_print_int("%10.5i", -216);
	test_print_int("%8.5i", 0);
	test_print_int("%8.3i", -8473);
	test_print_int("%-8.5i", 34);
	test_print_int("%-10.5i", -216);
	test_print_int("%-8.5i", 0);
	test_print_int("%-8.3i", -8473);
	test_print_int("%08.5i", 34);
	test_print_int("%010.5i", -216);
	test_print_int("%08.5i", 0);
	test_print_int("%08.3i", 8375);
	test_print_int("%08.3i", -8473);

	test_print_int("%.09s", NULL);
	test_print_int("%3.6s", NULL);
	test_print_int("%20.6s", NULL);
	test_print_int("%-3.8s", NULL);
	test_print_int("%-10.8s", NULL);
	test_print_int("%8.5i", 34);
	test_print_int("%10.5i", -216);
	test_print_int("%8.5i", 0);
	test_print_int("%8.3i", -8473);
	test_print_int("%-8.5i", 34);
	test_print_int("%-10.5i", -216);
	test_print_int("%-8.5i", 0);
	test_print_int("%-8.3i", -8473);
	test_print_int("%08.5i", 34);
	test_print_int("%010.5i", -216);
	test_print_int("%08.5i", 0);
	test_print_int("%08.3i", 8375);
	test_print_int("%08.3i", -8473);
	test_print_int("%.0i", 0);
	test_print_int("%.i", 0);
	
	test_print_int("%8.3i", -8473);
	test_print_int("%-8.3i", -8473);
	test_print_int("%08.5i", 34);
	test_print_int("%010.5i", -216);
	test_print_int("%08.5i", 0);
	test_print_int("%08.3i", 8375);
	test_print_int("%08.3i", -8473);
	test_print_int("%.0i", 0);
	test_print_int("%.i", 0);
	test_print_int("%5.0i", 0);
	test_print_int("%5.i", 0);
	test_print_int("%-5.0i", 0);
	test_print_int("%-5.i", 0);
	test_print_int("%8.3d", -8473);
	test_print_int("%-8.3d", -8473);
	test_print_int("%08.5d", 34);
	test_print_int("%010.5d", -216);
	test_print_int("%08.5d", 0);
	test_print_int("%08.3d", 8375);
	test_print_int("%08.3d", -8473);
	
	test_print_int("%7i", -14);
	test_print_int("%10.5i", -216);
	test_print_int("%-8.3i", -8473);
	test_print_int("%08.5i", 34);
	test_print_int("%010.5i", -216);
	test_print_int("%08.5i", 0);
	test_print_int("%08.3i", 8375);
	test_print_int("%08.3i", -8473);
	test_print_int("%7d", -14);
	test_print_int("%10.5d", -216);
	test_print_int("%-8.3d", -8473);
	test_print_int("%08.5d", 34);
	test_print_int("%010.5d", -216);
	test_print_int("%08.5d", 0);
	test_print_int("%08.3d", 8375);
	test_print_int("%08.3d", -8473);
	test_print_int("%08.5u", 34);
	test_print_int("%08.5u", 0);
	test_print_int("%08.3u", 8375);
	test_print_int("%08.5x", 34);
	
	test_print_int(" %04d ", 9);
	test_print_int(" %03d ", 15);
	test_print_int(" %04d ", 16);
	test_print_int(" %05d ", 17);
	test_print_int(" %04d ", -14);
	test_print_int(" %05d ", -15);
	test_print_int(" %06d ", -16);
	test_print_int(" %011d ", LONG_MAX);
	test_print_int(" %012d ", LONG_MIN);
	test_print_int(" %013d ", UINT_MAX);
	test_print_int(" %014d ", ULONG_MAX);
	test_print_int(" %015d ", 9223372036854775807LL);
	test_print_int(" %03i ", 1);
	test_print_int(" %04i ", 9);
	test_print_int(" %03i ", 15);
	test_print_int(" %04i ", 16);
	test_print_int(" %05i ", 17);
	test_print_int(" %05i ", -15);
	test_print_int(" %i ", LONG_MIN);
	test_print_int(" %d ", LONG_MIN);
	test_print_int("|%lld|", (long long)(-LONG_MIN));
	
	test_print_int("%.0i", 0);
	test_print_int("%.i", 0);
	test_print_int("%5.0i", 0);
	test_print_int("%5.i", 0);
	test_print_int("%-5.0i", 0);
	test_print_int("%-5.i", 0);
	test_print_int("%.0d", 0);
	test_print_int("%.d", 0);
	test_print_int("%5.0d", 0);
	test_print_int("%5.d", 0);
	test_print_int("%-5.0d", 0);
	test_print_int("%-5.d", 0);
	test_print_int("%.0u", 0);
	test_print_int("%.u", 0);
	test_print_int("%5.0u", 0);
	test_print_int("%5.u", 0);
	test_print_int("%-5.0u", 0);
	test_print_int("%-5.u", 0);
	test_print_int("%.0x", 0);
	test_print_int("%.x", 0);


	test_print_int(" %-2p ", 1);
	test_print_int(" %-2p ", 15);
	test_print_int(" %-3p ", 16);
	test_print_int(" %-4p ", 17);
	test_print_ints(" %-11p %-12p ", INT_MIN, INT_MAX);
	test_print_ints(" %-13p %-14p ", ULONG_MAX, -ULONG_MAX);
	test_print_int("%15p", NULL);
	test_print_int("%-15p", NULL);
	//test_print_ptrs(" %p ", -1);
	test_print_ptrs(" %p %p ", LONG_MIN, LONG_MAX);
	test_print_ptrs(" %p %p ", INT_MIN, INT_MAX);
	*/
	// test_print_int("% 5c", 0);
	/*
	test_print_ptrs(" %#11x %#12X ", NULL, NULL);
	test_print_ptrs(" %-13p %-14p ", NULL, NULL);
	test_print_ptrs(" %-11p %-12p ", INT_MIN, INT_MAX);
	test_print_ptrs(" %-13p %-14p ", ULONG_MAX, -ULONG_MAX);
	// printf("\n");
	printf("\n");
	printf("%0 5d, %0 5d, %0 5d, %0 5d, %0 5d, %0 5d, %0 5d, %0 5d", 0, 5, -1, -10, 100, -1862, INT_MIN, INT_MAX);
	// printf("%0+5d, %0+5d, %0+5d, %0+5d, %0+5d, %0+5d, %0+5d, %0+5d", 0, 5, -1, -10, 100, -1862, INT_MIN, INT_MAX);
	// printf("%+5.d, %+5.d, %+5.d, %+5.d, %+5.d, %+5.d, %+5.d, %+5.d", 0, 5, -1, -10, 100, -1862, INT_MIN, INT_MAX);
	printf("\n");
	// ft_printf("%0+5d, %0+5d, %0+5d, %0+5d, %0+5d, %0+5d, %0+5d, %0+5d", 0, 5, -1, -10, 100, -1862, INT_MIN, INT_MAX);
	// ft_printf("%+5.d, %+5.d, %+5.d, %+5.d, %+5.d, %+5.d, %+5.d, %+5.d", 0, 5, -1, -10, 100, -1862, INT_MIN, INT_MAX);
	ft_printf("%0 5d, %0 5d, %0 5d, %0 5d, %0 5d, %0 5d, %0 5d, %0 5d", 0, 5, -1, -10, 100, -1862, INT_MIN, INT_MAX);

	// test_print_int("%i   |%5%",0);
	// test_print_int("%i   |%-5%",0);
	// test_print_int("%i   |%-05%",0);
	test_print_int("%c", 0);
	test_print_int("%5.i", 0);
	test_print_int("%.0i", 0);
	test_print_int("%.i", 0);
	test_print_int("%5.1i", 0);
	test_print_int("%0+8.5i", 0);
	test_print_int("%02d", -1);
	test_print_int("%+.d", LONG_MIN);
	

	test_print_str("%.c", 'a');
	test_print_str("%.c", 'a');
	test_print_str("%1.c", 'a');
	test_print_str("%5.c", 'a');
	test_print_strs("NULL |%.3s| |%1s| NULL", NULL, NULL);

	test_print_int_eight("%0 5d, %0 5d, %0 5d, %0 5d, %0 5d, %0 5d, %0 5d, %0 5d", 0, 5, -1, -10, 100, -1862, INT_MIN, INT_MAX);
	test_print_int_ten("%#5x, %#5x, %#5x, %#5x, %#5x, %#5x, %#5x, %#5x, %#5x, %#5x", 0, 5, -1, -10, 0x1234, -1862, 0xABCDE, INT_MIN, INT_MAX, UINT_MAX);
	
	test_print_int_ten("%#10.5x, %#10.5x, %#10.5x, %#10.5x, %#10.5x, %#10.5x, %#10.5x, %#10.5x, %#10.5x, %#10.5x", 0, 5, -1, -10, 0x1234, -1862, 0xABCDE, INT_MIN, INT_MAX, UINT_MAX);
  // test_print_noarg("%%%%%%%%%%%%%%%%");
  // test_print_noarg("%%c%%s%%p%%d%%i%%u%%x%%X%%");
	printf("%--4s %s %------------------9s of %s of %-5s", "for", "the", "goooood", "aaall", "us"); 
	printf("\n"); 
	fflush(stdout);	
	ft_printf("%--4s %s %------------------9s of %s of %-5s", "for", "the", "goooood", "aaall", "us"); 
	printf("\n"); 
	printf("%--4.1s %s %------------------9.3s of %s of %-5.7s", "for", "the", "goooood", "aaall", "us");
	printf("\n"); 
	fflush(stdout);	
	ft_printf("%--4.1s %s %------------------9.3s of %s of %-5.7s", "for", "the", "goooood", "aaall", "us");
	test_print_ptrs(" |%3p|  |%4p| ", NULL, NULL);
	test_print_ptrs(" |%-4p|  |%-10p| ", NULL, NULL);
	fflush(stdout);	
	ft_printf("\n |%.5s| ", (char *)NULL);
	printf("\n |%.5s| ", (char *)NULL);
	fflush(stdout);	
	*/
   //test_print_noarg("%c - %s - %p %d - %i - %u - %x %X %%", 'a', "test", (void *)0xdeadc0de, 20, -20, -1, -1, 200000000);
}
