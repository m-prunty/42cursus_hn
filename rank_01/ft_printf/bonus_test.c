#include <stdio.h>
#include <limits.h>
#include <stdint.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include "include/ft_printf.h"

#define CAPTURE(expr) \
({ \
	char	*result; \
	int	pipefd[2]; \
	int	saved; \
	int	n; \
	\
	pipe(pipefd); \
	saved = dup(STDOUT_FILENO);\
	dup2(pipefd[1], STDOUT_FILENO);\
	close(pipefd[1]); \
	\
	setvbuf(stdout, NULL, _IONBF, 0); \
	int	_f(void) {return expr;} \
	_f(); \
	\
	fflush(stdout); \
	dup2(saved, STDOUT_FILENO); \
	close(saved); \
	\
	result = malloc(4096); \
	n = read(pipefd[0], result, 4095); \
	result[n] = 0; \
	close(pipefd[0]); \
	result ; \
})

/*
   	printf("\nog_printf>> ");	
	fflush(stdout);	
    printf(format, a, b, c);

   	printf("\nmy_printf>> ");	
	fflush(stdout);	
    ft_printf(format, a, b, c);

*/
#define CLR_RMV	"\033[0m"
#define RED		"\033[1;31m"
#define GREEN	"\033[1;32m"
#define ERRLOG_FILE "error_log.txt"

int g_current_test_id = 0;

void log_error(const char *fmt, ...)
{
    FILE *f = fopen(ERRLOG_FILE, "a");
    if (!f)
        return;

    va_list args;
    va_start(args, fmt);

    vfprintf(f, fmt, args);
    fprintf(f, "\n---------------------------------------------\n");

    va_end(args);
    fclose(f);
}

void	test_print_chars(char *format, int a, int b, int c)
{
	static int i = 0;
	static int last_id = -1;
	char *out1 = CAPTURE(printf(format, a, b, c));
	char *out2 = CAPTURE(ft_printf(format, a, b, c));

	if (g_current_test_id != last_id)
	{
		i = 0;
		last_id = g_current_test_id;
		printf("\n\nTesting; %c\n" , g_current_test_id);
	}
	printf("\t%i:" , ++i);
	if (strcmp(out1, out2) == 0)
		printf("%sOK%s", GREEN, CLR_RMV);
	else
	{
		printf("%sKO%s", RED, CLR_RMV);
		log_error(
				"Type : %c\n"
				"Test %d FAILED\n"
				"Format: \"%s\"\n"
				"Args: \"%c\", \"%c\", \"%c\"\n"
				"printf:\t\t|%i	|%s|\n"
				"ft_printf:\t|%i	|%s|\n",
				g_current_test_id, i, format, a, b, c, strlen(out1), out1, strlen(out2), out2
				);
	}
	free(out1);
	free(out2);
}

void	test_print_strs_four(char *format, char *a, char *b, char *c, char *d)
{
	static int i = 0;
	char *out1 = CAPTURE(printf(format, a, b, c, d));
	char *out2 = CAPTURE(ft_printf(format, a, b, c, d));
	static int last_id = -1;

	if (g_current_test_id != last_id)
	{
		i = 0;             // reset counter
		last_id = g_current_test_id;
		printf("\n\nTesting; %c\n" , g_current_test_id);
	}
	printf("\t%i:" , ++i);
	if (strcmp(out1, out2) == 0)
		printf("%sOK%s", GREEN, CLR_RMV);
	else
	{
		printf("%sKO%s", RED, CLR_RMV);
		log_error(
				"Type : %c\n"
				"Test %d FAILED\n"
				"Format: \"%s\"\n"
				"Args: \"%s\", \"%s\", \"%s\", \"%s\"\n"
				"printf:\t\t|%i	|%s|\n"
				"ft_printf:\t|%i	|%s|\n",
				g_current_test_id, i, format, a, b, c, d, strlen(out1), out1, strlen(out2), out2
				);
	}
	free(out1);
	free(out2);
}

void	test_print_ptrs_six(char *format, void *a, void *b, void *c, void *d, void *e, void *f)
{
	static int i = 0;
	char *out1 = CAPTURE(printf(format, a, b, c, d, e, f));
	char *out2 = CAPTURE(ft_printf(format, a, b, c, d, e, f));
	static int last_id = -1;

	if (g_current_test_id != last_id)
	{
		i = 0;
		last_id = g_current_test_id;
		printf("\n\nTesting; %c\n" , g_current_test_id);
	}
	printf("\t%i:" , ++i);
	if (strcmp(out1, out2) == 0)
		printf("%sOK%s", GREEN, CLR_RMV);
	else
	{
		printf("%sKO%s", RED, CLR_RMV);
		log_error(
				"Type : %c\n"
				"Test %d FAILED\n"
				"Format: \"%s\"\n"
				"Args: \"%p\", \"%p\", \"%p\", \"%p\", \"%p\", \"%p\"\n"
				"printf:\t\t|%i	|%s|\n"
				"ft_printf:\t|%i	|%s|\n",
				g_current_test_id, i, format, a, b, c, d, e, f,strlen(out1), out1, strlen(out2), out2
				);
	}
	free(out1);
	free(out2);
}

void	test_print_int_eight(char *format, int a , int b, int c, int d, int e, int f, int g, int h)
{

	static int i = 0;
	char *out1 = CAPTURE(printf(format, a, b, c, d, e, f, g, h));
	char *out2 = CAPTURE(ft_printf(format, a, b, c, d, e, f, g, h));
	static int last_id = -1;

	if (g_current_test_id != last_id)
	{
		i = 0;             // reset counter
		last_id = g_current_test_id;
		printf("\n\nTesting; %c\n" , g_current_test_id);
	}
	printf("\t%i:" , ++i);
	if (strcmp(out1, out2) == 0)
		printf("%sOK%s", GREEN, CLR_RMV);
	else
	{
		printf("%sKO%s", RED, CLR_RMV);
		log_error(
				"Type : %c\n"
				"Test %d FAILED\n"
				"Format: \"%s\"\n"
				"Args: \"%i\", \"%i\", \"%i\", \"%i\", \"%i\", \"%i\", \"%i\", \"%i\"\n"
				"printf:\t\t|%i	|%s|\n"
				"ft_printf:\t|%i	|%s|\n",
				g_current_test_id, i, format, a, b, c, d, e, f, g, h, strlen(out1), out1, strlen(out2), out2
				);
	}
	free(out1);
	free(out2);
}

void	test_print_long_ten(char *format, unsigned long a , unsigned long b, unsigned long c, unsigned long d, unsigned long e, unsigned long f, unsigned long g, unsigned long h, unsigned long k, unsigned long l)
{
	static int i = 0;
	char *out1 = CAPTURE(printf(format, a, b, c, d, e, f, g, h, k, l));
	char *out2 = CAPTURE(ft_printf(format, a, b, c, d, e, f, g, h, k, l));
	static int last_id = -1;

	if (g_current_test_id != last_id)
	{
		i = 0;             // reset counter
		last_id = g_current_test_id;
		printf("\n\nTesting; %c\n" , g_current_test_id);
	}
	printf("\t%i:" , ++i);
	if (strcmp(out1, out2) == 0)
		printf("%sOK%s", GREEN, CLR_RMV);
	else
	{
		printf("%sKO%s", RED, CLR_RMV);
		log_error(
				"Type : %c\n"
				"Test %d FAILED\n"
				"Format: \"%s\"\n"
				"Args: \"%lli\", \"%lli\", \"%lli\", \"%lli\", \"%lli\", \"%lli\", \"%lli\", \"%lli\", \"%lli\", \"%lli\" \n"
				"printf:\t\t|%i	|%s|\n"
				"ft_printf:\t|%i	|%s|\n",
				g_current_test_id, i, format, a, b, c, d, e, f, g, h, k, l, strlen(out1), out1, strlen(out2), out2
				);
	}
	free(out1);
	free(out2);
}

void test_printf_noarg(char * format)
{
	return ;
};

void test_c() {
	g_current_test_id = 'c';
	/* 1 */ test_print_chars("%c, %c, %c", '5', 'x', ' ');
	/* 2 */ test_print_chars("%1c, %1c, %1c", '5', 'x', ' ');
	/* 3 */ test_print_chars("%5c, %5c, %5c", '5', 'x', ' ');
	/* 4 */ test_print_chars("%10c, %10c, %10c", '5', 'x', ' ');
	/* 5 */ test_print_chars("%100c, %100c, %100c", '5', 'x', ' ');
	/* 6 */ test_print_chars("%-c, %-c, %-c", '5', 'x', ' ');
	/* 7 */ test_print_chars("%-1c, %-1c, %-1c", '5', 'x', ' ');
	/* 8 */ test_print_chars("%-5c, %-5c, %-5c", '5', 'x', ' ');
	/* 9 */ test_print_chars("%-10c, %-10c, %-10c", '5', 'x', ' ');
	/* 10 */ test_print_chars("%-100c, %-100c, %-100c", '5', 'x', ' ');
}


void test_s() {
	g_current_test_id = 's';
	/* 1 */ test_print_strs_four("%s, %s, %s, %s", (char *)NULL, "", "test", "joihwhhgsdkhksdgsdg\t\v\n\r\f\a25252\b6");
	/* 2 */ test_print_strs_four("%1s, %1s, %1s, %1s", (char *)NULL, "", "test", "joihwhhgsdkhksdgsdg\t\v\n\r\f\a25252\b6");
	/* 3 */ test_print_strs_four("%5s, %5s, %5s, %5s", (char *)NULL, "", "test", "joihwhhgsdkhksdgsdg\t\v\n\r\f\a25252\b6");
	/* 4 */ test_print_strs_four("%10s, %10s, %10s, %10s", (char *)NULL, "", "test", "joihwhhgsdkhksdgsdg\t\v\n\r\f\a25252\b6");
	/* 5 */ test_print_strs_four("%100s, %100s, %100s, %100s", (char *)NULL, "", "test", "joihwhhgsdkhksdgsdg\t\v\n\r\f\a25252\b6");
	/* 6 */ test_print_strs_four("%.s, %.s, %.s, %.s", (char *)NULL, "", "test", "joihwhhgsdkhksdgsdg\t\v\n\r\f\a25252\b6");
	/* 7 */ test_print_strs_four("%.0s, %.0s, %.0s, %.0s", (char *)NULL, "", "test", "joihwhhgsdkhksdgsdg\t\v\n\r\f\a25252\b6");
	/* 8 */ test_print_strs_four("%.1s, %.1s, %.1s, %.1s", (char *)NULL, "", "test", "joihwhhgsdkhksdgsdg\t\v\n\r\f\a25252\b6");
	/* 9 */ test_print_strs_four("%.5s, %.5s, %.5s, %.5s", (char *)NULL, "", "test", "joihwhhgsdkhksdgsdg\t\v\n\r\f\a25252\b6");
	/* 10 */ test_print_strs_four("%.10s, %.10s, %.10s, %.10s", (char *)NULL, "", "test", "joihwhhgsdkhksdgsdg\t\v\n\r\f\a25252\b6");
	/* 11 */ test_print_strs_four("%.100s, %.100s, %.100s, %.100s", (char *)NULL, "", "test", "joihwhhgsdkhksdgsdg\t\v\n\r\f\a25252\b6");
	/* 12 */ test_print_strs_four("%1.s, %1.s, %1.s, %1.s", (char *)NULL, "", "test", "joihwhhgsdkhksdgsdg\t\v\n\r\f\a25252\b6");
	/* 13 */ test_print_strs_four("%1.0s, %1.0s, %1.0s, %1.0s", (char *)NULL, "", "test", "joihwhhgsdkhksdgsdg\t\v\n\r\f\a25252\b6");
	/* 14 */ test_print_strs_four("%1.1s, %1.1s, %1.1s, %1.1s", (char *)NULL, "", "test", "joihwhhgsdkhksdgsdg\t\v\n\r\f\a25252\b6");
	/* 15 */ test_print_strs_four("%1.5s, %1.5s, %1.5s, %1.5s", (char *)NULL, "", "test", "joihwhhgsdkhksdgsdg\t\v\n\r\f\a25252\b6");
	/* 16 */ test_print_strs_four("%1.10s, %1.10s, %1.10s, %1.10s", (char *)NULL, "", "test", "joihwhhgsdkhksdgsdg\t\v\n\r\f\a25252\b6");
	/* 17 */ test_print_strs_four("%1.100s, %1.100s, %1.100s, %1.100s", (char *)NULL, "", "test", "joihwhhgsdkhksdgsdg\t\v\n\r\f\a25252\b6");
	/* 18 */ test_print_strs_four("%5.s, %5.s, %5.s, %5.s", (char *)NULL, "", "test", "joihwhhgsdkhksdgsdg\t\v\n\r\f\a25252\b6");
	/* 19 */ test_print_strs_four("%5.0s, %5.0s, %5.0s, %5.0s", (char *)NULL, "", "test", "joihwhhgsdkhksdgsdg\t\v\n\r\f\a25252\b6");
	/* 20 */ test_print_strs_four("%5.1s, %5.1s, %5.1s, %5.1s", (char *)NULL, "", "test", "joihwhhgsdkhksdgsdg\t\v\n\r\f\a25252\b6");
	/* 21 */ test_print_strs_four("%5.5s, %5.5s, %5.5s, %5.5s", (char *)NULL, "", "test", "joihwhhgsdkhksdgsdg\t\v\n\r\f\a25252\b6");
	/* 22 */ test_print_strs_four("%5.10s, %5.10s, %5.10s, %5.10s", (char *)NULL, "", "test", "joihwhhgsdkhksdgsdg\t\v\n\r\f\a25252\b6");
	/* 23 */ test_print_strs_four("%5.100s, %5.100s, %5.100s, %5.100s", (char *)NULL, "", "test", "joihwhhgsdkhksdgsdg\t\v\n\r\f\a25252\b6");
	/* 24 */ test_print_strs_four("%10.s, %10.s, %10.s, %10.s", (char *)NULL, "", "test", "joihwhhgsdkhksdgsdg\t\v\n\r\f\a25252\b6");
	/* 25 */ test_print_strs_four("%10.0s, %10.0s, %10.0s, %10.0s", (char *)NULL, "", "test", "joihwhhgsdkhksdgsdg\t\v\n\r\f\a25252\b6");
	/* 26 */ test_print_strs_four("%10.1s, %10.1s, %10.1s, %10.1s", (char *)NULL, "", "test", "joihwhhgsdkhksdgsdg\t\v\n\r\f\a25252\b6");
	/* 27 */ test_print_strs_four("%10.5s, %10.5s, %10.5s, %10.5s", (char *)NULL, "", "test", "joihwhhgsdkhksdgsdg\t\v\n\r\f\a25252\b6");
	/* 28 */ test_print_strs_four("%10.10s, %10.10s, %10.10s, %10.10s", (char *)NULL, "", "test", "joihwhhgsdkhksdgsdg\t\v\n\r\f\a25252\b6");
	/* 29 */ test_print_strs_four("%10.100s, %10.100s, %10.100s, %10.100s", (char *)NULL, "", "test", "joihwhhgsdkhksdgsdg\t\v\n\r\f\a25252\b6");
	/* 30 */ test_print_strs_four("%100.s, %100.s, %100.s, %100.s", (char *)NULL, "", "test", "joihwhhgsdkhksdgsdg\t\v\n\r\f\a25252\b6");
	/* 31 */ test_print_strs_four("%100.0s, %100.0s, %100.0s, %100.0s", (char *)NULL, "", "test", "joihwhhgsdkhksdgsdg\t\v\n\r\f\a25252\b6");
	/* 32 */ test_print_strs_four("%100.1s, %100.1s, %100.1s, %100.1s", (char *)NULL, "", "test", "joihwhhgsdkhksdgsdg\t\v\n\r\f\a25252\b6");
	/* 33 */ test_print_strs_four("%100.5s, %100.5s, %100.5s, %100.5s", (char *)NULL, "", "test", "joihwhhgsdkhksdgsdg\t\v\n\r\f\a25252\b6");
	/* 34 */ test_print_strs_four("%100.10s, %100.10s, %100.10s, %100.10s", (char *)NULL, "", "test", "joihwhhgsdkhksdgsdg\t\v\n\r\f\a25252\b6");
	/* 35 */ test_print_strs_four("%100.100s, %100.100s, %100.100s, %100.100s", (char *)NULL, "", "test", "joihwhhgsdkhksdgsdg\t\v\n\r\f\a25252\b6");
	/* 36 */ test_print_strs_four("%-s, %-s, %-s, %-s", (char *)NULL, "", "test", "joihwhhgsdkhksdgsdg\t\v\n\r\f\a25252\b6");
	/* 37 */ test_print_strs_four("%-1s, %-1s, %-1s, %-1s", (char *)NULL, "", "test", "joihwhhgsdkhksdgsdg\t\v\n\r\f\a25252\b6");
	/* 38 */ test_print_strs_four("%-5s, %-5s, %-5s, %-5s", (char *)NULL, "", "test", "joihwhhgsdkhksdgsdg\t\v\n\r\f\a25252\b6");
	/* 39 */ test_print_strs_four("%-10s, %-10s, %-10s, %-10s", (char *)NULL, "", "test", "joihwhhgsdkhksdgsdg\t\v\n\r\f\a25252\b6");
	/* 40 */ test_print_strs_four("%-100s, %-100s, %-100s, %-100s", (char *)NULL, "", "test", "joihwhhgsdkhksdgsdg\t\v\n\r\f\a25252\b6");
	/* 41 */ test_print_strs_four("%-.s, %-.s, %-.s, %-.s", (char *)NULL, "", "test", "joihwhhgsdkhksdgsdg\t\v\n\r\f\a25252\b6");
	/* 42 */ test_print_strs_four("%-.0s, %-.0s, %-.0s, %-.0s", (char *)NULL, "", "test", "joihwhhgsdkhksdgsdg\t\v\n\r\f\a25252\b6");
	/* 43 */ test_print_strs_four("%-.1s, %-.1s, %-.1s, %-.1s", (char *)NULL, "", "test", "joihwhhgsdkhksdgsdg\t\v\n\r\f\a25252\b6");
	/* 44 */ test_print_strs_four("%-.5s, %-.5s, %-.5s, %-.5s", (char *)NULL, "", "test", "joihwhhgsdkhksdgsdg\t\v\n\r\f\a25252\b6");
	/* 45 */ test_print_strs_four("%-.10s, %-.10s, %-.10s, %-.10s", (char *)NULL, "", "test", "joihwhhgsdkhksdgsdg\t\v\n\r\f\a25252\b6");
	/* 46 */ test_print_strs_four("%-.100s, %-.100s, %-.100s, %-.100s", (char *)NULL, "", "test", "joihwhhgsdkhksdgsdg\t\v\n\r\f\a25252\b6");
	/* 47 */ test_print_strs_four("%-1.s, %-1.s, %-1.s, %-1.s", (char *)NULL, "", "test", "joihwhhgsdkhksdgsdg\t\v\n\r\f\a25252\b6");
	/* 48 */ test_print_strs_four("%-1.0s, %-1.0s, %-1.0s, %-1.0s", (char *)NULL, "", "test", "joihwhhgsdkhksdgsdg\t\v\n\r\f\a25252\b6");
	/* 49 */ test_print_strs_four("%-1.1s, %-1.1s, %-1.1s, %-1.1s", (char *)NULL, "", "test", "joihwhhgsdkhksdgsdg\t\v\n\r\f\a25252\b6");
	/* 50 */ test_print_strs_four("%-1.5s, %-1.5s, %-1.5s, %-1.5s", (char *)NULL, "", "test", "joihwhhgsdkhksdgsdg\t\v\n\r\f\a25252\b6");
	/* 51 */ test_print_strs_four("%-1.10s, %-1.10s, %-1.10s, %-1.10s", (char *)NULL, "", "test", "joihwhhgsdkhksdgsdg\t\v\n\r\f\a25252\b6");
	/* 52 */ test_print_strs_four("%-1.100s, %-1.100s, %-1.100s, %-1.100s", (char *)NULL, "", "test", "joihwhhgsdkhksdgsdg\t\v\n\r\f\a25252\b6");
	/* 53 */ test_print_strs_four("%-5.s, %-5.s, %-5.s, %-5.s", (char *)NULL, "", "test", "joihwhhgsdkhksdgsdg\t\v\n\r\f\a25252\b6");
	/* 54 */ test_print_strs_four("%-5.0s, %-5.0s, %-5.0s, %-5.0s", (char *)NULL, "", "test", "joihwhhgsdkhksdgsdg\t\v\n\r\f\a25252\b6");
	/* 55 */ test_print_strs_four("%-5.1s, %-5.1s, %-5.1s, %-5.1s", (char *)NULL, "", "test", "joihwhhgsdkhksdgsdg\t\v\n\r\f\a25252\b6");
	/* 56 */ test_print_strs_four("%-5.5s, %-5.5s, %-5.5s, %-5.5s", (char *)NULL, "", "test", "joihwhhgsdkhksdgsdg\t\v\n\r\f\a25252\b6");
	/* 57 */ test_print_strs_four("%-5.10s, %-5.10s, %-5.10s, %-5.10s", (char *)NULL, "", "test", "joihwhhgsdkhksdgsdg\t\v\n\r\f\a25252\b6");
	/* 58 */ test_print_strs_four("%-5.100s, %-5.100s, %-5.100s, %-5.100s", (char *)NULL, "", "test", "joihwhhgsdkhksdgsdg\t\v\n\r\f\a25252\b6");
	/* 59 */ test_print_strs_four("%-10.s, %-10.s, %-10.s, %-10.s", (char *)NULL, "", "test", "joihwhhgsdkhksdgsdg\t\v\n\r\f\a25252\b6");
	/* 60 */ test_print_strs_four("%-10.0s, %-10.0s, %-10.0s, %-10.0s", (char *)NULL, "", "test", "joihwhhgsdkhksdgsdg\t\v\n\r\f\a25252\b6");
	/* 61 */ test_print_strs_four("%-10.1s, %-10.1s, %-10.1s, %-10.1s", (char *)NULL, "", "test", "joihwhhgsdkhksdgsdg\t\v\n\r\f\a25252\b6");
	/* 62 */ test_print_strs_four("%-10.5s, %-10.5s, %-10.5s, %-10.5s", (char *)NULL, "", "test", "joihwhhgsdkhksdgsdg\t\v\n\r\f\a25252\b6");
	/* 63 */ test_print_strs_four("%-10.10s, %-10.10s, %-10.10s, %-10.10s", (char *)NULL, "", "test", "joihwhhgsdkhksdgsdg\t\v\n\r\f\a25252\b6");
	/* 64 */ test_print_strs_four("%-10.100s, %-10.100s, %-10.100s, %-10.100s", (char *)NULL, "", "test", "joihwhhgsdkhksdgsdg\t\v\n\r\f\a25252\b6");
	/* 65 */ test_print_strs_four("%-100.s, %-100.s, %-100.s, %-100.s", (char *)NULL, "", "test", "joihwhhgsdkhksdgsdg\t\v\n\r\f\a25252\b6");
	/* 66 */ test_print_strs_four("%-100.0s, %-100.0s, %-100.0s, %-100.0s", (char *)NULL, "", "test", "joihwhhgsdkhksdgsdg\t\v\n\r\f\a25252\b6");
	/* 67 */ test_print_strs_four("%-100.1s, %-100.1s, %-100.1s, %-100.1s", (char *)NULL, "", "test", "joihwhhgsdkhksdgsdg\t\v\n\r\f\a25252\b6");
	/* 68 */ test_print_strs_four("%-100.5s, %-100.5s, %-100.5s, %-100.5s", (char *)NULL, "", "test", "joihwhhgsdkhksdgsdg\t\v\n\r\f\a25252\b6");
	/* 69 */ test_print_strs_four("%-100.10s, %-100.10s, %-100.10s, %-100.10s", (char *)NULL, "", "test", "joihwhhgsdkhksdgsdg\t\v\n\r\f\a25252\b6");
	/* 70 */ test_print_strs_four("%-100.100s, %-100.100s, %-100.100s, %-100.100s", (char *)NULL, "", "test", "joihwhhgsdkhksdgsdg\t\v\n\r\f\a25252\b6");
}

void test_p() {
	g_current_test_id = 'p';
	/* 1 */ test_print_ptrs_six("%p, %p, %p, %p, %p, %p", (void *)0, (void *)0xABCDE, (void *)ULONG_MAX, (void *)LONG_MIN, (void *)-1, (void *)-2352);
	/* 2 */ test_print_ptrs_six("%1p, %1p, %1p, %1p, %1p, %1p", (void *)0, (void *)0xABCDE, (void *)ULONG_MAX, (void *)LONG_MIN, (void *)-1, (void *)-2352);
	/* 3 */ test_print_ptrs_six("%5p, %5p, %5p, %5p, %5p, %5p", (void *)0, (void *)0xABCDE, (void *)ULONG_MAX, (void *)LONG_MIN, (void *)-1, (void *)-2352);
	/* 4 */ test_print_ptrs_six("%10p, %10p, %10p, %10p, %10p, %10p", (void *)0, (void *)0xABCDE, (void *)ULONG_MAX, (void *)LONG_MIN, (void *)-1, (void *)-2352);
	/* 5 */ test_print_ptrs_six("%100p, %100p, %100p, %100p, %100p, %100p", (void *)0, (void *)0xABCDE, (void *)ULONG_MAX, (void *)LONG_MIN, (void *)-1, (void *)-2352);
	/* 6 */ test_print_ptrs_six("%-p, %-p, %-p, %-p, %-p, %-p", (void *)0, (void *)0xABCDE, (void *)ULONG_MAX, (void *)LONG_MIN, (void *)-1, (void *)-2352);
	/* 7 */ test_print_ptrs_six("%-1p, %-1p, %-1p, %-1p, %-1p, %-1p", (void *)0, (void *)0xABCDE, (void *)ULONG_MAX, (void *)LONG_MIN, (void *)-1, (void *)-2352);
	/* 8 */ test_print_ptrs_six("%-5p, %-5p, %-5p, %-5p, %-5p, %-5p", (void *)0, (void *)0xABCDE, (void *)ULONG_MAX, (void *)LONG_MIN, (void *)-1, (void *)-2352);
	/* 9 */ test_print_ptrs_six("%-10p, %-10p, %-10p, %-10p, %-10p, %-10p", (void *)0, (void *)0xABCDE, (void *)ULONG_MAX, (void *)LONG_MIN, (void *)-1, (void *)-2352);
	/* 10 */ test_print_ptrs_six("%-100p, %-100p, %-100p, %-100p, %-100p, %-100p", (void *)0, (void *)0xABCDE, (void *)ULONG_MAX, (void *)LONG_MIN, (void *)-1, (void *)-2352);
}

void test_d() {
	g_current_test_id = 'd';
	/* 1 */ test_print_int_eight("%d, %d, %d, %d, %d, %d, %d, %d", 0, 5, -1, -10, 100, -1862, INT_MIN, INT_MAX);
	/* 2 */ test_print_int_eight("%1d, %1d, %1d, %1d, %1d, %1d, %1d, %1d", 0, 5, -1, -10, 100, -1862, INT_MIN, INT_MAX);
	/* 3 */ test_print_int_eight("%5d, %5d, %5d, %5d, %5d, %5d, %5d, %5d", 0, 5, -1, -10, 100, -1862, INT_MIN, INT_MAX);
	/* 4 */ test_print_int_eight("%10d, %10d, %10d, %10d, %10d, %10d, %10d, %10d", 0, 5, -1, -10, 100, -1862, INT_MIN, INT_MAX);
	/* 5 */ test_print_int_eight("%100d, %100d, %100d, %100d, %100d, %100d, %100d, %100d", 0, 5, -1, -10, 100, -1862, INT_MIN, INT_MAX);
	/* 6 */ test_print_int_eight("%.d, %.d, %.d, %.d, %.d, %.d, %.d, %.d", 0, 5, -1, -10, 100, -1862, INT_MIN, INT_MAX);
	/* 7 */ test_print_int_eight("%.0d, %.0d, %.0d, %.0d, %.0d, %.0d, %.0d, %.0d", 0, 5, -1, -10, 100, -1862, INT_MIN, INT_MAX);
	/* 8 */ test_print_int_eight("%.1d, %.1d, %.1d, %.1d, %.1d, %.1d, %.1d, %.1d", 0, 5, -1, -10, 100, -1862, INT_MIN, INT_MAX);
	/* 9 */ test_print_int_eight("%.5d, %.5d, %.5d, %.5d, %.5d, %.5d, %.5d, %.5d", 0, 5, -1, -10, 100, -1862, INT_MIN, INT_MAX);
	/* 10 */ test_print_int_eight("%.10d, %.10d, %.10d, %.10d, %.10d, %.10d, %.10d, %.10d", 0, 5, -1, -10, 100, -1862, INT_MIN, INT_MAX);
	/* 11 */ test_print_int_eight("%.100d, %.100d, %.100d, %.100d, %.100d, %.100d, %.100d, %.100d", 0, 5, -1, -10, 100, -1862, INT_MIN, INT_MAX);
	/* 12 */ test_print_int_eight("%1.d, %1.d, %1.d, %1.d, %1.d, %1.d, %1.d, %1.d", 0, 5, -1, -10, 100, -1862, INT_MIN, INT_MAX);
	/* 13 */ test_print_int_eight("%1.0d, %1.0d, %1.0d, %1.0d, %1.0d, %1.0d, %1.0d, %1.0d", 0, 5, -1, -10, 100, -1862, INT_MIN, INT_MAX);
	/* 14 */ test_print_int_eight("%1.1d, %1.1d, %1.1d, %1.1d, %1.1d, %1.1d, %1.1d, %1.1d", 0, 5, -1, -10, 100, -1862, INT_MIN, INT_MAX);
	/* 15 */ test_print_int_eight("%1.5d, %1.5d, %1.5d, %1.5d, %1.5d, %1.5d, %1.5d, %1.5d", 0, 5, -1, -10, 100, -1862, INT_MIN, INT_MAX);
	/* 16 */ test_print_int_eight("%1.10d, %1.10d, %1.10d, %1.10d, %1.10d, %1.10d, %1.10d, %1.10d", 0, 5, -1, -10, 100, -1862, INT_MIN, INT_MAX);
	/* 17 */ test_print_int_eight("%1.100d, %1.100d, %1.100d, %1.100d, %1.100d, %1.100d, %1.100d, %1.100d", 0, 5, -1, -10, 100, -1862, INT_MIN, INT_MAX);
	/* 18 */ test_print_int_eight("%5.d, %5.d, %5.d, %5.d, %5.d, %5.d, %5.d, %5.d", 0, 5, -1, -10, 100, -1862, INT_MIN, INT_MAX);
	/* 19 */ test_print_int_eight("%5.0d, %5.0d, %5.0d, %5.0d, %5.0d, %5.0d, %5.0d, %5.0d", 0, 5, -1, -10, 100, -1862, INT_MIN, INT_MAX);
	/* 20 */ test_print_int_eight("%5.1d, %5.1d, %5.1d, %5.1d, %5.1d, %5.1d, %5.1d, %5.1d", 0, 5, -1, -10, 100, -1862, INT_MIN, INT_MAX);
	/* 21 */ test_print_int_eight("%5.5d, %5.5d, %5.5d, %5.5d, %5.5d, %5.5d, %5.5d, %5.5d", 0, 5, -1, -10, 100, -1862, INT_MIN, INT_MAX);
	/* 22 */ test_print_int_eight("%5.10d, %5.10d, %5.10d, %5.10d, %5.10d, %5.10d, %5.10d, %5.10d", 0, 5, -1, -10, 100, -1862, INT_MIN, INT_MAX);
	/* 23 */ test_print_int_eight("%5.100d, %5.100d, %5.100d, %5.100d, %5.100d, %5.100d, %5.100d, %5.100d", 0, 5, -1, -10, 100, -1862, INT_MIN, INT_MAX);
	/* 24 */ test_print_int_eight("%10.d, %10.d, %10.d, %10.d, %10.d, %10.d, %10.d, %10.d", 0, 5, -1, -10, 100, -1862, INT_MIN, INT_MAX);
	/* 25 */ test_print_int_eight("%10.0d, %10.0d, %10.0d, %10.0d, %10.0d, %10.0d, %10.0d, %10.0d", 0, 5, -1, -10, 100, -1862, INT_MIN, INT_MAX);
	/* 26 */ test_print_int_eight("%10.1d, %10.1d, %10.1d, %10.1d, %10.1d, %10.1d, %10.1d, %10.1d", 0, 5, -1, -10, 100, -1862, INT_MIN, INT_MAX);
	/* 27 */ test_print_int_eight("%10.5d, %10.5d, %10.5d, %10.5d, %10.5d, %10.5d, %10.5d, %10.5d", 0, 5, -1, -10, 100, -1862, INT_MIN, INT_MAX);
	/* 28 */ test_print_int_eight("%10.10d, %10.10d, %10.10d, %10.10d, %10.10d, %10.10d, %10.10d, %10.10d", 0, 5, -1, -10, 100, -1862, INT_MIN, INT_MAX);
	/* 29 */ test_print_int_eight("%10.100d, %10.100d, %10.100d, %10.100d, %10.100d, %10.100d, %10.100d, %10.100d", 0, 5, -1, -10, 100, -1862, INT_MIN, INT_MAX);
	/* 30 */ test_print_int_eight("%100.d, %100.d, %100.d, %100.d, %100.d, %100.d, %100.d, %100.d", 0, 5, -1, -10, 100, -1862, INT_MIN, INT_MAX);
	/* 31 */ test_print_int_eight("%100.0d, %100.0d, %100.0d, %100.0d, %100.0d, %100.0d, %100.0d, %100.0d", 0, 5, -1, -10, 100, -1862, INT_MIN, INT_MAX);
	/* 32 */ test_print_int_eight("%100.1d, %100.1d, %100.1d, %100.1d, %100.1d, %100.1d, %100.1d, %100.1d", 0, 5, -1, -10, 100, -1862, INT_MIN, INT_MAX);
	/* 33 */ test_print_int_eight("%100.5d, %100.5d, %100.5d, %100.5d, %100.5d, %100.5d, %100.5d, %100.5d", 0, 5, -1, -10, 100, -1862, INT_MIN, INT_MAX);
	/* 34 */ test_print_int_eight("%100.10d, %100.10d, %100.10d, %100.10d, %100.10d, %100.10d, %100.10d, %100.10d", 0, 5, -1, -10, 100, -1862, INT_MIN, INT_MAX);
	/* 35 */ test_print_int_eight("%100.100d, %100.100d, %100.100d, %100.100d, %100.100d, %100.100d, %100.100d, %100.100d", 0, 5, -1, -10, 100, -1862, INT_MIN, INT_MAX);
	/* 36 */ test_print_int_eight("%+d, %+d, %+d, %+d, %+d, %+d, %+d, %+d", 0, 5, -1, -10, 100, -1862, INT_MIN, INT_MAX);
	/* 37 */ test_print_int_eight("%+1d, %+1d, %+1d, %+1d, %+1d, %+1d, %+1d, %+1d", 0, 5, -1, -10, 100, -1862, INT_MIN, INT_MAX);
	/* 38 */ test_print_int_eight("%+5d, %+5d, %+5d, %+5d, %+5d, %+5d, %+5d, %+5d", 0, 5, -1, -10, 100, -1862, INT_MIN, INT_MAX);
	/* 39 */ test_print_int_eight("%+10d, %+10d, %+10d, %+10d, %+10d, %+10d, %+10d, %+10d", 0, 5, -1, -10, 100, -1862, INT_MIN, INT_MAX);
	/* 40 */ test_print_int_eight("%+100d, %+100d, %+100d, %+100d, %+100d, %+100d, %+100d, %+100d", 0, 5, -1, -10, 100, -1862, INT_MIN, INT_MAX);
	/* 41 */ test_print_int_eight("%+.d, %+.d, %+.d, %+.d, %+.d, %+.d, %+.d, %+.d", 0, 5, -1, -10, 100, -1862, INT_MIN, INT_MAX);
	/* 42 */ test_print_int_eight("%+.0d, %+.0d, %+.0d, %+.0d, %+.0d, %+.0d, %+.0d, %+.0d", 0, 5, -1, -10, 100, -1862, INT_MIN, INT_MAX);
	/* 43 */ test_print_int_eight("%+.1d, %+.1d, %+.1d, %+.1d, %+.1d, %+.1d, %+.1d, %+.1d", 0, 5, -1, -10, 100, -1862, INT_MIN, INT_MAX);
	/* 44 */ test_print_int_eight("%+.5d, %+.5d, %+.5d, %+.5d, %+.5d, %+.5d, %+.5d, %+.5d", 0, 5, -1, -10, 100, -1862, INT_MIN, INT_MAX);
	/* 45 */ test_print_int_eight("%+.10d, %+.10d, %+.10d, %+.10d, %+.10d, %+.10d, %+.10d, %+.10d", 0, 5, -1, -10, 100, -1862, INT_MIN, INT_MAX);
	/* 46 */ test_print_int_eight("%+.100d, %+.100d, %+.100d, %+.100d, %+.100d, %+.100d, %+.100d, %+.100d", 0, 5, -1, -10, 100, -1862, INT_MIN, INT_MAX);
	/* 47 */ test_print_int_eight("%+1.d, %+1.d, %+1.d, %+1.d, %+1.d, %+1.d, %+1.d, %+1.d", 0, 5, -1, -10, 100, -1862, INT_MIN, INT_MAX);
	/* 48 */ test_print_int_eight("%+1.0d, %+1.0d, %+1.0d, %+1.0d, %+1.0d, %+1.0d, %+1.0d, %+1.0d", 0, 5, -1, -10, 100, -1862, INT_MIN, INT_MAX);
	/* 49 */ test_print_int_eight("%+1.1d, %+1.1d, %+1.1d, %+1.1d, %+1.1d, %+1.1d, %+1.1d, %+1.1d", 0, 5, -1, -10, 100, -1862, INT_MIN, INT_MAX);
	/* 50 */ test_print_int_eight("%+1.5d, %+1.5d, %+1.5d, %+1.5d, %+1.5d, %+1.5d, %+1.5d, %+1.5d", 0, 5, -1, -10, 100, -1862, INT_MIN, INT_MAX);
	/* 51 */ test_print_int_eight("%+1.10d, %+1.10d, %+1.10d, %+1.10d, %+1.10d, %+1.10d, %+1.10d, %+1.10d", 0, 5, -1, -10, 100, -1862, INT_MIN, INT_MAX);
	/* 52 */ test_print_int_eight("%+1.100d, %+1.100d, %+1.100d, %+1.100d, %+1.100d, %+1.100d, %+1.100d, %+1.100d", 0, 5, -1, -10, 100, -1862, INT_MIN, INT_MAX);
	/* 53 */ test_print_int_eight("%+5.d, %+5.d, %+5.d, %+5.d, %+5.d, %+5.d, %+5.d, %+5.d", 0, 5, -1, -10, 100, -1862, INT_MIN, INT_MAX);
	/* 54 */ test_print_int_eight("%+5.0d, %+5.0d, %+5.0d, %+5.0d, %+5.0d, %+5.0d, %+5.0d, %+5.0d", 0, 5, -1, -10, 100, -1862, INT_MIN, INT_MAX);
	/* 55 */ test_print_int_eight("%+5.1d, %+5.1d, %+5.1d, %+5.1d, %+5.1d, %+5.1d, %+5.1d, %+5.1d", 0, 5, -1, -10, 100, -1862, INT_MIN, INT_MAX);
	/* 56 */ test_print_int_eight("%+5.5d, %+5.5d, %+5.5d, %+5.5d, %+5.5d, %+5.5d, %+5.5d, %+5.5d", 0, 5, -1, -10, 100, -1862, INT_MIN, INT_MAX);
	/* 57 */ test_print_int_eight("%+5.10d, %+5.10d, %+5.10d, %+5.10d, %+5.10d, %+5.10d, %+5.10d, %+5.10d", 0, 5, -1, -10, 100, -1862, INT_MIN, INT_MAX);
	/* 58 */ test_print_int_eight("%+5.100d, %+5.100d, %+5.100d, %+5.100d, %+5.100d, %+5.100d, %+5.100d, %+5.100d", 0, 5, -1, -10, 100, -1862, INT_MIN, INT_MAX);
	/* 59 */ test_print_int_eight("%+10.d, %+10.d, %+10.d, %+10.d, %+10.d, %+10.d, %+10.d, %+10.d", 0, 5, -1, -10, 100, -1862, INT_MIN, INT_MAX);
	/* 60 */ test_print_int_eight("%+10.0d, %+10.0d, %+10.0d, %+10.0d, %+10.0d, %+10.0d, %+10.0d, %+10.0d", 0, 5, -1, -10, 100, -1862, INT_MIN, INT_MAX);
	/* 61 */ test_print_int_eight("%+10.1d, %+10.1d, %+10.1d, %+10.1d, %+10.1d, %+10.1d, %+10.1d, %+10.1d", 0, 5, -1, -10, 100, -1862, INT_MIN, INT_MAX);
	/* 62 */ test_print_int_eight("%+10.5d, %+10.5d, %+10.5d, %+10.5d, %+10.5d, %+10.5d, %+10.5d, %+10.5d", 0, 5, -1, -10, 100, -1862, INT_MIN, INT_MAX);
	/* 63 */ test_print_int_eight("%+10.10d, %+10.10d, %+10.10d, %+10.10d, %+10.10d, %+10.10d, %+10.10d, %+10.10d", 0, 5, -1, -10, 100, -1862, INT_MIN, INT_MAX);
	/* 64 */ test_print_int_eight("%+10.100d, %+10.100d, %+10.100d, %+10.100d, %+10.100d, %+10.100d, %+10.100d, %+10.100d", 0, 5, -1, -10, 100, -1862, INT_MIN, INT_MAX);
	/* 65 */ test_print_int_eight("%+100.d, %+100.d, %+100.d, %+100.d, %+100.d, %+100.d, %+100.d, %+100.d", 0, 5, -1, -10, 100, -1862, INT_MIN, INT_MAX);
	/* 66 */ test_print_int_eight("%+100.0d, %+100.0d, %+100.0d, %+100.0d, %+100.0d, %+100.0d, %+100.0d, %+100.0d", 0, 5, -1, -10, 100, -1862, INT_MIN, INT_MAX);
	/* 67 */ test_print_int_eight("%+100.1d, %+100.1d, %+100.1d, %+100.1d, %+100.1d, %+100.1d, %+100.1d, %+100.1d", 0, 5, -1, -10, 100, -1862, INT_MIN, INT_MAX);
	/* 68 */ test_print_int_eight("%+100.5d, %+100.5d, %+100.5d, %+100.5d, %+100.5d, %+100.5d, %+100.5d, %+100.5d", 0, 5, -1, -10, 100, -1862, INT_MIN, INT_MAX);
	/* 69 */ test_print_int_eight("%+100.10d, %+100.10d, %+100.10d, %+100.10d, %+100.10d, %+100.10d, %+100.10d, %+100.10d", 0, 5, -1, -10, 100, -1862, INT_MIN, INT_MAX);
	/* 70 */ test_print_int_eight("%+100.100d, %+100.100d, %+100.100d, %+100.100d, %+100.100d, %+100.100d, %+100.100d, %+100.100d", 0, 5, -1, -10, 100, -1862, INT_MIN, INT_MAX);
	/* 71 */ test_print_int_eight("% d, % d, % d, % d, % d, % d, % d, % d", 0, 5, -1, -10, 100, -1862, INT_MIN, INT_MAX);
	/* 72 */ test_print_int_eight("% 1d, % 1d, % 1d, % 1d, % 1d, % 1d, % 1d, % 1d", 0, 5, -1, -10, 100, -1862, INT_MIN, INT_MAX);
	/* 73 */ test_print_int_eight("% 5d, % 5d, % 5d, % 5d, % 5d, % 5d, % 5d, % 5d", 0, 5, -1, -10, 100, -1862, INT_MIN, INT_MAX);
	/* 74 */ test_print_int_eight("% 10d, % 10d, % 10d, % 10d, % 10d, % 10d, % 10d, % 10d", 0, 5, -1, -10, 100, -1862, INT_MIN, INT_MAX);
	/* 75 */ test_print_int_eight("% 100d, % 100d, % 100d, % 100d, % 100d, % 100d, % 100d, % 100d", 0, 5, -1, -10, 100, -1862, INT_MIN, INT_MAX);
	/* 76 */ test_print_int_eight("% .d, % .d, % .d, % .d, % .d, % .d, % .d, % .d", 0, 5, -1, -10, 100, -1862, INT_MIN, INT_MAX);
	/* 77 */ test_print_int_eight("% .0d, % .0d, % .0d, % .0d, % .0d, % .0d, % .0d, % .0d", 0, 5, -1, -10, 100, -1862, INT_MIN, INT_MAX);
	/* 78 */ test_print_int_eight("% .1d, % .1d, % .1d, % .1d, % .1d, % .1d, % .1d, % .1d", 0, 5, -1, -10, 100, -1862, INT_MIN, INT_MAX);
	/* 79 */ test_print_int_eight("% .5d, % .5d, % .5d, % .5d, % .5d, % .5d, % .5d, % .5d", 0, 5, -1, -10, 100, -1862, INT_MIN, INT_MAX);
	/* 80 */ test_print_int_eight("% .10d, % .10d, % .10d, % .10d, % .10d, % .10d, % .10d, % .10d", 0, 5, -1, -10, 100, -1862, INT_MIN, INT_MAX);
	/* 81 */ test_print_int_eight("% .100d, % .100d, % .100d, % .100d, % .100d, % .100d, % .100d, % .100d", 0, 5, -1, -10, 100, -1862, INT_MIN, INT_MAX);
	/* 82 */ test_print_int_eight("% 1.d, % 1.d, % 1.d, % 1.d, % 1.d, % 1.d, % 1.d, % 1.d", 0, 5, -1, -10, 100, -1862, INT_MIN, INT_MAX);
	/* 83 */ test_print_int_eight("% 1.0d, % 1.0d, % 1.0d, % 1.0d, % 1.0d, % 1.0d, % 1.0d, % 1.0d", 0, 5, -1, -10, 100, -1862, INT_MIN, INT_MAX);
	/* 84 */ test_print_int_eight("% 1.1d, % 1.1d, % 1.1d, % 1.1d, % 1.1d, % 1.1d, % 1.1d, % 1.1d", 0, 5, -1, -10, 100, -1862, INT_MIN, INT_MAX);
	/* 85 */ test_print_int_eight("% 1.5d, % 1.5d, % 1.5d, % 1.5d, % 1.5d, % 1.5d, % 1.5d, % 1.5d", 0, 5, -1, -10, 100, -1862, INT_MIN, INT_MAX);
	/* 86 */ test_print_int_eight("% 1.10d, % 1.10d, % 1.10d, % 1.10d, % 1.10d, % 1.10d, % 1.10d, % 1.10d", 0, 5, -1, -10, 100, -1862, INT_MIN, INT_MAX);
	/* 87 */ test_print_int_eight("% 1.100d, % 1.100d, % 1.100d, % 1.100d, % 1.100d, % 1.100d, % 1.100d, % 1.100d", 0, 5, -1, -10, 100, -1862, INT_MIN, INT_MAX);
	/* 88 */ test_print_int_eight("% 5.d, % 5.d, % 5.d, % 5.d, % 5.d, % 5.d, % 5.d, % 5.d", 0, 5, -1, -10, 100, -1862, INT_MIN, INT_MAX);
	/* 89 */ test_print_int_eight("% 5.0d, % 5.0d, % 5.0d, % 5.0d, % 5.0d, % 5.0d, % 5.0d, % 5.0d", 0, 5, -1, -10, 100, -1862, INT_MIN, INT_MAX);
	/* 90 */ test_print_int_eight("% 5.1d, % 5.1d, % 5.1d, % 5.1d, % 5.1d, % 5.1d, % 5.1d, % 5.1d", 0, 5, -1, -10, 100, -1862, INT_MIN, INT_MAX);
	/* 91 */ test_print_int_eight("% 5.5d, % 5.5d, % 5.5d, % 5.5d, % 5.5d, % 5.5d, % 5.5d, % 5.5d", 0, 5, -1, -10, 100, -1862, INT_MIN, INT_MAX);
	/* 92 */ test_print_int_eight("% 5.10d, % 5.10d, % 5.10d, % 5.10d, % 5.10d, % 5.10d, % 5.10d, % 5.10d", 0, 5, -1, -10, 100, -1862, INT_MIN, INT_MAX);
	/* 93 */ test_print_int_eight("% 5.100d, % 5.100d, % 5.100d, % 5.100d, % 5.100d, % 5.100d, % 5.100d, % 5.100d", 0, 5, -1, -10, 100, -1862, INT_MIN, INT_MAX);
	/* 94 */ test_print_int_eight("% 10.d, % 10.d, % 10.d, % 10.d, % 10.d, % 10.d, % 10.d, % 10.d", 0, 5, -1, -10, 100, -1862, INT_MIN, INT_MAX);
	/* 95 */ test_print_int_eight("% 10.0d, % 10.0d, % 10.0d, % 10.0d, % 10.0d, % 10.0d, % 10.0d, % 10.0d", 0, 5, -1, -10, 100, -1862, INT_MIN, INT_MAX);
	/* 96 */ test_print_int_eight("% 10.1d, % 10.1d, % 10.1d, % 10.1d, % 10.1d, % 10.1d, % 10.1d, % 10.1d", 0, 5, -1, -10, 100, -1862, INT_MIN, INT_MAX);
	/* 97 */ test_print_int_eight("% 10.5d, % 10.5d, % 10.5d, % 10.5d, % 10.5d, % 10.5d, % 10.5d, % 10.5d", 0, 5, -1, -10, 100, -1862, INT_MIN, INT_MAX);
	/* 98 */ test_print_int_eight("% 10.10d, % 10.10d, % 10.10d, % 10.10d, % 10.10d, % 10.10d, % 10.10d, % 10.10d", 0, 5, -1, -10, 100, -1862, INT_MIN, INT_MAX);
	/* 99 */ test_print_int_eight("% 10.100d, % 10.100d, % 10.100d, % 10.100d, % 10.100d, % 10.100d, % 10.100d, % 10.100d", 0, 5, -1, -10, 100, -1862, INT_MIN, INT_MAX);
	/* 100 */ test_print_int_eight("% 100.d, % 100.d, % 100.d, % 100.d, % 100.d, % 100.d, % 100.d, % 100.d", 0, 5, -1, -10, 100, -1862, INT_MIN, INT_MAX);
	/* 101 */ test_print_int_eight("% 100.0d, % 100.0d, % 100.0d, % 100.0d, % 100.0d, % 100.0d, % 100.0d, % 100.0d", 0, 5, -1, -10, 100, -1862, INT_MIN, INT_MAX);
	/* 102 */ test_print_int_eight("% 100.1d, % 100.1d, % 100.1d, % 100.1d, % 100.1d, % 100.1d, % 100.1d, % 100.1d", 0, 5, -1, -10, 100, -1862, INT_MIN, INT_MAX);
	/* 103 */ test_print_int_eight("% 100.5d, % 100.5d, % 100.5d, % 100.5d, % 100.5d, % 100.5d, % 100.5d, % 100.5d", 0, 5, -1, -10, 100, -1862, INT_MIN, INT_MAX);
	/* 104 */ test_print_int_eight("% 100.10d, % 100.10d, % 100.10d, % 100.10d, % 100.10d, % 100.10d, % 100.10d, % 100.10d", 0, 5, -1, -10, 100, -1862, INT_MIN, INT_MAX);
	/* 105 */ test_print_int_eight("% 100.100d, % 100.100d, % 100.100d, % 100.100d, % 100.100d, % 100.100d, % 100.100d, % 100.100d", 0, 5, -1, -10, 100, -1862, INT_MIN, INT_MAX);
	/* 106 */ test_print_int_eight("%0d, %0d, %0d, %0d, %0d, %0d, %0d, %0d", 0, 5, -1, -10, 100, -1862, INT_MIN, INT_MAX);
	/* 107 */ test_print_int_eight("%01d, %01d, %01d, %01d, %01d, %01d, %01d, %01d", 0, 5, -1, -10, 100, -1862, INT_MIN, INT_MAX);
	/* 108 */ test_print_int_eight("%05d, %05d, %05d, %05d, %05d, %05d, %05d, %05d", 0, 5, -1, -10, 100, -1862, INT_MIN, INT_MAX);
	/* 109 */ test_print_int_eight("%010d, %010d, %010d, %010d, %010d, %010d, %010d, %010d", 0, 5, -1, -10, 100, -1862, INT_MIN, INT_MAX);
	/* 110 */ test_print_int_eight("%0100d, %0100d, %0100d, %0100d, %0100d, %0100d, %0100d, %0100d", 0, 5, -1, -10, 100, -1862, INT_MIN, INT_MAX);
	/* 111 */ test_print_int_eight("%0.d, %0.d, %0.d, %0.d, %0.d, %0.d, %0.d, %0.d", 0, 5, -1, -10, 100, -1862, INT_MIN, INT_MAX);
	/* 112 */ test_print_int_eight("%0.0d, %0.0d, %0.0d, %0.0d, %0.0d, %0.0d, %0.0d, %0.0d", 0, 5, -1, -10, 100, -1862, INT_MIN, INT_MAX);
	/* 113 */ test_print_int_eight("%0.1d, %0.1d, %0.1d, %0.1d, %0.1d, %0.1d, %0.1d, %0.1d", 0, 5, -1, -10, 100, -1862, INT_MIN, INT_MAX);
	/* 114 */ test_print_int_eight("%0.5d, %0.5d, %0.5d, %0.5d, %0.5d, %0.5d, %0.5d, %0.5d", 0, 5, -1, -10, 100, -1862, INT_MIN, INT_MAX);
	/* 115 */ test_print_int_eight("%0.10d, %0.10d, %0.10d, %0.10d, %0.10d, %0.10d, %0.10d, %0.10d", 0, 5, -1, -10, 100, -1862, INT_MIN, INT_MAX);
	/* 116 */ test_print_int_eight("%0.100d, %0.100d, %0.100d, %0.100d, %0.100d, %0.100d, %0.100d, %0.100d", 0, 5, -1, -10, 100, -1862, INT_MIN, INT_MAX);
	/* 117 */ test_print_int_eight("%01.d, %01.d, %01.d, %01.d, %01.d, %01.d, %01.d, %01.d", 0, 5, -1, -10, 100, -1862, INT_MIN, INT_MAX);
	/* 118 */ test_print_int_eight("%01.0d, %01.0d, %01.0d, %01.0d, %01.0d, %01.0d, %01.0d, %01.0d", 0, 5, -1, -10, 100, -1862, INT_MIN, INT_MAX);
	/* 119 */ test_print_int_eight("%01.1d, %01.1d, %01.1d, %01.1d, %01.1d, %01.1d, %01.1d, %01.1d", 0, 5, -1, -10, 100, -1862, INT_MIN, INT_MAX);
	/* 120 */ test_print_int_eight("%01.5d, %01.5d, %01.5d, %01.5d, %01.5d, %01.5d, %01.5d, %01.5d", 0, 5, -1, -10, 100, -1862, INT_MIN, INT_MAX);
	/* 121 */ test_print_int_eight("%01.10d, %01.10d, %01.10d, %01.10d, %01.10d, %01.10d, %01.10d, %01.10d", 0, 5, -1, -10, 100, -1862, INT_MIN, INT_MAX);
	/* 122 */ test_print_int_eight("%01.100d, %01.100d, %01.100d, %01.100d, %01.100d, %01.100d, %01.100d, %01.100d", 0, 5, -1, -10, 100, -1862, INT_MIN, INT_MAX);
	/* 123 */ test_print_int_eight("%05.d, %05.d, %05.d, %05.d, %05.d, %05.d, %05.d, %05.d", 0, 5, -1, -10, 100, -1862, INT_MIN, INT_MAX);
	/* 124 */ test_print_int_eight("%05.0d, %05.0d, %05.0d, %05.0d, %05.0d, %05.0d, %05.0d, %05.0d", 0, 5, -1, -10, 100, -1862, INT_MIN, INT_MAX);
	/* 125 */ test_print_int_eight("%05.1d, %05.1d, %05.1d, %05.1d, %05.1d, %05.1d, %05.1d, %05.1d", 0, 5, -1, -10, 100, -1862, INT_MIN, INT_MAX);
	/* 126 */ test_print_int_eight("%05.5d, %05.5d, %05.5d, %05.5d, %05.5d, %05.5d, %05.5d, %05.5d", 0, 5, -1, -10, 100, -1862, INT_MIN, INT_MAX);
	/* 127 */ test_print_int_eight("%05.10d, %05.10d, %05.10d, %05.10d, %05.10d, %05.10d, %05.10d, %05.10d", 0, 5, -1, -10, 100, -1862, INT_MIN, INT_MAX);
	/* 128 */ test_print_int_eight("%05.100d, %05.100d, %05.100d, %05.100d, %05.100d, %05.100d, %05.100d, %05.100d", 0, 5, -1, -10, 100, -1862, INT_MIN, INT_MAX);
	/* 129 */ test_print_int_eight("%010.d, %010.d, %010.d, %010.d, %010.d, %010.d, %010.d, %010.d", 0, 5, -1, -10, 100, -1862, INT_MIN, INT_MAX);
	/* 130 */ test_print_int_eight("%010.0d, %010.0d, %010.0d, %010.0d, %010.0d, %010.0d, %010.0d, %010.0d", 0, 5, -1, -10, 100, -1862, INT_MIN, INT_MAX);
	/* 131 */ test_print_int_eight("%010.1d, %010.1d, %010.1d, %010.1d, %010.1d, %010.1d, %010.1d, %010.1d", 0, 5, -1, -10, 100, -1862, INT_MIN, INT_MAX);
	/* 132 */ test_print_int_eight("%010.5d, %010.5d, %010.5d, %010.5d, %010.5d, %010.5d, %010.5d, %010.5d", 0, 5, -1, -10, 100, -1862, INT_MIN, INT_MAX);
	/* 133 */ test_print_int_eight("%010.10d, %010.10d, %010.10d, %010.10d, %010.10d, %010.10d, %010.10d, %010.10d", 0, 5, -1, -10, 100, -1862, INT_MIN, INT_MAX);
	/* 134 */ test_print_int_eight("%010.100d, %010.100d, %010.100d, %010.100d, %010.100d, %010.100d, %010.100d, %010.100d", 0, 5, -1, -10, 100, -1862, INT_MIN, INT_MAX);
	/* 135 */ test_print_int_eight("%0100.d, %0100.d, %0100.d, %0100.d, %0100.d, %0100.d, %0100.d, %0100.d", 0, 5, -1, -10, 100, -1862, INT_MIN, INT_MAX);
	/* 136 */ test_print_int_eight("%0100.0d, %0100.0d, %0100.0d, %0100.0d, %0100.0d, %0100.0d, %0100.0d, %0100.0d", 0, 5, -1, -10, 100, -1862, INT_MIN, INT_MAX);
	/* 137 */ test_print_int_eight("%0100.1d, %0100.1d, %0100.1d, %0100.1d, %0100.1d, %0100.1d, %0100.1d, %0100.1d", 0, 5, -1, -10, 100, -1862, INT_MIN, INT_MAX);
	/* 138 */ test_print_int_eight("%0100.5d, %0100.5d, %0100.5d, %0100.5d, %0100.5d, %0100.5d, %0100.5d, %0100.5d", 0, 5, -1, -10, 100, -1862, INT_MIN, INT_MAX);
	/* 139 */ test_print_int_eight("%0100.10d, %0100.10d, %0100.10d, %0100.10d, %0100.10d, %0100.10d, %0100.10d, %0100.10d", 0, 5, -1, -10, 100, -1862, INT_MIN, INT_MAX);
	/* 140 */ test_print_int_eight("%0100.100d, %0100.100d, %0100.100d, %0100.100d, %0100.100d, %0100.100d, %0100.100d, %0100.100d", 0, 5, -1, -10, 100, -1862, INT_MIN, INT_MAX);
	/* 141 */ test_print_int_eight("%0+d, %0+d, %0+d, %0+d, %0+d, %0+d, %0+d, %0+d", 0, 5, -1, -10, 100, -1862, INT_MIN, INT_MAX);
	/* 142 */ test_print_int_eight("%0+1d, %0+1d, %0+1d, %0+1d, %0+1d, %0+1d, %0+1d, %0+1d", 0, 5, -1, -10, 100, -1862, INT_MIN, INT_MAX);
	/* 143 */ test_print_int_eight("%0+5d, %0+5d, %0+5d, %0+5d, %0+5d, %0+5d, %0+5d, %0+5d", 0, 5, -1, -10, 100, -1862, INT_MIN, INT_MAX);
	/* 144 */ test_print_int_eight("%0+10d, %0+10d, %0+10d, %0+10d, %0+10d, %0+10d, %0+10d, %0+10d", 0, 5, -1, -10, 100, -1862, INT_MIN, INT_MAX);
	/* 145 */ test_print_int_eight("%0+100d, %0+100d, %0+100d, %0+100d, %0+100d, %0+100d, %0+100d, %0+100d", 0, 5, -1, -10, 100, -1862, INT_MIN, INT_MAX);
	/* 146 */ test_print_int_eight("%0+.d, %0+.d, %0+.d, %0+.d, %0+.d, %0+.d, %0+.d, %0+.d", 0, 5, -1, -10, 100, -1862, INT_MIN, INT_MAX);
	/* 147 */ test_print_int_eight("%0+.0d, %0+.0d, %0+.0d, %0+.0d, %0+.0d, %0+.0d, %0+.0d, %0+.0d", 0, 5, -1, -10, 100, -1862, INT_MIN, INT_MAX);
	/* 148 */ test_print_int_eight("%0+.1d, %0+.1d, %0+.1d, %0+.1d, %0+.1d, %0+.1d, %0+.1d, %0+.1d", 0, 5, -1, -10, 100, -1862, INT_MIN, INT_MAX);
	/* 149 */ test_print_int_eight("%0+.5d, %0+.5d, %0+.5d, %0+.5d, %0+.5d, %0+.5d, %0+.5d, %0+.5d", 0, 5, -1, -10, 100, -1862, INT_MIN, INT_MAX);
	/* 150 */ test_print_int_eight("%0+.10d, %0+.10d, %0+.10d, %0+.10d, %0+.10d, %0+.10d, %0+.10d, %0+.10d", 0, 5, -1, -10, 100, -1862, INT_MIN, INT_MAX);
	/* 151 */ test_print_int_eight("%0+.100d, %0+.100d, %0+.100d, %0+.100d, %0+.100d, %0+.100d, %0+.100d, %0+.100d", 0, 5, -1, -10, 100, -1862, INT_MIN, INT_MAX);
	/* 152 */ test_print_int_eight("%0+1.d, %0+1.d, %0+1.d, %0+1.d, %0+1.d, %0+1.d, %0+1.d, %0+1.d", 0, 5, -1, -10, 100, -1862, INT_MIN, INT_MAX);
	/* 153 */ test_print_int_eight("%0+1.0d, %0+1.0d, %0+1.0d, %0+1.0d, %0+1.0d, %0+1.0d, %0+1.0d, %0+1.0d", 0, 5, -1, -10, 100, -1862, INT_MIN, INT_MAX);
	/* 154 */ test_print_int_eight("%0+1.1d, %0+1.1d, %0+1.1d, %0+1.1d, %0+1.1d, %0+1.1d, %0+1.1d, %0+1.1d", 0, 5, -1, -10, 100, -1862, INT_MIN, INT_MAX);
	/* 155 */ test_print_int_eight("%0+1.5d, %0+1.5d, %0+1.5d, %0+1.5d, %0+1.5d, %0+1.5d, %0+1.5d, %0+1.5d", 0, 5, -1, -10, 100, -1862, INT_MIN, INT_MAX);
	/* 156 */ test_print_int_eight("%0+1.10d, %0+1.10d, %0+1.10d, %0+1.10d, %0+1.10d, %0+1.10d, %0+1.10d, %0+1.10d", 0, 5, -1, -10, 100, -1862, INT_MIN, INT_MAX);
	/* 157 */ test_print_int_eight("%0+1.100d, %0+1.100d, %0+1.100d, %0+1.100d, %0+1.100d, %0+1.100d, %0+1.100d, %0+1.100d", 0, 5, -1, -10, 100, -1862, INT_MIN, INT_MAX);
	/* 158 */ test_print_int_eight("%0+5.d, %0+5.d, %0+5.d, %0+5.d, %0+5.d, %0+5.d, %0+5.d, %0+5.d", 0, 5, -1, -10, 100, -1862, INT_MIN, INT_MAX);
	/* 159 */ test_print_int_eight("%0+5.0d, %0+5.0d, %0+5.0d, %0+5.0d, %0+5.0d, %0+5.0d, %0+5.0d, %0+5.0d", 0, 5, -1, -10, 100, -1862, INT_MIN, INT_MAX);
	/* 160 */ test_print_int_eight("%0+5.1d, %0+5.1d, %0+5.1d, %0+5.1d, %0+5.1d, %0+5.1d, %0+5.1d, %0+5.1d", 0, 5, -1, -10, 100, -1862, INT_MIN, INT_MAX);
	/* 161 */ test_print_int_eight("%0+5.5d, %0+5.5d, %0+5.5d, %0+5.5d, %0+5.5d, %0+5.5d, %0+5.5d, %0+5.5d", 0, 5, -1, -10, 100, -1862, INT_MIN, INT_MAX);
	/* 162 */ test_print_int_eight("%0+5.10d, %0+5.10d, %0+5.10d, %0+5.10d, %0+5.10d, %0+5.10d, %0+5.10d, %0+5.10d", 0, 5, -1, -10, 100, -1862, INT_MIN, INT_MAX);
	/* 163 */ test_print_int_eight("%0+5.100d, %0+5.100d, %0+5.100d, %0+5.100d, %0+5.100d, %0+5.100d, %0+5.100d, %0+5.100d", 0, 5, -1, -10, 100, -1862, INT_MIN, INT_MAX);
	/* 164 */ test_print_int_eight("%0+10.d, %0+10.d, %0+10.d, %0+10.d, %0+10.d, %0+10.d, %0+10.d, %0+10.d", 0, 5, -1, -10, 100, -1862, INT_MIN, INT_MAX);
	/* 165 */ test_print_int_eight("%0+10.0d, %0+10.0d, %0+10.0d, %0+10.0d, %0+10.0d, %0+10.0d, %0+10.0d, %0+10.0d", 0, 5, -1, -10, 100, -1862, INT_MIN, INT_MAX);
	/* 166 */ test_print_int_eight("%0+10.1d, %0+10.1d, %0+10.1d, %0+10.1d, %0+10.1d, %0+10.1d, %0+10.1d, %0+10.1d", 0, 5, -1, -10, 100, -1862, INT_MIN, INT_MAX);
	/* 167 */ test_print_int_eight("%0+10.5d, %0+10.5d, %0+10.5d, %0+10.5d, %0+10.5d, %0+10.5d, %0+10.5d, %0+10.5d", 0, 5, -1, -10, 100, -1862, INT_MIN, INT_MAX);
	/* 168 */ test_print_int_eight("%0+10.10d, %0+10.10d, %0+10.10d, %0+10.10d, %0+10.10d, %0+10.10d, %0+10.10d, %0+10.10d", 0, 5, -1, -10, 100, -1862, INT_MIN, INT_MAX);
	/* 169 */ test_print_int_eight("%0+10.100d, %0+10.100d, %0+10.100d, %0+10.100d, %0+10.100d, %0+10.100d, %0+10.100d, %0+10.100d", 0, 5, -1, -10, 100, -1862, INT_MIN, INT_MAX);
	/* 170 */ test_print_int_eight("%0+100.d, %0+100.d, %0+100.d, %0+100.d, %0+100.d, %0+100.d, %0+100.d, %0+100.d", 0, 5, -1, -10, 100, -1862, INT_MIN, INT_MAX);
	/* 171 */ test_print_int_eight("%0+100.0d, %0+100.0d, %0+100.0d, %0+100.0d, %0+100.0d, %0+100.0d, %0+100.0d, %0+100.0d", 0, 5, -1, -10, 100, -1862, INT_MIN, INT_MAX);
	/* 172 */ test_print_int_eight("%0+100.1d, %0+100.1d, %0+100.1d, %0+100.1d, %0+100.1d, %0+100.1d, %0+100.1d, %0+100.1d", 0, 5, -1, -10, 100, -1862, INT_MIN, INT_MAX);
	/* 173 */ test_print_int_eight("%0+100.5d, %0+100.5d, %0+100.5d, %0+100.5d, %0+100.5d, %0+100.5d, %0+100.5d, %0+100.5d", 0, 5, -1, -10, 100, -1862, INT_MIN, INT_MAX);
	/* 174 */ test_print_int_eight("%0+100.10d, %0+100.10d, %0+100.10d, %0+100.10d, %0+100.10d, %0+100.10d, %0+100.10d, %0+100.10d", 0, 5, -1, -10, 100, -1862, INT_MIN, INT_MAX);
	/* 175 */ test_print_int_eight("%0+100.100d, %0+100.100d, %0+100.100d, %0+100.100d, %0+100.100d, %0+100.100d, %0+100.100d, %0+100.100d", 0, 5, -1, -10, 100, -1862, INT_MIN, INT_MAX);
	/* 176 */ test_print_int_eight("%0 d, %0 d, %0 d, %0 d, %0 d, %0 d, %0 d, %0 d", 0, 5, -1, -10, 100, -1862, INT_MIN, INT_MAX);
	/* 177 */ test_print_int_eight("%0 1d, %0 1d, %0 1d, %0 1d, %0 1d, %0 1d, %0 1d, %0 1d", 0, 5, -1, -10, 100, -1862, INT_MIN, INT_MAX);
	/* 178 */ test_print_int_eight("%0 5d, %0 5d, %0 5d, %0 5d, %0 5d, %0 5d, %0 5d, %0 5d", 0, 5, -1, -10, 100, -1862, INT_MIN, INT_MAX);
	/* 179 */ test_print_int_eight("%0 10d, %0 10d, %0 10d, %0 10d, %0 10d, %0 10d, %0 10d, %0 10d", 0, 5, -1, -10, 100, -1862, INT_MIN, INT_MAX);
	/* 180 */ test_print_int_eight("%0 100d, %0 100d, %0 100d, %0 100d, %0 100d, %0 100d, %0 100d, %0 100d", 0, 5, -1, -10, 100, -1862, INT_MIN, INT_MAX);
	/* 181 */ test_print_int_eight("%0 .d, %0 .d, %0 .d, %0 .d, %0 .d, %0 .d, %0 .d, %0 .d", 0, 5, -1, -10, 100, -1862, INT_MIN, INT_MAX);
	/* 182 */ test_print_int_eight("%0 .0d, %0 .0d, %0 .0d, %0 .0d, %0 .0d, %0 .0d, %0 .0d, %0 .0d", 0, 5, -1, -10, 100, -1862, INT_MIN, INT_MAX);
	/* 183 */ test_print_int_eight("%0 .1d, %0 .1d, %0 .1d, %0 .1d, %0 .1d, %0 .1d, %0 .1d, %0 .1d", 0, 5, -1, -10, 100, -1862, INT_MIN, INT_MAX);
	/* 184 */ test_print_int_eight("%0 .5d, %0 .5d, %0 .5d, %0 .5d, %0 .5d, %0 .5d, %0 .5d, %0 .5d", 0, 5, -1, -10, 100, -1862, INT_MIN, INT_MAX);
	/* 185 */ test_print_int_eight("%0 .10d, %0 .10d, %0 .10d, %0 .10d, %0 .10d, %0 .10d, %0 .10d, %0 .10d", 0, 5, -1, -10, 100, -1862, INT_MIN, INT_MAX);
	/* 186 */ test_print_int_eight("%0 .100d, %0 .100d, %0 .100d, %0 .100d, %0 .100d, %0 .100d, %0 .100d, %0 .100d", 0, 5, -1, -10, 100, -1862, INT_MIN, INT_MAX);
	/* 187 */ test_print_int_eight("%0 1.d, %0 1.d, %0 1.d, %0 1.d, %0 1.d, %0 1.d, %0 1.d, %0 1.d", 0, 5, -1, -10, 100, -1862, INT_MIN, INT_MAX);
	/* 188 */ test_print_int_eight("%0 1.0d, %0 1.0d, %0 1.0d, %0 1.0d, %0 1.0d, %0 1.0d, %0 1.0d, %0 1.0d", 0, 5, -1, -10, 100, -1862, INT_MIN, INT_MAX);
	/* 189 */ test_print_int_eight("%0 1.1d, %0 1.1d, %0 1.1d, %0 1.1d, %0 1.1d, %0 1.1d, %0 1.1d, %0 1.1d", 0, 5, -1, -10, 100, -1862, INT_MIN, INT_MAX);
	/* 190 */ test_print_int_eight("%0 1.5d, %0 1.5d, %0 1.5d, %0 1.5d, %0 1.5d, %0 1.5d, %0 1.5d, %0 1.5d", 0, 5, -1, -10, 100, -1862, INT_MIN, INT_MAX);
	/* 191 */ test_print_int_eight("%0 1.10d, %0 1.10d, %0 1.10d, %0 1.10d, %0 1.10d, %0 1.10d, %0 1.10d, %0 1.10d", 0, 5, -1, -10, 100, -1862, INT_MIN, INT_MAX);
	/* 192 */ test_print_int_eight("%0 1.100d, %0 1.100d, %0 1.100d, %0 1.100d, %0 1.100d, %0 1.100d, %0 1.100d, %0 1.100d", 0, 5, -1, -10, 100, -1862, INT_MIN, INT_MAX);
	/* 193 */ test_print_int_eight("%0 5.d, %0 5.d, %0 5.d, %0 5.d, %0 5.d, %0 5.d, %0 5.d, %0 5.d", 0, 5, -1, -10, 100, -1862, INT_MIN, INT_MAX);
	/* 194 */ test_print_int_eight("%0 5.0d, %0 5.0d, %0 5.0d, %0 5.0d, %0 5.0d, %0 5.0d, %0 5.0d, %0 5.0d", 0, 5, -1, -10, 100, -1862, INT_MIN, INT_MAX);
	/* 195 */ test_print_int_eight("%0 5.1d, %0 5.1d, %0 5.1d, %0 5.1d, %0 5.1d, %0 5.1d, %0 5.1d, %0 5.1d", 0, 5, -1, -10, 100, -1862, INT_MIN, INT_MAX);
	/* 196 */ test_print_int_eight("%0 5.5d, %0 5.5d, %0 5.5d, %0 5.5d, %0 5.5d, %0 5.5d, %0 5.5d, %0 5.5d", 0, 5, -1, -10, 100, -1862, INT_MIN, INT_MAX);
	/* 197 */ test_print_int_eight("%0 5.10d, %0 5.10d, %0 5.10d, %0 5.10d, %0 5.10d, %0 5.10d, %0 5.10d, %0 5.10d", 0, 5, -1, -10, 100, -1862, INT_MIN, INT_MAX);
	/* 198 */ test_print_int_eight("%0 5.100d, %0 5.100d, %0 5.100d, %0 5.100d, %0 5.100d, %0 5.100d, %0 5.100d, %0 5.100d", 0, 5, -1, -10, 100, -1862, INT_MIN, INT_MAX);
	/* 199 */ test_print_int_eight("%0 10.d, %0 10.d, %0 10.d, %0 10.d, %0 10.d, %0 10.d, %0 10.d, %0 10.d", 0, 5, -1, -10, 100, -1862, INT_MIN, INT_MAX);
	/* 200 */ test_print_int_eight("%0 10.0d, %0 10.0d, %0 10.0d, %0 10.0d, %0 10.0d, %0 10.0d, %0 10.0d, %0 10.0d", 0, 5, -1, -10, 100, -1862, INT_MIN, INT_MAX);
	/* 201 */ test_print_int_eight("%0 10.1d, %0 10.1d, %0 10.1d, %0 10.1d, %0 10.1d, %0 10.1d, %0 10.1d, %0 10.1d", 0, 5, -1, -10, 100, -1862, INT_MIN, INT_MAX);
	/* 202 */ test_print_int_eight("%0 10.5d, %0 10.5d, %0 10.5d, %0 10.5d, %0 10.5d, %0 10.5d, %0 10.5d, %0 10.5d", 0, 5, -1, -10, 100, -1862, INT_MIN, INT_MAX);
	/* 203 */ test_print_int_eight("%0 10.10d, %0 10.10d, %0 10.10d, %0 10.10d, %0 10.10d, %0 10.10d, %0 10.10d, %0 10.10d", 0, 5, -1, -10, 100, -1862, INT_MIN, INT_MAX);
	/* 204 */ test_print_int_eight("%0 10.100d, %0 10.100d, %0 10.100d, %0 10.100d, %0 10.100d, %0 10.100d, %0 10.100d, %0 10.100d", 0, 5, -1, -10, 100, -1862, INT_MIN, INT_MAX);
	/* 205 */ test_print_int_eight("%0 100.d, %0 100.d, %0 100.d, %0 100.d, %0 100.d, %0 100.d, %0 100.d, %0 100.d", 0, 5, -1, -10, 100, -1862, INT_MIN, INT_MAX);
	/* 206 */ test_print_int_eight("%0 100.0d, %0 100.0d, %0 100.0d, %0 100.0d, %0 100.0d, %0 100.0d, %0 100.0d, %0 100.0d", 0, 5, -1, -10, 100, -1862, INT_MIN, INT_MAX);
	/* 207 */ test_print_int_eight("%0 100.1d, %0 100.1d, %0 100.1d, %0 100.1d, %0 100.1d, %0 100.1d, %0 100.1d, %0 100.1d", 0, 5, -1, -10, 100, -1862, INT_MIN, INT_MAX);
	/* 208 */ test_print_int_eight("%0 100.5d, %0 100.5d, %0 100.5d, %0 100.5d, %0 100.5d, %0 100.5d, %0 100.5d, %0 100.5d", 0, 5, -1, -10, 100, -1862, INT_MIN, INT_MAX);
	/* 209 */ test_print_int_eight("%0 100.10d, %0 100.10d, %0 100.10d, %0 100.10d, %0 100.10d, %0 100.10d, %0 100.10d, %0 100.10d", 0, 5, -1, -10, 100, -1862, INT_MIN, INT_MAX);
	/* 210 */ test_print_int_eight("%0 100.100d, %0 100.100d, %0 100.100d, %0 100.100d, %0 100.100d, %0 100.100d, %0 100.100d, %0 100.100d", 0, 5, -1, -10, 100, -1862, INT_MIN, INT_MAX);
	/* 211 */ test_print_int_eight("%-d, %-d, %-d, %-d, %-d, %-d, %-d, %-d", 0, 5, -1, -10, 100, -1862, INT_MIN, INT_MAX);
	/* 212 */ test_print_int_eight("%-1d, %-1d, %-1d, %-1d, %-1d, %-1d, %-1d, %-1d", 0, 5, -1, -10, 100, -1862, INT_MIN, INT_MAX);
	/* 213 */ test_print_int_eight("%-5d, %-5d, %-5d, %-5d, %-5d, %-5d, %-5d, %-5d", 0, 5, -1, -10, 100, -1862, INT_MIN, INT_MAX);
	/* 214 */ test_print_int_eight("%-10d, %-10d, %-10d, %-10d, %-10d, %-10d, %-10d, %-10d", 0, 5, -1, -10, 100, -1862, INT_MIN, INT_MAX);
	/* 215 */ test_print_int_eight("%-100d, %-100d, %-100d, %-100d, %-100d, %-100d, %-100d, %-100d", 0, 5, -1, -10, 100, -1862, INT_MIN, INT_MAX);
	/* 216 */ test_print_int_eight("%-.d, %-.d, %-.d, %-.d, %-.d, %-.d, %-.d, %-.d", 0, 5, -1, -10, 100, -1862, INT_MIN, INT_MAX);
	/* 217 */ test_print_int_eight("%-.0d, %-.0d, %-.0d, %-.0d, %-.0d, %-.0d, %-.0d, %-.0d", 0, 5, -1, -10, 100, -1862, INT_MIN, INT_MAX);
	/* 218 */ test_print_int_eight("%-.1d, %-.1d, %-.1d, %-.1d, %-.1d, %-.1d, %-.1d, %-.1d", 0, 5, -1, -10, 100, -1862, INT_MIN, INT_MAX);
	/* 219 */ test_print_int_eight("%-.5d, %-.5d, %-.5d, %-.5d, %-.5d, %-.5d, %-.5d, %-.5d", 0, 5, -1, -10, 100, -1862, INT_MIN, INT_MAX);
	/* 220 */ test_print_int_eight("%-.10d, %-.10d, %-.10d, %-.10d, %-.10d, %-.10d, %-.10d, %-.10d", 0, 5, -1, -10, 100, -1862, INT_MIN, INT_MAX);
	/* 221 */ test_print_int_eight("%-.100d, %-.100d, %-.100d, %-.100d, %-.100d, %-.100d, %-.100d, %-.100d", 0, 5, -1, -10, 100, -1862, INT_MIN, INT_MAX);
	/* 222 */ test_print_int_eight("%-1.d, %-1.d, %-1.d, %-1.d, %-1.d, %-1.d, %-1.d, %-1.d", 0, 5, -1, -10, 100, -1862, INT_MIN, INT_MAX);
	/* 223 */ test_print_int_eight("%-1.0d, %-1.0d, %-1.0d, %-1.0d, %-1.0d, %-1.0d, %-1.0d, %-1.0d", 0, 5, -1, -10, 100, -1862, INT_MIN, INT_MAX);
	/* 224 */ test_print_int_eight("%-1.1d, %-1.1d, %-1.1d, %-1.1d, %-1.1d, %-1.1d, %-1.1d, %-1.1d", 0, 5, -1, -10, 100, -1862, INT_MIN, INT_MAX);
	/* 225 */ test_print_int_eight("%-1.5d, %-1.5d, %-1.5d, %-1.5d, %-1.5d, %-1.5d, %-1.5d, %-1.5d", 0, 5, -1, -10, 100, -1862, INT_MIN, INT_MAX);
	/* 226 */ test_print_int_eight("%-1.10d, %-1.10d, %-1.10d, %-1.10d, %-1.10d, %-1.10d, %-1.10d, %-1.10d", 0, 5, -1, -10, 100, -1862, INT_MIN, INT_MAX);
	/* 227 */ test_print_int_eight("%-1.100d, %-1.100d, %-1.100d, %-1.100d, %-1.100d, %-1.100d, %-1.100d, %-1.100d", 0, 5, -1, -10, 100, -1862, INT_MIN, INT_MAX);
	/* 228 */ test_print_int_eight("%-5.d, %-5.d, %-5.d, %-5.d, %-5.d, %-5.d, %-5.d, %-5.d", 0, 5, -1, -10, 100, -1862, INT_MIN, INT_MAX);
	/* 229 */ test_print_int_eight("%-5.0d, %-5.0d, %-5.0d, %-5.0d, %-5.0d, %-5.0d, %-5.0d, %-5.0d", 0, 5, -1, -10, 100, -1862, INT_MIN, INT_MAX);
	/* 230 */ test_print_int_eight("%-5.1d, %-5.1d, %-5.1d, %-5.1d, %-5.1d, %-5.1d, %-5.1d, %-5.1d", 0, 5, -1, -10, 100, -1862, INT_MIN, INT_MAX);
	/* 231 */ test_print_int_eight("%-5.5d, %-5.5d, %-5.5d, %-5.5d, %-5.5d, %-5.5d, %-5.5d, %-5.5d", 0, 5, -1, -10, 100, -1862, INT_MIN, INT_MAX);
	/* 232 */ test_print_int_eight("%-5.10d, %-5.10d, %-5.10d, %-5.10d, %-5.10d, %-5.10d, %-5.10d, %-5.10d", 0, 5, -1, -10, 100, -1862, INT_MIN, INT_MAX);
	/* 233 */ test_print_int_eight("%-5.100d, %-5.100d, %-5.100d, %-5.100d, %-5.100d, %-5.100d, %-5.100d, %-5.100d", 0, 5, -1, -10, 100, -1862, INT_MIN, INT_MAX);
	/* 234 */ test_print_int_eight("%-10.d, %-10.d, %-10.d, %-10.d, %-10.d, %-10.d, %-10.d, %-10.d", 0, 5, -1, -10, 100, -1862, INT_MIN, INT_MAX);
	/* 235 */ test_print_int_eight("%-10.0d, %-10.0d, %-10.0d, %-10.0d, %-10.0d, %-10.0d, %-10.0d, %-10.0d", 0, 5, -1, -10, 100, -1862, INT_MIN, INT_MAX);
	/* 236 */ test_print_int_eight("%-10.1d, %-10.1d, %-10.1d, %-10.1d, %-10.1d, %-10.1d, %-10.1d, %-10.1d", 0, 5, -1, -10, 100, -1862, INT_MIN, INT_MAX);
	/* 237 */ test_print_int_eight("%-10.5d, %-10.5d, %-10.5d, %-10.5d, %-10.5d, %-10.5d, %-10.5d, %-10.5d", 0, 5, -1, -10, 100, -1862, INT_MIN, INT_MAX);
	/* 238 */ test_print_int_eight("%-10.10d, %-10.10d, %-10.10d, %-10.10d, %-10.10d, %-10.10d, %-10.10d, %-10.10d", 0, 5, -1, -10, 100, -1862, INT_MIN, INT_MAX);
	/* 239 */ test_print_int_eight("%-10.100d, %-10.100d, %-10.100d, %-10.100d, %-10.100d, %-10.100d, %-10.100d, %-10.100d", 0, 5, -1, -10, 100, -1862, INT_MIN, INT_MAX);
	/* 240 */ test_print_int_eight("%-100.d, %-100.d, %-100.d, %-100.d, %-100.d, %-100.d, %-100.d, %-100.d", 0, 5, -1, -10, 100, -1862, INT_MIN, INT_MAX);
	/* 241 */ test_print_int_eight("%-100.0d, %-100.0d, %-100.0d, %-100.0d, %-100.0d, %-100.0d, %-100.0d, %-100.0d", 0, 5, -1, -10, 100, -1862, INT_MIN, INT_MAX);
	/* 242 */ test_print_int_eight("%-100.1d, %-100.1d, %-100.1d, %-100.1d, %-100.1d, %-100.1d, %-100.1d, %-100.1d", 0, 5, -1, -10, 100, -1862, INT_MIN, INT_MAX);
	/* 243 */ test_print_int_eight("%-100.5d, %-100.5d, %-100.5d, %-100.5d, %-100.5d, %-100.5d, %-100.5d, %-100.5d", 0, 5, -1, -10, 100, -1862, INT_MIN, INT_MAX);
	/* 244 */ test_print_int_eight("%-100.10d, %-100.10d, %-100.10d, %-100.10d, %-100.10d, %-100.10d, %-100.10d, %-100.10d", 0, 5, -1, -10, 100, -1862, INT_MIN, INT_MAX);
	/* 245 */ test_print_int_eight("%-100.100d, %-100.100d, %-100.100d, %-100.100d, %-100.100d, %-100.100d, %-100.100d, %-100.100d", 0, 5, -1, -10, 100, -1862, INT_MIN, INT_MAX);
	/* 246 */ test_print_int_eight("%-+d, %-+d, %-+d, %-+d, %-+d, %-+d, %-+d, %-+d", 0, 5, -1, -10, 100, -1862, INT_MIN, INT_MAX);
	/* 247 */ test_print_int_eight("%-+1d, %-+1d, %-+1d, %-+1d, %-+1d, %-+1d, %-+1d, %-+1d", 0, 5, -1, -10, 100, -1862, INT_MIN, INT_MAX);
	/* 248 */ test_print_int_eight("%-+5d, %-+5d, %-+5d, %-+5d, %-+5d, %-+5d, %-+5d, %-+5d", 0, 5, -1, -10, 100, -1862, INT_MIN, INT_MAX);
	/* 249 */ test_print_int_eight("%-+10d, %-+10d, %-+10d, %-+10d, %-+10d, %-+10d, %-+10d, %-+10d", 0, 5, -1, -10, 100, -1862, INT_MIN, INT_MAX);
	/* 250 */ test_print_int_eight("%-+100d, %-+100d, %-+100d, %-+100d, %-+100d, %-+100d, %-+100d, %-+100d", 0, 5, -1, -10, 100, -1862, INT_MIN, INT_MAX);
	/* 251 */ test_print_int_eight("%-+.d, %-+.d, %-+.d, %-+.d, %-+.d, %-+.d, %-+.d, %-+.d", 0, 5, -1, -10, 100, -1862, INT_MIN, INT_MAX);
	/* 252 */ test_print_int_eight("%-+.0d, %-+.0d, %-+.0d, %-+.0d, %-+.0d, %-+.0d, %-+.0d, %-+.0d", 0, 5, -1, -10, 100, -1862, INT_MIN, INT_MAX);
	/* 253 */ test_print_int_eight("%-+.1d, %-+.1d, %-+.1d, %-+.1d, %-+.1d, %-+.1d, %-+.1d, %-+.1d", 0, 5, -1, -10, 100, -1862, INT_MIN, INT_MAX);
	/* 254 */ test_print_int_eight("%-+.5d, %-+.5d, %-+.5d, %-+.5d, %-+.5d, %-+.5d, %-+.5d, %-+.5d", 0, 5, -1, -10, 100, -1862, INT_MIN, INT_MAX);
	/* 255 */ test_print_int_eight("%-+.10d, %-+.10d, %-+.10d, %-+.10d, %-+.10d, %-+.10d, %-+.10d, %-+.10d", 0, 5, -1, -10, 100, -1862, INT_MIN, INT_MAX);
	/* 256 */ test_print_int_eight("%-+.100d, %-+.100d, %-+.100d, %-+.100d, %-+.100d, %-+.100d, %-+.100d, %-+.100d", 0, 5, -1, -10, 100, -1862, INT_MIN, INT_MAX);
	/* 257 */ test_print_int_eight("%-+1.d, %-+1.d, %-+1.d, %-+1.d, %-+1.d, %-+1.d, %-+1.d, %-+1.d", 0, 5, -1, -10, 100, -1862, INT_MIN, INT_MAX);
	/* 258 */ test_print_int_eight("%-+1.0d, %-+1.0d, %-+1.0d, %-+1.0d, %-+1.0d, %-+1.0d, %-+1.0d, %-+1.0d", 0, 5, -1, -10, 100, -1862, INT_MIN, INT_MAX);
	/* 259 */ test_print_int_eight("%-+1.1d, %-+1.1d, %-+1.1d, %-+1.1d, %-+1.1d, %-+1.1d, %-+1.1d, %-+1.1d", 0, 5, -1, -10, 100, -1862, INT_MIN, INT_MAX);
	/* 260 */ test_print_int_eight("%-+1.5d, %-+1.5d, %-+1.5d, %-+1.5d, %-+1.5d, %-+1.5d, %-+1.5d, %-+1.5d", 0, 5, -1, -10, 100, -1862, INT_MIN, INT_MAX);
	/* 261 */ test_print_int_eight("%-+1.10d, %-+1.10d, %-+1.10d, %-+1.10d, %-+1.10d, %-+1.10d, %-+1.10d, %-+1.10d", 0, 5, -1, -10, 100, -1862, INT_MIN, INT_MAX);
	/* 262 */ test_print_int_eight("%-+1.100d, %-+1.100d, %-+1.100d, %-+1.100d, %-+1.100d, %-+1.100d, %-+1.100d, %-+1.100d", 0, 5, -1, -10, 100, -1862, INT_MIN, INT_MAX);
	/* 263 */ test_print_int_eight("%-+5.d, %-+5.d, %-+5.d, %-+5.d, %-+5.d, %-+5.d, %-+5.d, %-+5.d", 0, 5, -1, -10, 100, -1862, INT_MIN, INT_MAX);
	/* 264 */ test_print_int_eight("%-+5.0d, %-+5.0d, %-+5.0d, %-+5.0d, %-+5.0d, %-+5.0d, %-+5.0d, %-+5.0d", 0, 5, -1, -10, 100, -1862, INT_MIN, INT_MAX);
	/* 265 */ test_print_int_eight("%-+5.1d, %-+5.1d, %-+5.1d, %-+5.1d, %-+5.1d, %-+5.1d, %-+5.1d, %-+5.1d", 0, 5, -1, -10, 100, -1862, INT_MIN, INT_MAX);
	/* 266 */ test_print_int_eight("%-+5.5d, %-+5.5d, %-+5.5d, %-+5.5d, %-+5.5d, %-+5.5d, %-+5.5d, %-+5.5d", 0, 5, -1, -10, 100, -1862, INT_MIN, INT_MAX);
	/* 267 */ test_print_int_eight("%-+5.10d, %-+5.10d, %-+5.10d, %-+5.10d, %-+5.10d, %-+5.10d, %-+5.10d, %-+5.10d", 0, 5, -1, -10, 100, -1862, INT_MIN, INT_MAX);
	/* 268 */ test_print_int_eight("%-+5.100d, %-+5.100d, %-+5.100d, %-+5.100d, %-+5.100d, %-+5.100d, %-+5.100d, %-+5.100d", 0, 5, -1, -10, 100, -1862, INT_MIN, INT_MAX);
	/* 269 */ test_print_int_eight("%-+10.d, %-+10.d, %-+10.d, %-+10.d, %-+10.d, %-+10.d, %-+10.d, %-+10.d", 0, 5, -1, -10, 100, -1862, INT_MIN, INT_MAX);
	/* 270 */ test_print_int_eight("%-+10.0d, %-+10.0d, %-+10.0d, %-+10.0d, %-+10.0d, %-+10.0d, %-+10.0d, %-+10.0d", 0, 5, -1, -10, 100, -1862, INT_MIN, INT_MAX);
	/* 271 */ test_print_int_eight("%-+10.1d, %-+10.1d, %-+10.1d, %-+10.1d, %-+10.1d, %-+10.1d, %-+10.1d, %-+10.1d", 0, 5, -1, -10, 100, -1862, INT_MIN, INT_MAX);
	/* 272 */ test_print_int_eight("%-+10.5d, %-+10.5d, %-+10.5d, %-+10.5d, %-+10.5d, %-+10.5d, %-+10.5d, %-+10.5d", 0, 5, -1, -10, 100, -1862, INT_MIN, INT_MAX);
	/* 273 */ test_print_int_eight("%-+10.10d, %-+10.10d, %-+10.10d, %-+10.10d, %-+10.10d, %-+10.10d, %-+10.10d, %-+10.10d", 0, 5, -1, -10, 100, -1862, INT_MIN, INT_MAX);
	/* 274 */ test_print_int_eight("%-+10.100d, %-+10.100d, %-+10.100d, %-+10.100d, %-+10.100d, %-+10.100d, %-+10.100d, %-+10.100d", 0, 5, -1, -10, 100, -1862, INT_MIN, INT_MAX);
	/* 275 */ test_print_int_eight("%-+100.d, %-+100.d, %-+100.d, %-+100.d, %-+100.d, %-+100.d, %-+100.d, %-+100.d", 0, 5, -1, -10, 100, -1862, INT_MIN, INT_MAX);
	/* 276 */ test_print_int_eight("%-+100.0d, %-+100.0d, %-+100.0d, %-+100.0d, %-+100.0d, %-+100.0d, %-+100.0d, %-+100.0d", 0, 5, -1, -10, 100, -1862, INT_MIN, INT_MAX);
	/* 277 */ test_print_int_eight("%-+100.1d, %-+100.1d, %-+100.1d, %-+100.1d, %-+100.1d, %-+100.1d, %-+100.1d, %-+100.1d", 0, 5, -1, -10, 100, -1862, INT_MIN, INT_MAX);
	/* 278 */ test_print_int_eight("%-+100.5d, %-+100.5d, %-+100.5d, %-+100.5d, %-+100.5d, %-+100.5d, %-+100.5d, %-+100.5d", 0, 5, -1, -10, 100, -1862, INT_MIN, INT_MAX);
	/* 279 */ test_print_int_eight("%-+100.10d, %-+100.10d, %-+100.10d, %-+100.10d, %-+100.10d, %-+100.10d, %-+100.10d, %-+100.10d", 0, 5, -1, -10, 100, -1862, INT_MIN, INT_MAX);
	/* 280 */ test_print_int_eight("%-+100.100d, %-+100.100d, %-+100.100d, %-+100.100d, %-+100.100d, %-+100.100d, %-+100.100d, %-+100.100d", 0, 5, -1, -10, 100, -1862, INT_MIN, INT_MAX);
	/* 281 */ test_print_int_eight("%- d, %- d, %- d, %- d, %- d, %- d, %- d, %- d", 0, 5, -1, -10, 100, -1862, INT_MIN, INT_MAX);
	/* 282 */ test_print_int_eight("%- 1d, %- 1d, %- 1d, %- 1d, %- 1d, %- 1d, %- 1d, %- 1d", 0, 5, -1, -10, 100, -1862, INT_MIN, INT_MAX);
	/* 283 */ test_print_int_eight("%- 5d, %- 5d, %- 5d, %- 5d, %- 5d, %- 5d, %- 5d, %- 5d", 0, 5, -1, -10, 100, -1862, INT_MIN, INT_MAX);
	/* 284 */ test_print_int_eight("%- 10d, %- 10d, %- 10d, %- 10d, %- 10d, %- 10d, %- 10d, %- 10d", 0, 5, -1, -10, 100, -1862, INT_MIN, INT_MAX);
	/* 285 */ test_print_int_eight("%- 100d, %- 100d, %- 100d, %- 100d, %- 100d, %- 100d, %- 100d, %- 100d", 0, 5, -1, -10, 100, -1862, INT_MIN, INT_MAX);
	/* 286 */ test_print_int_eight("%- .d, %- .d, %- .d, %- .d, %- .d, %- .d, %- .d, %- .d", 0, 5, -1, -10, 100, -1862, INT_MIN, INT_MAX);
	/* 287 */ test_print_int_eight("%- .0d, %- .0d, %- .0d, %- .0d, %- .0d, %- .0d, %- .0d, %- .0d", 0, 5, -1, -10, 100, -1862, INT_MIN, INT_MAX);
	/* 288 */ test_print_int_eight("%- .1d, %- .1d, %- .1d, %- .1d, %- .1d, %- .1d, %- .1d, %- .1d", 0, 5, -1, -10, 100, -1862, INT_MIN, INT_MAX);
	/* 289 */ test_print_int_eight("%- .5d, %- .5d, %- .5d, %- .5d, %- .5d, %- .5d, %- .5d, %- .5d", 0, 5, -1, -10, 100, -1862, INT_MIN, INT_MAX);
	/* 290 */ test_print_int_eight("%- .10d, %- .10d, %- .10d, %- .10d, %- .10d, %- .10d, %- .10d, %- .10d", 0, 5, -1, -10, 100, -1862, INT_MIN, INT_MAX);
	/* 291 */ test_print_int_eight("%- .100d, %- .100d, %- .100d, %- .100d, %- .100d, %- .100d, %- .100d, %- .100d", 0, 5, -1, -10, 100, -1862, INT_MIN, INT_MAX);
	/* 292 */ test_print_int_eight("%- 1.d, %- 1.d, %- 1.d, %- 1.d, %- 1.d, %- 1.d, %- 1.d, %- 1.d", 0, 5, -1, -10, 100, -1862, INT_MIN, INT_MAX);
	/* 293 */ test_print_int_eight("%- 1.0d, %- 1.0d, %- 1.0d, %- 1.0d, %- 1.0d, %- 1.0d, %- 1.0d, %- 1.0d", 0, 5, -1, -10, 100, -1862, INT_MIN, INT_MAX);
	/* 294 */ test_print_int_eight("%- 1.1d, %- 1.1d, %- 1.1d, %- 1.1d, %- 1.1d, %- 1.1d, %- 1.1d, %- 1.1d", 0, 5, -1, -10, 100, -1862, INT_MIN, INT_MAX);
	/* 295 */ test_print_int_eight("%- 1.5d, %- 1.5d, %- 1.5d, %- 1.5d, %- 1.5d, %- 1.5d, %- 1.5d, %- 1.5d", 0, 5, -1, -10, 100, -1862, INT_MIN, INT_MAX);
	/* 296 */ test_print_int_eight("%- 1.10d, %- 1.10d, %- 1.10d, %- 1.10d, %- 1.10d, %- 1.10d, %- 1.10d, %- 1.10d", 0, 5, -1, -10, 100, -1862, INT_MIN, INT_MAX);
	/* 297 */ test_print_int_eight("%- 1.100d, %- 1.100d, %- 1.100d, %- 1.100d, %- 1.100d, %- 1.100d, %- 1.100d, %- 1.100d", 0, 5, -1, -10, 100, -1862, INT_MIN, INT_MAX);
	/* 298 */ test_print_int_eight("%- 5.d, %- 5.d, %- 5.d, %- 5.d, %- 5.d, %- 5.d, %- 5.d, %- 5.d", 0, 5, -1, -10, 100, -1862, INT_MIN, INT_MAX);
	/* 299 */ test_print_int_eight("%- 5.0d, %- 5.0d, %- 5.0d, %- 5.0d, %- 5.0d, %- 5.0d, %- 5.0d, %- 5.0d", 0, 5, -1, -10, 100, -1862, INT_MIN, INT_MAX);
	/* 300 */ test_print_int_eight("%- 5.1d, %- 5.1d, %- 5.1d, %- 5.1d, %- 5.1d, %- 5.1d, %- 5.1d, %- 5.1d", 0, 5, -1, -10, 100, -1862, INT_MIN, INT_MAX);
	/* 301 */ test_print_int_eight("%- 5.5d, %- 5.5d, %- 5.5d, %- 5.5d, %- 5.5d, %- 5.5d, %- 5.5d, %- 5.5d", 0, 5, -1, -10, 100, -1862, INT_MIN, INT_MAX);
	/* 302 */ test_print_int_eight("%- 5.10d, %- 5.10d, %- 5.10d, %- 5.10d, %- 5.10d, %- 5.10d, %- 5.10d, %- 5.10d", 0, 5, -1, -10, 100, -1862, INT_MIN, INT_MAX);
	/* 303 */ test_print_int_eight("%- 5.100d, %- 5.100d, %- 5.100d, %- 5.100d, %- 5.100d, %- 5.100d, %- 5.100d, %- 5.100d", 0, 5, -1, -10, 100, -1862, INT_MIN, INT_MAX);
	/* 304 */ test_print_int_eight("%- 10.d, %- 10.d, %- 10.d, %- 10.d, %- 10.d, %- 10.d, %- 10.d, %- 10.d", 0, 5, -1, -10, 100, -1862, INT_MIN, INT_MAX);
	/* 305 */ test_print_int_eight("%- 10.0d, %- 10.0d, %- 10.0d, %- 10.0d, %- 10.0d, %- 10.0d, %- 10.0d, %- 10.0d", 0, 5, -1, -10, 100, -1862, INT_MIN, INT_MAX);
	/* 306 */ test_print_int_eight("%- 10.1d, %- 10.1d, %- 10.1d, %- 10.1d, %- 10.1d, %- 10.1d, %- 10.1d, %- 10.1d", 0, 5, -1, -10, 100, -1862, INT_MIN, INT_MAX);
	/* 307 */ test_print_int_eight("%- 10.5d, %- 10.5d, %- 10.5d, %- 10.5d, %- 10.5d, %- 10.5d, %- 10.5d, %- 10.5d", 0, 5, -1, -10, 100, -1862, INT_MIN, INT_MAX);
	/* 308 */ test_print_int_eight("%- 10.10d, %- 10.10d, %- 10.10d, %- 10.10d, %- 10.10d, %- 10.10d, %- 10.10d, %- 10.10d", 0, 5, -1, -10, 100, -1862, INT_MIN, INT_MAX);
	/* 309 */ test_print_int_eight("%- 10.100d, %- 10.100d, %- 10.100d, %- 10.100d, %- 10.100d, %- 10.100d, %- 10.100d, %- 10.100d", 0, 5, -1, -10, 100, -1862, INT_MIN, INT_MAX);
	/* 310 */ test_print_int_eight("%- 100.d, %- 100.d, %- 100.d, %- 100.d, %- 100.d, %- 100.d, %- 100.d, %- 100.d", 0, 5, -1, -10, 100, -1862, INT_MIN, INT_MAX);
	/* 311 */ test_print_int_eight("%- 100.0d, %- 100.0d, %- 100.0d, %- 100.0d, %- 100.0d, %- 100.0d, %- 100.0d, %- 100.0d", 0, 5, -1, -10, 100, -1862, INT_MIN, INT_MAX);
	/* 312 */ test_print_int_eight("%- 100.1d, %- 100.1d, %- 100.1d, %- 100.1d, %- 100.1d, %- 100.1d, %- 100.1d, %- 100.1d", 0, 5, -1, -10, 100, -1862, INT_MIN, INT_MAX);
	/* 313 */ test_print_int_eight("%- 100.5d, %- 100.5d, %- 100.5d, %- 100.5d, %- 100.5d, %- 100.5d, %- 100.5d, %- 100.5d", 0, 5, -1, -10, 100, -1862, INT_MIN, INT_MAX);
	/* 314 */ test_print_int_eight("%- 100.10d, %- 100.10d, %- 100.10d, %- 100.10d, %- 100.10d, %- 100.10d, %- 100.10d, %- 100.10d", 0, 5, -1, -10, 100, -1862, INT_MIN, INT_MAX);
	/* 315 */ test_print_int_eight("%- 100.100d, %- 100.100d, %- 100.100d, %- 100.100d, %- 100.100d, %- 100.100d, %- 100.100d, %- 100.100d", 0, 5, -1, -10, 100, -1862, INT_MIN, INT_MAX);
}

void test_i() {
	g_current_test_id = 'i';
	/* 1 */ test_print_int_eight("%i, %i, %i, %i, %i, %i, %i, %i", 0, 5, -1, -10, 100, -1862, INT_MIN, INT_MAX);
	/* 2 */ test_print_int_eight("%1i, %1i, %1i, %1i, %1i, %1i, %1i, %1i", 0, 5, -1, -10, 100, -1862, INT_MIN, INT_MAX);
	/* 3 */ test_print_int_eight("%5i, %5i, %5i, %5i, %5i, %5i, %5i, %5i", 0, 5, -1, -10, 100, -1862, INT_MIN, INT_MAX);
	/* 4 */ test_print_int_eight("%10i, %10i, %10i, %10i, %10i, %10i, %10i, %10i", 0, 5, -1, -10, 100, -1862, INT_MIN, INT_MAX);
	/* 5 */ test_print_int_eight("%100i, %100i, %100i, %100i, %100i, %100i, %100i, %100i", 0, 5, -1, -10, 100, -1862, INT_MIN, INT_MAX);
	/* 6 */ test_print_int_eight("%.i, %.i, %.i, %.i, %.i, %.i, %.i, %.i", 0, 5, -1, -10, 100, -1862, INT_MIN, INT_MAX);
	/* 7 */ test_print_int_eight("%.0i, %.0i, %.0i, %.0i, %.0i, %.0i, %.0i, %.0i", 0, 5, -1, -10, 100, -1862, INT_MIN, INT_MAX);
	/* 8 */ test_print_int_eight("%.1i, %.1i, %.1i, %.1i, %.1i, %.1i, %.1i, %.1i", 0, 5, -1, -10, 100, -1862, INT_MIN, INT_MAX);
	/* 9 */ test_print_int_eight("%.5i, %.5i, %.5i, %.5i, %.5i, %.5i, %.5i, %.5i", 0, 5, -1, -10, 100, -1862, INT_MIN, INT_MAX);
	/* 10 */ test_print_int_eight("%.10i, %.10i, %.10i, %.10i, %.10i, %.10i, %.10i, %.10i", 0, 5, -1, -10, 100, -1862, INT_MIN, INT_MAX);
	/* 11 */ test_print_int_eight("%.100i, %.100i, %.100i, %.100i, %.100i, %.100i, %.100i, %.100i", 0, 5, -1, -10, 100, -1862, INT_MIN, INT_MAX);
	/* 12 */ test_print_int_eight("%1.i, %1.i, %1.i, %1.i, %1.i, %1.i, %1.i, %1.i", 0, 5, -1, -10, 100, -1862, INT_MIN, INT_MAX);
	/* 13 */ test_print_int_eight("%1.0i, %1.0i, %1.0i, %1.0i, %1.0i, %1.0i, %1.0i, %1.0i", 0, 5, -1, -10, 100, -1862, INT_MIN, INT_MAX);
	/* 14 */ test_print_int_eight("%1.1i, %1.1i, %1.1i, %1.1i, %1.1i, %1.1i, %1.1i, %1.1i", 0, 5, -1, -10, 100, -1862, INT_MIN, INT_MAX);
	/* 15 */ test_print_int_eight("%1.5i, %1.5i, %1.5i, %1.5i, %1.5i, %1.5i, %1.5i, %1.5i", 0, 5, -1, -10, 100, -1862, INT_MIN, INT_MAX);
	/* 16 */ test_print_int_eight("%1.10i, %1.10i, %1.10i, %1.10i, %1.10i, %1.10i, %1.10i, %1.10i", 0, 5, -1, -10, 100, -1862, INT_MIN, INT_MAX);
	/* 17 */ test_print_int_eight("%1.100i, %1.100i, %1.100i, %1.100i, %1.100i, %1.100i, %1.100i, %1.100i", 0, 5, -1, -10, 100, -1862, INT_MIN, INT_MAX);
	/* 18 */ test_print_int_eight("%5.i, %5.i, %5.i, %5.i, %5.i, %5.i, %5.i, %5.i", 0, 5, -1, -10, 100, -1862, INT_MIN, INT_MAX);
	/* 19 */ test_print_int_eight("%5.0i, %5.0i, %5.0i, %5.0i, %5.0i, %5.0i, %5.0i, %5.0i", 0, 5, -1, -10, 100, -1862, INT_MIN, INT_MAX);
	/* 20 */ test_print_int_eight("%5.1i, %5.1i, %5.1i, %5.1i, %5.1i, %5.1i, %5.1i, %5.1i", 0, 5, -1, -10, 100, -1862, INT_MIN, INT_MAX);
	/* 21 */ test_print_int_eight("%5.5i, %5.5i, %5.5i, %5.5i, %5.5i, %5.5i, %5.5i, %5.5i", 0, 5, -1, -10, 100, -1862, INT_MIN, INT_MAX);
	/* 22 */ test_print_int_eight("%5.10i, %5.10i, %5.10i, %5.10i, %5.10i, %5.10i, %5.10i, %5.10i", 0, 5, -1, -10, 100, -1862, INT_MIN, INT_MAX);
	/* 23 */ test_print_int_eight("%5.100i, %5.100i, %5.100i, %5.100i, %5.100i, %5.100i, %5.100i, %5.100i", 0, 5, -1, -10, 100, -1862, INT_MIN, INT_MAX);
	/* 24 */ test_print_int_eight("%10.i, %10.i, %10.i, %10.i, %10.i, %10.i, %10.i, %10.i", 0, 5, -1, -10, 100, -1862, INT_MIN, INT_MAX);
	/* 25 */ test_print_int_eight("%10.0i, %10.0i, %10.0i, %10.0i, %10.0i, %10.0i, %10.0i, %10.0i", 0, 5, -1, -10, 100, -1862, INT_MIN, INT_MAX);
	/* 26 */ test_print_int_eight("%10.1i, %10.1i, %10.1i, %10.1i, %10.1i, %10.1i, %10.1i, %10.1i", 0, 5, -1, -10, 100, -1862, INT_MIN, INT_MAX);
	/* 27 */ test_print_int_eight("%10.5i, %10.5i, %10.5i, %10.5i, %10.5i, %10.5i, %10.5i, %10.5i", 0, 5, -1, -10, 100, -1862, INT_MIN, INT_MAX);
	/* 28 */ test_print_int_eight("%10.10i, %10.10i, %10.10i, %10.10i, %10.10i, %10.10i, %10.10i, %10.10i", 0, 5, -1, -10, 100, -1862, INT_MIN, INT_MAX);
	/* 29 */ test_print_int_eight("%10.100i, %10.100i, %10.100i, %10.100i, %10.100i, %10.100i, %10.100i, %10.100i", 0, 5, -1, -10, 100, -1862, INT_MIN, INT_MAX);
	/* 30 */ test_print_int_eight("%100.i, %100.i, %100.i, %100.i, %100.i, %100.i, %100.i, %100.i", 0, 5, -1, -10, 100, -1862, INT_MIN, INT_MAX);
	/* 31 */ test_print_int_eight("%100.0i, %100.0i, %100.0i, %100.0i, %100.0i, %100.0i, %100.0i, %100.0i", 0, 5, -1, -10, 100, -1862, INT_MIN, INT_MAX);
	/* 32 */ test_print_int_eight("%100.1i, %100.1i, %100.1i, %100.1i, %100.1i, %100.1i, %100.1i, %100.1i", 0, 5, -1, -10, 100, -1862, INT_MIN, INT_MAX);
	/* 33 */ test_print_int_eight("%100.5i, %100.5i, %100.5i, %100.5i, %100.5i, %100.5i, %100.5i, %100.5i", 0, 5, -1, -10, 100, -1862, INT_MIN, INT_MAX);
	/* 34 */ test_print_int_eight("%100.10i, %100.10i, %100.10i, %100.10i, %100.10i, %100.10i, %100.10i, %100.10i", 0, 5, -1, -10, 100, -1862, INT_MIN, INT_MAX);
	/* 35 */ test_print_int_eight("%100.100i, %100.100i, %100.100i, %100.100i, %100.100i, %100.100i, %100.100i, %100.100i", 0, 5, -1, -10, 100, -1862, INT_MIN, INT_MAX);
	/* 36 */ test_print_int_eight("%+i, %+i, %+i, %+i, %+i, %+i, %+i, %+i", 0, 5, -1, -10, 100, -1862, INT_MIN, INT_MAX);
	/* 37 */ test_print_int_eight("%+1i, %+1i, %+1i, %+1i, %+1i, %+1i, %+1i, %+1i", 0, 5, -1, -10, 100, -1862, INT_MIN, INT_MAX);
	/* 38 */ test_print_int_eight("%+5i, %+5i, %+5i, %+5i, %+5i, %+5i, %+5i, %+5i", 0, 5, -1, -10, 100, -1862, INT_MIN, INT_MAX);
	/* 39 */ test_print_int_eight("%+10i, %+10i, %+10i, %+10i, %+10i, %+10i, %+10i, %+10i", 0, 5, -1, -10, 100, -1862, INT_MIN, INT_MAX);
	/* 40 */ test_print_int_eight("%+100i, %+100i, %+100i, %+100i, %+100i, %+100i, %+100i, %+100i", 0, 5, -1, -10, 100, -1862, INT_MIN, INT_MAX);
	/* 41 */ test_print_int_eight("%+.i, %+.i, %+.i, %+.i, %+.i, %+.i, %+.i, %+.i", 0, 5, -1, -10, 100, -1862, INT_MIN, INT_MAX);
	/* 42 */ test_print_int_eight("%+.0i, %+.0i, %+.0i, %+.0i, %+.0i, %+.0i, %+.0i, %+.0i", 0, 5, -1, -10, 100, -1862, INT_MIN, INT_MAX);
	/* 43 */ test_print_int_eight("%+.1i, %+.1i, %+.1i, %+.1i, %+.1i, %+.1i, %+.1i, %+.1i", 0, 5, -1, -10, 100, -1862, INT_MIN, INT_MAX);
	/* 44 */ test_print_int_eight("%+.5i, %+.5i, %+.5i, %+.5i, %+.5i, %+.5i, %+.5i, %+.5i", 0, 5, -1, -10, 100, -1862, INT_MIN, INT_MAX);
	/* 45 */ test_print_int_eight("%+.10i, %+.10i, %+.10i, %+.10i, %+.10i, %+.10i, %+.10i, %+.10i", 0, 5, -1, -10, 100, -1862, INT_MIN, INT_MAX);
	/* 46 */ test_print_int_eight("%+.100i, %+.100i, %+.100i, %+.100i, %+.100i, %+.100i, %+.100i, %+.100i", 0, 5, -1, -10, 100, -1862, INT_MIN, INT_MAX);
	/* 47 */ test_print_int_eight("%+1.i, %+1.i, %+1.i, %+1.i, %+1.i, %+1.i, %+1.i, %+1.i", 0, 5, -1, -10, 100, -1862, INT_MIN, INT_MAX);
	/* 48 */ test_print_int_eight("%+1.0i, %+1.0i, %+1.0i, %+1.0i, %+1.0i, %+1.0i, %+1.0i, %+1.0i", 0, 5, -1, -10, 100, -1862, INT_MIN, INT_MAX);
	/* 49 */ test_print_int_eight("%+1.1i, %+1.1i, %+1.1i, %+1.1i, %+1.1i, %+1.1i, %+1.1i, %+1.1i", 0, 5, -1, -10, 100, -1862, INT_MIN, INT_MAX);
	/* 50 */ test_print_int_eight("%+1.5i, %+1.5i, %+1.5i, %+1.5i, %+1.5i, %+1.5i, %+1.5i, %+1.5i", 0, 5, -1, -10, 100, -1862, INT_MIN, INT_MAX);
	/* 51 */ test_print_int_eight("%+1.10i, %+1.10i, %+1.10i, %+1.10i, %+1.10i, %+1.10i, %+1.10i, %+1.10i", 0, 5, -1, -10, 100, -1862, INT_MIN, INT_MAX);
	/* 52 */ test_print_int_eight("%+1.100i, %+1.100i, %+1.100i, %+1.100i, %+1.100i, %+1.100i, %+1.100i, %+1.100i", 0, 5, -1, -10, 100, -1862, INT_MIN, INT_MAX);
	/* 53 */ test_print_int_eight("%+5.i, %+5.i, %+5.i, %+5.i, %+5.i, %+5.i, %+5.i, %+5.i", 0, 5, -1, -10, 100, -1862, INT_MIN, INT_MAX);
	/* 54 */ test_print_int_eight("%+5.0i, %+5.0i, %+5.0i, %+5.0i, %+5.0i, %+5.0i, %+5.0i, %+5.0i", 0, 5, -1, -10, 100, -1862, INT_MIN, INT_MAX);
	/* 55 */ test_print_int_eight("%+5.1i, %+5.1i, %+5.1i, %+5.1i, %+5.1i, %+5.1i, %+5.1i, %+5.1i", 0, 5, -1, -10, 100, -1862, INT_MIN, INT_MAX);
	/* 56 */ test_print_int_eight("%+5.5i, %+5.5i, %+5.5i, %+5.5i, %+5.5i, %+5.5i, %+5.5i, %+5.5i", 0, 5, -1, -10, 100, -1862, INT_MIN, INT_MAX);
	/* 57 */ test_print_int_eight("%+5.10i, %+5.10i, %+5.10i, %+5.10i, %+5.10i, %+5.10i, %+5.10i, %+5.10i", 0, 5, -1, -10, 100, -1862, INT_MIN, INT_MAX);
	/* 58 */ test_print_int_eight("%+5.100i, %+5.100i, %+5.100i, %+5.100i, %+5.100i, %+5.100i, %+5.100i, %+5.100i", 0, 5, -1, -10, 100, -1862, INT_MIN, INT_MAX);
	/* 59 */ test_print_int_eight("%+10.i, %+10.i, %+10.i, %+10.i, %+10.i, %+10.i, %+10.i, %+10.i", 0, 5, -1, -10, 100, -1862, INT_MIN, INT_MAX);
	/* 60 */ test_print_int_eight("%+10.0i, %+10.0i, %+10.0i, %+10.0i, %+10.0i, %+10.0i, %+10.0i, %+10.0i", 0, 5, -1, -10, 100, -1862, INT_MIN, INT_MAX);
	/* 61 */ test_print_int_eight("%+10.1i, %+10.1i, %+10.1i, %+10.1i, %+10.1i, %+10.1i, %+10.1i, %+10.1i", 0, 5, -1, -10, 100, -1862, INT_MIN, INT_MAX);
	/* 62 */ test_print_int_eight("%+10.5i, %+10.5i, %+10.5i, %+10.5i, %+10.5i, %+10.5i, %+10.5i, %+10.5i", 0, 5, -1, -10, 100, -1862, INT_MIN, INT_MAX);
	/* 63 */ test_print_int_eight("%+10.10i, %+10.10i, %+10.10i, %+10.10i, %+10.10i, %+10.10i, %+10.10i, %+10.10i", 0, 5, -1, -10, 100, -1862, INT_MIN, INT_MAX);
	/* 64 */ test_print_int_eight("%+10.100i, %+10.100i, %+10.100i, %+10.100i, %+10.100i, %+10.100i, %+10.100i, %+10.100i", 0, 5, -1, -10, 100, -1862, INT_MIN, INT_MAX);
	/* 65 */ test_print_int_eight("%+100.i, %+100.i, %+100.i, %+100.i, %+100.i, %+100.i, %+100.i, %+100.i", 0, 5, -1, -10, 100, -1862, INT_MIN, INT_MAX);
	/* 66 */ test_print_int_eight("%+100.0i, %+100.0i, %+100.0i, %+100.0i, %+100.0i, %+100.0i, %+100.0i, %+100.0i", 0, 5, -1, -10, 100, -1862, INT_MIN, INT_MAX);
	/* 67 */ test_print_int_eight("%+100.1i, %+100.1i, %+100.1i, %+100.1i, %+100.1i, %+100.1i, %+100.1i, %+100.1i", 0, 5, -1, -10, 100, -1862, INT_MIN, INT_MAX);
	/* 68 */ test_print_int_eight("%+100.5i, %+100.5i, %+100.5i, %+100.5i, %+100.5i, %+100.5i, %+100.5i, %+100.5i", 0, 5, -1, -10, 100, -1862, INT_MIN, INT_MAX);
	/* 69 */ test_print_int_eight("%+100.10i, %+100.10i, %+100.10i, %+100.10i, %+100.10i, %+100.10i, %+100.10i, %+100.10i", 0, 5, -1, -10, 100, -1862, INT_MIN, INT_MAX);
	/* 70 */ test_print_int_eight("%+100.100i, %+100.100i, %+100.100i, %+100.100i, %+100.100i, %+100.100i, %+100.100i, %+100.100i", 0, 5, -1, -10, 100, -1862, INT_MIN, INT_MAX);
	/* 71 */ test_print_int_eight("% i, % i, % i, % i, % i, % i, % i, % i", 0, 5, -1, -10, 100, -1862, INT_MIN, INT_MAX);
	/* 72 */ test_print_int_eight("% 1i, % 1i, % 1i, % 1i, % 1i, % 1i, % 1i, % 1i", 0, 5, -1, -10, 100, -1862, INT_MIN, INT_MAX);
	/* 73 */ test_print_int_eight("% 5i, % 5i, % 5i, % 5i, % 5i, % 5i, % 5i, % 5i", 0, 5, -1, -10, 100, -1862, INT_MIN, INT_MAX);
	/* 74 */ test_print_int_eight("% 10i, % 10i, % 10i, % 10i, % 10i, % 10i, % 10i, % 10i", 0, 5, -1, -10, 100, -1862, INT_MIN, INT_MAX);
	/* 75 */ test_print_int_eight("% 100i, % 100i, % 100i, % 100i, % 100i, % 100i, % 100i, % 100i", 0, 5, -1, -10, 100, -1862, INT_MIN, INT_MAX);
	/* 76 */ test_print_int_eight("% .i, % .i, % .i, % .i, % .i, % .i, % .i, % .i", 0, 5, -1, -10, 100, -1862, INT_MIN, INT_MAX);
	/* 77 */ test_print_int_eight("% .0i, % .0i, % .0i, % .0i, % .0i, % .0i, % .0i, % .0i", 0, 5, -1, -10, 100, -1862, INT_MIN, INT_MAX);
	/* 78 */ test_print_int_eight("% .1i, % .1i, % .1i, % .1i, % .1i, % .1i, % .1i, % .1i", 0, 5, -1, -10, 100, -1862, INT_MIN, INT_MAX);
	/* 79 */ test_print_int_eight("% .5i, % .5i, % .5i, % .5i, % .5i, % .5i, % .5i, % .5i", 0, 5, -1, -10, 100, -1862, INT_MIN, INT_MAX);
	/* 80 */ test_print_int_eight("% .10i, % .10i, % .10i, % .10i, % .10i, % .10i, % .10i, % .10i", 0, 5, -1, -10, 100, -1862, INT_MIN, INT_MAX);
	/* 81 */ test_print_int_eight("% .100i, % .100i, % .100i, % .100i, % .100i, % .100i, % .100i, % .100i", 0, 5, -1, -10, 100, -1862, INT_MIN, INT_MAX);
	/* 82 */ test_print_int_eight("% 1.i, % 1.i, % 1.i, % 1.i, % 1.i, % 1.i, % 1.i, % 1.i", 0, 5, -1, -10, 100, -1862, INT_MIN, INT_MAX);
	/* 83 */ test_print_int_eight("% 1.0i, % 1.0i, % 1.0i, % 1.0i, % 1.0i, % 1.0i, % 1.0i, % 1.0i", 0, 5, -1, -10, 100, -1862, INT_MIN, INT_MAX);
	/* 84 */ test_print_int_eight("% 1.1i, % 1.1i, % 1.1i, % 1.1i, % 1.1i, % 1.1i, % 1.1i, % 1.1i", 0, 5, -1, -10, 100, -1862, INT_MIN, INT_MAX);
	/* 85 */ test_print_int_eight("% 1.5i, % 1.5i, % 1.5i, % 1.5i, % 1.5i, % 1.5i, % 1.5i, % 1.5i", 0, 5, -1, -10, 100, -1862, INT_MIN, INT_MAX);
	/* 86 */ test_print_int_eight("% 1.10i, % 1.10i, % 1.10i, % 1.10i, % 1.10i, % 1.10i, % 1.10i, % 1.10i", 0, 5, -1, -10, 100, -1862, INT_MIN, INT_MAX);
	/* 87 */ test_print_int_eight("% 1.100i, % 1.100i, % 1.100i, % 1.100i, % 1.100i, % 1.100i, % 1.100i, % 1.100i", 0, 5, -1, -10, 100, -1862, INT_MIN, INT_MAX);
	/* 88 */ test_print_int_eight("% 5.i, % 5.i, % 5.i, % 5.i, % 5.i, % 5.i, % 5.i, % 5.i", 0, 5, -1, -10, 100, -1862, INT_MIN, INT_MAX);
	/* 89 */ test_print_int_eight("% 5.0i, % 5.0i, % 5.0i, % 5.0i, % 5.0i, % 5.0i, % 5.0i, % 5.0i", 0, 5, -1, -10, 100, -1862, INT_MIN, INT_MAX);
	/* 90 */ test_print_int_eight("% 5.1i, % 5.1i, % 5.1i, % 5.1i, % 5.1i, % 5.1i, % 5.1i, % 5.1i", 0, 5, -1, -10, 100, -1862, INT_MIN, INT_MAX);
	/* 91 */ test_print_int_eight("% 5.5i, % 5.5i, % 5.5i, % 5.5i, % 5.5i, % 5.5i, % 5.5i, % 5.5i", 0, 5, -1, -10, 100, -1862, INT_MIN, INT_MAX);
	/* 92 */ test_print_int_eight("% 5.10i, % 5.10i, % 5.10i, % 5.10i, % 5.10i, % 5.10i, % 5.10i, % 5.10i", 0, 5, -1, -10, 100, -1862, INT_MIN, INT_MAX);
	/* 93 */ test_print_int_eight("% 5.100i, % 5.100i, % 5.100i, % 5.100i, % 5.100i, % 5.100i, % 5.100i, % 5.100i", 0, 5, -1, -10, 100, -1862, INT_MIN, INT_MAX);
	/* 94 */ test_print_int_eight("% 10.i, % 10.i, % 10.i, % 10.i, % 10.i, % 10.i, % 10.i, % 10.i", 0, 5, -1, -10, 100, -1862, INT_MIN, INT_MAX);
	/* 95 */ test_print_int_eight("% 10.0i, % 10.0i, % 10.0i, % 10.0i, % 10.0i, % 10.0i, % 10.0i, % 10.0i", 0, 5, -1, -10, 100, -1862, INT_MIN, INT_MAX);
	/* 96 */ test_print_int_eight("% 10.1i, % 10.1i, % 10.1i, % 10.1i, % 10.1i, % 10.1i, % 10.1i, % 10.1i", 0, 5, -1, -10, 100, -1862, INT_MIN, INT_MAX);
	/* 97 */ test_print_int_eight("% 10.5i, % 10.5i, % 10.5i, % 10.5i, % 10.5i, % 10.5i, % 10.5i, % 10.5i", 0, 5, -1, -10, 100, -1862, INT_MIN, INT_MAX);
	/* 98 */ test_print_int_eight("% 10.10i, % 10.10i, % 10.10i, % 10.10i, % 10.10i, % 10.10i, % 10.10i, % 10.10i", 0, 5, -1, -10, 100, -1862, INT_MIN, INT_MAX);
	/* 99 */ test_print_int_eight("% 10.100i, % 10.100i, % 10.100i, % 10.100i, % 10.100i, % 10.100i, % 10.100i, % 10.100i", 0, 5, -1, -10, 100, -1862, INT_MIN, INT_MAX);
	/* 100 */ test_print_int_eight("% 100.i, % 100.i, % 100.i, % 100.i, % 100.i, % 100.i, % 100.i, % 100.i", 0, 5, -1, -10, 100, -1862, INT_MIN, INT_MAX);
	/* 101 */ test_print_int_eight("% 100.0i, % 100.0i, % 100.0i, % 100.0i, % 100.0i, % 100.0i, % 100.0i, % 100.0i", 0, 5, -1, -10, 100, -1862, INT_MIN, INT_MAX);
	/* 102 */ test_print_int_eight("% 100.1i, % 100.1i, % 100.1i, % 100.1i, % 100.1i, % 100.1i, % 100.1i, % 100.1i", 0, 5, -1, -10, 100, -1862, INT_MIN, INT_MAX);
	/* 103 */ test_print_int_eight("% 100.5i, % 100.5i, % 100.5i, % 100.5i, % 100.5i, % 100.5i, % 100.5i, % 100.5i", 0, 5, -1, -10, 100, -1862, INT_MIN, INT_MAX);
	/* 104 */ test_print_int_eight("% 100.10i, % 100.10i, % 100.10i, % 100.10i, % 100.10i, % 100.10i, % 100.10i, % 100.10i", 0, 5, -1, -10, 100, -1862, INT_MIN, INT_MAX);
	/* 105 */ test_print_int_eight("% 100.100i, % 100.100i, % 100.100i, % 100.100i, % 100.100i, % 100.100i, % 100.100i, % 100.100i", 0, 5, -1, -10, 100, -1862, INT_MIN, INT_MAX);
	/* 106 */ test_print_int_eight("%0i, %0i, %0i, %0i, %0i, %0i, %0i, %0i", 0, 5, -1, -10, 100, -1862, INT_MIN, INT_MAX);
	/* 107 */ test_print_int_eight("%01i, %01i, %01i, %01i, %01i, %01i, %01i, %01i", 0, 5, -1, -10, 100, -1862, INT_MIN, INT_MAX);
	/* 108 */ test_print_int_eight("%05i, %05i, %05i, %05i, %05i, %05i, %05i, %05i", 0, 5, -1, -10, 100, -1862, INT_MIN, INT_MAX);
	/* 109 */ test_print_int_eight("%010i, %010i, %010i, %010i, %010i, %010i, %010i, %010i", 0, 5, -1, -10, 100, -1862, INT_MIN, INT_MAX);
	/* 110 */ test_print_int_eight("%0100i, %0100i, %0100i, %0100i, %0100i, %0100i, %0100i, %0100i", 0, 5, -1, -10, 100, -1862, INT_MIN, INT_MAX);
	/* 111 */ test_print_int_eight("%0.i, %0.i, %0.i, %0.i, %0.i, %0.i, %0.i, %0.i", 0, 5, -1, -10, 100, -1862, INT_MIN, INT_MAX);
	/* 112 */ test_print_int_eight("%0.0i, %0.0i, %0.0i, %0.0i, %0.0i, %0.0i, %0.0i, %0.0i", 0, 5, -1, -10, 100, -1862, INT_MIN, INT_MAX);
	/* 113 */ test_print_int_eight("%0.1i, %0.1i, %0.1i, %0.1i, %0.1i, %0.1i, %0.1i, %0.1i", 0, 5, -1, -10, 100, -1862, INT_MIN, INT_MAX);
	/* 114 */ test_print_int_eight("%0.5i, %0.5i, %0.5i, %0.5i, %0.5i, %0.5i, %0.5i, %0.5i", 0, 5, -1, -10, 100, -1862, INT_MIN, INT_MAX);
	/* 115 */ test_print_int_eight("%0.10i, %0.10i, %0.10i, %0.10i, %0.10i, %0.10i, %0.10i, %0.10i", 0, 5, -1, -10, 100, -1862, INT_MIN, INT_MAX);
	/* 116 */ test_print_int_eight("%0.100i, %0.100i, %0.100i, %0.100i, %0.100i, %0.100i, %0.100i, %0.100i", 0, 5, -1, -10, 100, -1862, INT_MIN, INT_MAX);
	/* 117 */ test_print_int_eight("%01.i, %01.i, %01.i, %01.i, %01.i, %01.i, %01.i, %01.i", 0, 5, -1, -10, 100, -1862, INT_MIN, INT_MAX);
	/* 118 */ test_print_int_eight("%01.0i, %01.0i, %01.0i, %01.0i, %01.0i, %01.0i, %01.0i, %01.0i", 0, 5, -1, -10, 100, -1862, INT_MIN, INT_MAX);
	/* 119 */ test_print_int_eight("%01.1i, %01.1i, %01.1i, %01.1i, %01.1i, %01.1i, %01.1i, %01.1i", 0, 5, -1, -10, 100, -1862, INT_MIN, INT_MAX);
	/* 120 */ test_print_int_eight("%01.5i, %01.5i, %01.5i, %01.5i, %01.5i, %01.5i, %01.5i, %01.5i", 0, 5, -1, -10, 100, -1862, INT_MIN, INT_MAX);
	/* 121 */ test_print_int_eight("%01.10i, %01.10i, %01.10i, %01.10i, %01.10i, %01.10i, %01.10i, %01.10i", 0, 5, -1, -10, 100, -1862, INT_MIN, INT_MAX);
	/* 122 */ test_print_int_eight("%01.100i, %01.100i, %01.100i, %01.100i, %01.100i, %01.100i, %01.100i, %01.100i", 0, 5, -1, -10, 100, -1862, INT_MIN, INT_MAX);
	/* 123 */ test_print_int_eight("%05.i, %05.i, %05.i, %05.i, %05.i, %05.i, %05.i, %05.i", 0, 5, -1, -10, 100, -1862, INT_MIN, INT_MAX);
	/* 124 */ test_print_int_eight("%05.0i, %05.0i, %05.0i, %05.0i, %05.0i, %05.0i, %05.0i, %05.0i", 0, 5, -1, -10, 100, -1862, INT_MIN, INT_MAX);
	/* 125 */ test_print_int_eight("%05.1i, %05.1i, %05.1i, %05.1i, %05.1i, %05.1i, %05.1i, %05.1i", 0, 5, -1, -10, 100, -1862, INT_MIN, INT_MAX);
	/* 126 */ test_print_int_eight("%05.5i, %05.5i, %05.5i, %05.5i, %05.5i, %05.5i, %05.5i, %05.5i", 0, 5, -1, -10, 100, -1862, INT_MIN, INT_MAX);
	/* 127 */ test_print_int_eight("%05.10i, %05.10i, %05.10i, %05.10i, %05.10i, %05.10i, %05.10i, %05.10i", 0, 5, -1, -10, 100, -1862, INT_MIN, INT_MAX);
	/* 128 */ test_print_int_eight("%05.100i, %05.100i, %05.100i, %05.100i, %05.100i, %05.100i, %05.100i, %05.100i", 0, 5, -1, -10, 100, -1862, INT_MIN, INT_MAX);
	/* 129 */ test_print_int_eight("%010.i, %010.i, %010.i, %010.i, %010.i, %010.i, %010.i, %010.i", 0, 5, -1, -10, 100, -1862, INT_MIN, INT_MAX);
	/* 130 */ test_print_int_eight("%010.0i, %010.0i, %010.0i, %010.0i, %010.0i, %010.0i, %010.0i, %010.0i", 0, 5, -1, -10, 100, -1862, INT_MIN, INT_MAX);
	/* 131 */ test_print_int_eight("%010.1i, %010.1i, %010.1i, %010.1i, %010.1i, %010.1i, %010.1i, %010.1i", 0, 5, -1, -10, 100, -1862, INT_MIN, INT_MAX);
	/* 132 */ test_print_int_eight("%010.5i, %010.5i, %010.5i, %010.5i, %010.5i, %010.5i, %010.5i, %010.5i", 0, 5, -1, -10, 100, -1862, INT_MIN, INT_MAX);
	/* 133 */ test_print_int_eight("%010.10i, %010.10i, %010.10i, %010.10i, %010.10i, %010.10i, %010.10i, %010.10i", 0, 5, -1, -10, 100, -1862, INT_MIN, INT_MAX);
	/* 134 */ test_print_int_eight("%010.100i, %010.100i, %010.100i, %010.100i, %010.100i, %010.100i, %010.100i, %010.100i", 0, 5, -1, -10, 100, -1862, INT_MIN, INT_MAX);
	/* 135 */ test_print_int_eight("%0100.i, %0100.i, %0100.i, %0100.i, %0100.i, %0100.i, %0100.i, %0100.i", 0, 5, -1, -10, 100, -1862, INT_MIN, INT_MAX);
	/* 136 */ test_print_int_eight("%0100.0i, %0100.0i, %0100.0i, %0100.0i, %0100.0i, %0100.0i, %0100.0i, %0100.0i", 0, 5, -1, -10, 100, -1862, INT_MIN, INT_MAX);
	/* 137 */ test_print_int_eight("%0100.1i, %0100.1i, %0100.1i, %0100.1i, %0100.1i, %0100.1i, %0100.1i, %0100.1i", 0, 5, -1, -10, 100, -1862, INT_MIN, INT_MAX);
	/* 138 */ test_print_int_eight("%0100.5i, %0100.5i, %0100.5i, %0100.5i, %0100.5i, %0100.5i, %0100.5i, %0100.5i", 0, 5, -1, -10, 100, -1862, INT_MIN, INT_MAX);
	/* 139 */ test_print_int_eight("%0100.10i, %0100.10i, %0100.10i, %0100.10i, %0100.10i, %0100.10i, %0100.10i, %0100.10i", 0, 5, -1, -10, 100, -1862, INT_MIN, INT_MAX);
	/* 140 */ test_print_int_eight("%0100.100i, %0100.100i, %0100.100i, %0100.100i, %0100.100i, %0100.100i, %0100.100i, %0100.100i", 0, 5, -1, -10, 100, -1862, INT_MIN, INT_MAX);
	/* 141 */ test_print_int_eight("%0+i, %0+i, %0+i, %0+i, %0+i, %0+i, %0+i, %0+i", 0, 5, -1, -10, 100, -1862, INT_MIN, INT_MAX);
	/* 142 */ test_print_int_eight("%0+1i, %0+1i, %0+1i, %0+1i, %0+1i, %0+1i, %0+1i, %0+1i", 0, 5, -1, -10, 100, -1862, INT_MIN, INT_MAX);
	/* 143 */ test_print_int_eight("%0+5i, %0+5i, %0+5i, %0+5i, %0+5i, %0+5i, %0+5i, %0+5i", 0, 5, -1, -10, 100, -1862, INT_MIN, INT_MAX);
	/* 144 */ test_print_int_eight("%0+10i, %0+10i, %0+10i, %0+10i, %0+10i, %0+10i, %0+10i, %0+10i", 0, 5, -1, -10, 100, -1862, INT_MIN, INT_MAX);
	/* 145 */ test_print_int_eight("%0+100i, %0+100i, %0+100i, %0+100i, %0+100i, %0+100i, %0+100i, %0+100i", 0, 5, -1, -10, 100, -1862, INT_MIN, INT_MAX);
	/* 146 */ test_print_int_eight("%0+.i, %0+.i, %0+.i, %0+.i, %0+.i, %0+.i, %0+.i, %0+.i", 0, 5, -1, -10, 100, -1862, INT_MIN, INT_MAX);
	/* 147 */ test_print_int_eight("%0+.0i, %0+.0i, %0+.0i, %0+.0i, %0+.0i, %0+.0i, %0+.0i, %0+.0i", 0, 5, -1, -10, 100, -1862, INT_MIN, INT_MAX);
	/* 148 */ test_print_int_eight("%0+.1i, %0+.1i, %0+.1i, %0+.1i, %0+.1i, %0+.1i, %0+.1i, %0+.1i", 0, 5, -1, -10, 100, -1862, INT_MIN, INT_MAX);
	/* 149 */ test_print_int_eight("%0+.5i, %0+.5i, %0+.5i, %0+.5i, %0+.5i, %0+.5i, %0+.5i, %0+.5i", 0, 5, -1, -10, 100, -1862, INT_MIN, INT_MAX);
	/* 150 */ test_print_int_eight("%0+.10i, %0+.10i, %0+.10i, %0+.10i, %0+.10i, %0+.10i, %0+.10i, %0+.10i", 0, 5, -1, -10, 100, -1862, INT_MIN, INT_MAX);
	/* 151 */ test_print_int_eight("%0+.100i, %0+.100i, %0+.100i, %0+.100i, %0+.100i, %0+.100i, %0+.100i, %0+.100i", 0, 5, -1, -10, 100, -1862, INT_MIN, INT_MAX);
	/* 152 */ test_print_int_eight("%0+1.i, %0+1.i, %0+1.i, %0+1.i, %0+1.i, %0+1.i, %0+1.i, %0+1.i", 0, 5, -1, -10, 100, -1862, INT_MIN, INT_MAX);
	/* 153 */ test_print_int_eight("%0+1.0i, %0+1.0i, %0+1.0i, %0+1.0i, %0+1.0i, %0+1.0i, %0+1.0i, %0+1.0i", 0, 5, -1, -10, 100, -1862, INT_MIN, INT_MAX);
	/* 154 */ test_print_int_eight("%0+1.1i, %0+1.1i, %0+1.1i, %0+1.1i, %0+1.1i, %0+1.1i, %0+1.1i, %0+1.1i", 0, 5, -1, -10, 100, -1862, INT_MIN, INT_MAX);
	/* 155 */ test_print_int_eight("%0+1.5i, %0+1.5i, %0+1.5i, %0+1.5i, %0+1.5i, %0+1.5i, %0+1.5i, %0+1.5i", 0, 5, -1, -10, 100, -1862, INT_MIN, INT_MAX);
	/* 156 */ test_print_int_eight("%0+1.10i, %0+1.10i, %0+1.10i, %0+1.10i, %0+1.10i, %0+1.10i, %0+1.10i, %0+1.10i", 0, 5, -1, -10, 100, -1862, INT_MIN, INT_MAX);
	/* 157 */ test_print_int_eight("%0+1.100i, %0+1.100i, %0+1.100i, %0+1.100i, %0+1.100i, %0+1.100i, %0+1.100i, %0+1.100i", 0, 5, -1, -10, 100, -1862, INT_MIN, INT_MAX);
	/* 158 */ test_print_int_eight("%0+5.i, %0+5.i, %0+5.i, %0+5.i, %0+5.i, %0+5.i, %0+5.i, %0+5.i", 0, 5, -1, -10, 100, -1862, INT_MIN, INT_MAX);
	/* 159 */ test_print_int_eight("%0+5.0i, %0+5.0i, %0+5.0i, %0+5.0i, %0+5.0i, %0+5.0i, %0+5.0i, %0+5.0i", 0, 5, -1, -10, 100, -1862, INT_MIN, INT_MAX);
	/* 160 */ test_print_int_eight("%0+5.1i, %0+5.1i, %0+5.1i, %0+5.1i, %0+5.1i, %0+5.1i, %0+5.1i, %0+5.1i", 0, 5, -1, -10, 100, -1862, INT_MIN, INT_MAX);
	/* 161 */ test_print_int_eight("%0+5.5i, %0+5.5i, %0+5.5i, %0+5.5i, %0+5.5i, %0+5.5i, %0+5.5i, %0+5.5i", 0, 5, -1, -10, 100, -1862, INT_MIN, INT_MAX);
	/* 162 */ test_print_int_eight("%0+5.10i, %0+5.10i, %0+5.10i, %0+5.10i, %0+5.10i, %0+5.10i, %0+5.10i, %0+5.10i", 0, 5, -1, -10, 100, -1862, INT_MIN, INT_MAX);
	/* 163 */ test_print_int_eight("%0+5.100i, %0+5.100i, %0+5.100i, %0+5.100i, %0+5.100i, %0+5.100i, %0+5.100i, %0+5.100i", 0, 5, -1, -10, 100, -1862, INT_MIN, INT_MAX);
	/* 164 */ test_print_int_eight("%0+10.i, %0+10.i, %0+10.i, %0+10.i, %0+10.i, %0+10.i, %0+10.i, %0+10.i", 0, 5, -1, -10, 100, -1862, INT_MIN, INT_MAX);
	/* 165 */ test_print_int_eight("%0+10.0i, %0+10.0i, %0+10.0i, %0+10.0i, %0+10.0i, %0+10.0i, %0+10.0i, %0+10.0i", 0, 5, -1, -10, 100, -1862, INT_MIN, INT_MAX);
	/* 166 */ test_print_int_eight("%0+10.1i, %0+10.1i, %0+10.1i, %0+10.1i, %0+10.1i, %0+10.1i, %0+10.1i, %0+10.1i", 0, 5, -1, -10, 100, -1862, INT_MIN, INT_MAX);
	/* 167 */ test_print_int_eight("%0+10.5i, %0+10.5i, %0+10.5i, %0+10.5i, %0+10.5i, %0+10.5i, %0+10.5i, %0+10.5i", 0, 5, -1, -10, 100, -1862, INT_MIN, INT_MAX);
	/* 168 */ test_print_int_eight("%0+10.10i, %0+10.10i, %0+10.10i, %0+10.10i, %0+10.10i, %0+10.10i, %0+10.10i, %0+10.10i", 0, 5, -1, -10, 100, -1862, INT_MIN, INT_MAX);
	/* 169 */ test_print_int_eight("%0+10.100i, %0+10.100i, %0+10.100i, %0+10.100i, %0+10.100i, %0+10.100i, %0+10.100i, %0+10.100i", 0, 5, -1, -10, 100, -1862, INT_MIN, INT_MAX);
	/* 170 */ test_print_int_eight("%0+100.i, %0+100.i, %0+100.i, %0+100.i, %0+100.i, %0+100.i, %0+100.i, %0+100.i", 0, 5, -1, -10, 100, -1862, INT_MIN, INT_MAX);
	/* 171 */ test_print_int_eight("%0+100.0i, %0+100.0i, %0+100.0i, %0+100.0i, %0+100.0i, %0+100.0i, %0+100.0i, %0+100.0i", 0, 5, -1, -10, 100, -1862, INT_MIN, INT_MAX);
	/* 172 */ test_print_int_eight("%0+100.1i, %0+100.1i, %0+100.1i, %0+100.1i, %0+100.1i, %0+100.1i, %0+100.1i, %0+100.1i", 0, 5, -1, -10, 100, -1862, INT_MIN, INT_MAX);
	/* 173 */ test_print_int_eight("%0+100.5i, %0+100.5i, %0+100.5i, %0+100.5i, %0+100.5i, %0+100.5i, %0+100.5i, %0+100.5i", 0, 5, -1, -10, 100, -1862, INT_MIN, INT_MAX);
	/* 174 */ test_print_int_eight("%0+100.10i, %0+100.10i, %0+100.10i, %0+100.10i, %0+100.10i, %0+100.10i, %0+100.10i, %0+100.10i", 0, 5, -1, -10, 100, -1862, INT_MIN, INT_MAX);
	/* 175 */ test_print_int_eight("%0+100.100i, %0+100.100i, %0+100.100i, %0+100.100i, %0+100.100i, %0+100.100i, %0+100.100i, %0+100.100i", 0, 5, -1, -10, 100, -1862, INT_MIN, INT_MAX);
	/* 176 */ test_print_int_eight("%0 i, %0 i, %0 i, %0 i, %0 i, %0 i, %0 i, %0 i", 0, 5, -1, -10, 100, -1862, INT_MIN, INT_MAX);
	/* 177 */ test_print_int_eight("%0 1i, %0 1i, %0 1i, %0 1i, %0 1i, %0 1i, %0 1i, %0 1i", 0, 5, -1, -10, 100, -1862, INT_MIN, INT_MAX);
	/* 178 */ test_print_int_eight("%0 5i, %0 5i, %0 5i, %0 5i, %0 5i, %0 5i, %0 5i, %0 5i", 0, 5, -1, -10, 100, -1862, INT_MIN, INT_MAX);
	/* 179 */ test_print_int_eight("%0 10i, %0 10i, %0 10i, %0 10i, %0 10i, %0 10i, %0 10i, %0 10i", 0, 5, -1, -10, 100, -1862, INT_MIN, INT_MAX);
	/* 180 */ test_print_int_eight("%0 100i, %0 100i, %0 100i, %0 100i, %0 100i, %0 100i, %0 100i, %0 100i", 0, 5, -1, -10, 100, -1862, INT_MIN, INT_MAX);
	/* 181 */ test_print_int_eight("%0 .i, %0 .i, %0 .i, %0 .i, %0 .i, %0 .i, %0 .i, %0 .i", 0, 5, -1, -10, 100, -1862, INT_MIN, INT_MAX);
	/* 182 */ test_print_int_eight("%0 .0i, %0 .0i, %0 .0i, %0 .0i, %0 .0i, %0 .0i, %0 .0i, %0 .0i", 0, 5, -1, -10, 100, -1862, INT_MIN, INT_MAX);
	/* 183 */ test_print_int_eight("%0 .1i, %0 .1i, %0 .1i, %0 .1i, %0 .1i, %0 .1i, %0 .1i, %0 .1i", 0, 5, -1, -10, 100, -1862, INT_MIN, INT_MAX);
	/* 184 */ test_print_int_eight("%0 .5i, %0 .5i, %0 .5i, %0 .5i, %0 .5i, %0 .5i, %0 .5i, %0 .5i", 0, 5, -1, -10, 100, -1862, INT_MIN, INT_MAX);
	/* 185 */ test_print_int_eight("%0 .10i, %0 .10i, %0 .10i, %0 .10i, %0 .10i, %0 .10i, %0 .10i, %0 .10i", 0, 5, -1, -10, 100, -1862, INT_MIN, INT_MAX);
	/* 186 */ test_print_int_eight("%0 .100i, %0 .100i, %0 .100i, %0 .100i, %0 .100i, %0 .100i, %0 .100i, %0 .100i", 0, 5, -1, -10, 100, -1862, INT_MIN, INT_MAX);
	/* 187 */ test_print_int_eight("%0 1.i, %0 1.i, %0 1.i, %0 1.i, %0 1.i, %0 1.i, %0 1.i, %0 1.i", 0, 5, -1, -10, 100, -1862, INT_MIN, INT_MAX);
	/* 188 */ test_print_int_eight("%0 1.0i, %0 1.0i, %0 1.0i, %0 1.0i, %0 1.0i, %0 1.0i, %0 1.0i, %0 1.0i", 0, 5, -1, -10, 100, -1862, INT_MIN, INT_MAX);
	/* 189 */ test_print_int_eight("%0 1.1i, %0 1.1i, %0 1.1i, %0 1.1i, %0 1.1i, %0 1.1i, %0 1.1i, %0 1.1i", 0, 5, -1, -10, 100, -1862, INT_MIN, INT_MAX);
	/* 190 */ test_print_int_eight("%0 1.5i, %0 1.5i, %0 1.5i, %0 1.5i, %0 1.5i, %0 1.5i, %0 1.5i, %0 1.5i", 0, 5, -1, -10, 100, -1862, INT_MIN, INT_MAX);
	/* 191 */ test_print_int_eight("%0 1.10i, %0 1.10i, %0 1.10i, %0 1.10i, %0 1.10i, %0 1.10i, %0 1.10i, %0 1.10i", 0, 5, -1, -10, 100, -1862, INT_MIN, INT_MAX);
	/* 192 */ test_print_int_eight("%0 1.100i, %0 1.100i, %0 1.100i, %0 1.100i, %0 1.100i, %0 1.100i, %0 1.100i, %0 1.100i", 0, 5, -1, -10, 100, -1862, INT_MIN, INT_MAX);
	/* 193 */ test_print_int_eight("%0 5.i, %0 5.i, %0 5.i, %0 5.i, %0 5.i, %0 5.i, %0 5.i, %0 5.i", 0, 5, -1, -10, 100, -1862, INT_MIN, INT_MAX);
	/* 194 */ test_print_int_eight("%0 5.0i, %0 5.0i, %0 5.0i, %0 5.0i, %0 5.0i, %0 5.0i, %0 5.0i, %0 5.0i", 0, 5, -1, -10, 100, -1862, INT_MIN, INT_MAX);
	/* 195 */ test_print_int_eight("%0 5.1i, %0 5.1i, %0 5.1i, %0 5.1i, %0 5.1i, %0 5.1i, %0 5.1i, %0 5.1i", 0, 5, -1, -10, 100, -1862, INT_MIN, INT_MAX);
	/* 196 */ test_print_int_eight("%0 5.5i, %0 5.5i, %0 5.5i, %0 5.5i, %0 5.5i, %0 5.5i, %0 5.5i, %0 5.5i", 0, 5, -1, -10, 100, -1862, INT_MIN, INT_MAX);
	/* 197 */ test_print_int_eight("%0 5.10i, %0 5.10i, %0 5.10i, %0 5.10i, %0 5.10i, %0 5.10i, %0 5.10i, %0 5.10i", 0, 5, -1, -10, 100, -1862, INT_MIN, INT_MAX);
	/* 198 */ test_print_int_eight("%0 5.100i, %0 5.100i, %0 5.100i, %0 5.100i, %0 5.100i, %0 5.100i, %0 5.100i, %0 5.100i", 0, 5, -1, -10, 100, -1862, INT_MIN, INT_MAX);
	/* 199 */ test_print_int_eight("%0 10.i, %0 10.i, %0 10.i, %0 10.i, %0 10.i, %0 10.i, %0 10.i, %0 10.i", 0, 5, -1, -10, 100, -1862, INT_MIN, INT_MAX);
	/* 200 */ test_print_int_eight("%0 10.0i, %0 10.0i, %0 10.0i, %0 10.0i, %0 10.0i, %0 10.0i, %0 10.0i, %0 10.0i", 0, 5, -1, -10, 100, -1862, INT_MIN, INT_MAX);
	/* 201 */ test_print_int_eight("%0 10.1i, %0 10.1i, %0 10.1i, %0 10.1i, %0 10.1i, %0 10.1i, %0 10.1i, %0 10.1i", 0, 5, -1, -10, 100, -1862, INT_MIN, INT_MAX);
	/* 202 */ test_print_int_eight("%0 10.5i, %0 10.5i, %0 10.5i, %0 10.5i, %0 10.5i, %0 10.5i, %0 10.5i, %0 10.5i", 0, 5, -1, -10, 100, -1862, INT_MIN, INT_MAX);
	/* 203 */ test_print_int_eight("%0 10.10i, %0 10.10i, %0 10.10i, %0 10.10i, %0 10.10i, %0 10.10i, %0 10.10i, %0 10.10i", 0, 5, -1, -10, 100, -1862, INT_MIN, INT_MAX);
	/* 204 */ test_print_int_eight("%0 10.100i, %0 10.100i, %0 10.100i, %0 10.100i, %0 10.100i, %0 10.100i, %0 10.100i, %0 10.100i", 0, 5, -1, -10, 100, -1862, INT_MIN, INT_MAX);
	/* 205 */ test_print_int_eight("%0 100.i, %0 100.i, %0 100.i, %0 100.i, %0 100.i, %0 100.i, %0 100.i, %0 100.i", 0, 5, -1, -10, 100, -1862, INT_MIN, INT_MAX);
	/* 206 */ test_print_int_eight("%0 100.0i, %0 100.0i, %0 100.0i, %0 100.0i, %0 100.0i, %0 100.0i, %0 100.0i, %0 100.0i", 0, 5, -1, -10, 100, -1862, INT_MIN, INT_MAX);
	/* 207 */ test_print_int_eight("%0 100.1i, %0 100.1i, %0 100.1i, %0 100.1i, %0 100.1i, %0 100.1i, %0 100.1i, %0 100.1i", 0, 5, -1, -10, 100, -1862, INT_MIN, INT_MAX);
	/* 208 */ test_print_int_eight("%0 100.5i, %0 100.5i, %0 100.5i, %0 100.5i, %0 100.5i, %0 100.5i, %0 100.5i, %0 100.5i", 0, 5, -1, -10, 100, -1862, INT_MIN, INT_MAX);
	/* 209 */ test_print_int_eight("%0 100.10i, %0 100.10i, %0 100.10i, %0 100.10i, %0 100.10i, %0 100.10i, %0 100.10i, %0 100.10i", 0, 5, -1, -10, 100, -1862, INT_MIN, INT_MAX);
	/* 210 */ test_print_int_eight("%0 100.100i, %0 100.100i, %0 100.100i, %0 100.100i, %0 100.100i, %0 100.100i, %0 100.100i, %0 100.100i", 0, 5, -1, -10, 100, -1862, INT_MIN, INT_MAX);
	/* 211 */ test_print_int_eight("%-i, %-i, %-i, %-i, %-i, %-i, %-i, %-i", 0, 5, -1, -10, 100, -1862, INT_MIN, INT_MAX);
	/* 212 */ test_print_int_eight("%-1i, %-1i, %-1i, %-1i, %-1i, %-1i, %-1i, %-1i", 0, 5, -1, -10, 100, -1862, INT_MIN, INT_MAX);
	/* 213 */ test_print_int_eight("%-5i, %-5i, %-5i, %-5i, %-5i, %-5i, %-5i, %-5i", 0, 5, -1, -10, 100, -1862, INT_MIN, INT_MAX);
	/* 214 */ test_print_int_eight("%-10i, %-10i, %-10i, %-10i, %-10i, %-10i, %-10i, %-10i", 0, 5, -1, -10, 100, -1862, INT_MIN, INT_MAX);
	/* 215 */ test_print_int_eight("%-100i, %-100i, %-100i, %-100i, %-100i, %-100i, %-100i, %-100i", 0, 5, -1, -10, 100, -1862, INT_MIN, INT_MAX);
	/* 216 */ test_print_int_eight("%-.i, %-.i, %-.i, %-.i, %-.i, %-.i, %-.i, %-.i", 0, 5, -1, -10, 100, -1862, INT_MIN, INT_MAX);
	/* 217 */ test_print_int_eight("%-.0i, %-.0i, %-.0i, %-.0i, %-.0i, %-.0i, %-.0i, %-.0i", 0, 5, -1, -10, 100, -1862, INT_MIN, INT_MAX);
	/* 218 */ test_print_int_eight("%-.1i, %-.1i, %-.1i, %-.1i, %-.1i, %-.1i, %-.1i, %-.1i", 0, 5, -1, -10, 100, -1862, INT_MIN, INT_MAX);
	/* 219 */ test_print_int_eight("%-.5i, %-.5i, %-.5i, %-.5i, %-.5i, %-.5i, %-.5i, %-.5i", 0, 5, -1, -10, 100, -1862, INT_MIN, INT_MAX);
	/* 220 */ test_print_int_eight("%-.10i, %-.10i, %-.10i, %-.10i, %-.10i, %-.10i, %-.10i, %-.10i", 0, 5, -1, -10, 100, -1862, INT_MIN, INT_MAX);
	/* 221 */ test_print_int_eight("%-.100i, %-.100i, %-.100i, %-.100i, %-.100i, %-.100i, %-.100i, %-.100i", 0, 5, -1, -10, 100, -1862, INT_MIN, INT_MAX);
	/* 222 */ test_print_int_eight("%-1.i, %-1.i, %-1.i, %-1.i, %-1.i, %-1.i, %-1.i, %-1.i", 0, 5, -1, -10, 100, -1862, INT_MIN, INT_MAX);
	/* 223 */ test_print_int_eight("%-1.0i, %-1.0i, %-1.0i, %-1.0i, %-1.0i, %-1.0i, %-1.0i, %-1.0i", 0, 5, -1, -10, 100, -1862, INT_MIN, INT_MAX);
	/* 224 */ test_print_int_eight("%-1.1i, %-1.1i, %-1.1i, %-1.1i, %-1.1i, %-1.1i, %-1.1i, %-1.1i", 0, 5, -1, -10, 100, -1862, INT_MIN, INT_MAX);
	/* 225 */ test_print_int_eight("%-1.5i, %-1.5i, %-1.5i, %-1.5i, %-1.5i, %-1.5i, %-1.5i, %-1.5i", 0, 5, -1, -10, 100, -1862, INT_MIN, INT_MAX);
	/* 226 */ test_print_int_eight("%-1.10i, %-1.10i, %-1.10i, %-1.10i, %-1.10i, %-1.10i, %-1.10i, %-1.10i", 0, 5, -1, -10, 100, -1862, INT_MIN, INT_MAX);
	/* 227 */ test_print_int_eight("%-1.100i, %-1.100i, %-1.100i, %-1.100i, %-1.100i, %-1.100i, %-1.100i, %-1.100i", 0, 5, -1, -10, 100, -1862, INT_MIN, INT_MAX);
	/* 228 */ test_print_int_eight("%-5.i, %-5.i, %-5.i, %-5.i, %-5.i, %-5.i, %-5.i, %-5.i", 0, 5, -1, -10, 100, -1862, INT_MIN, INT_MAX);
	/* 229 */ test_print_int_eight("%-5.0i, %-5.0i, %-5.0i, %-5.0i, %-5.0i, %-5.0i, %-5.0i, %-5.0i", 0, 5, -1, -10, 100, -1862, INT_MIN, INT_MAX);
	/* 230 */ test_print_int_eight("%-5.1i, %-5.1i, %-5.1i, %-5.1i, %-5.1i, %-5.1i, %-5.1i, %-5.1i", 0, 5, -1, -10, 100, -1862, INT_MIN, INT_MAX);
	/* 231 */ test_print_int_eight("%-5.5i, %-5.5i, %-5.5i, %-5.5i, %-5.5i, %-5.5i, %-5.5i, %-5.5i", 0, 5, -1, -10, 100, -1862, INT_MIN, INT_MAX);
	/* 232 */ test_print_int_eight("%-5.10i, %-5.10i, %-5.10i, %-5.10i, %-5.10i, %-5.10i, %-5.10i, %-5.10i", 0, 5, -1, -10, 100, -1862, INT_MIN, INT_MAX);
	/* 233 */ test_print_int_eight("%-5.100i, %-5.100i, %-5.100i, %-5.100i, %-5.100i, %-5.100i, %-5.100i, %-5.100i", 0, 5, -1, -10, 100, -1862, INT_MIN, INT_MAX);
	/* 234 */ test_print_int_eight("%-10.i, %-10.i, %-10.i, %-10.i, %-10.i, %-10.i, %-10.i, %-10.i", 0, 5, -1, -10, 100, -1862, INT_MIN, INT_MAX);
	/* 235 */ test_print_int_eight("%-10.0i, %-10.0i, %-10.0i, %-10.0i, %-10.0i, %-10.0i, %-10.0i, %-10.0i", 0, 5, -1, -10, 100, -1862, INT_MIN, INT_MAX);
	/* 236 */ test_print_int_eight("%-10.1i, %-10.1i, %-10.1i, %-10.1i, %-10.1i, %-10.1i, %-10.1i, %-10.1i", 0, 5, -1, -10, 100, -1862, INT_MIN, INT_MAX);
	/* 237 */ test_print_int_eight("%-10.5i, %-10.5i, %-10.5i, %-10.5i, %-10.5i, %-10.5i, %-10.5i, %-10.5i", 0, 5, -1, -10, 100, -1862, INT_MIN, INT_MAX);
	/* 238 */ test_print_int_eight("%-10.10i, %-10.10i, %-10.10i, %-10.10i, %-10.10i, %-10.10i, %-10.10i, %-10.10i", 0, 5, -1, -10, 100, -1862, INT_MIN, INT_MAX);
	/* 239 */ test_print_int_eight("%-10.100i, %-10.100i, %-10.100i, %-10.100i, %-10.100i, %-10.100i, %-10.100i, %-10.100i", 0, 5, -1, -10, 100, -1862, INT_MIN, INT_MAX);
	/* 240 */ test_print_int_eight("%-100.i, %-100.i, %-100.i, %-100.i, %-100.i, %-100.i, %-100.i, %-100.i", 0, 5, -1, -10, 100, -1862, INT_MIN, INT_MAX);
	/* 241 */ test_print_int_eight("%-100.0i, %-100.0i, %-100.0i, %-100.0i, %-100.0i, %-100.0i, %-100.0i, %-100.0i", 0, 5, -1, -10, 100, -1862, INT_MIN, INT_MAX);
	/* 242 */ test_print_int_eight("%-100.1i, %-100.1i, %-100.1i, %-100.1i, %-100.1i, %-100.1i, %-100.1i, %-100.1i", 0, 5, -1, -10, 100, -1862, INT_MIN, INT_MAX);
	/* 243 */ test_print_int_eight("%-100.5i, %-100.5i, %-100.5i, %-100.5i, %-100.5i, %-100.5i, %-100.5i, %-100.5i", 0, 5, -1, -10, 100, -1862, INT_MIN, INT_MAX);
	/* 244 */ test_print_int_eight("%-100.10i, %-100.10i, %-100.10i, %-100.10i, %-100.10i, %-100.10i, %-100.10i, %-100.10i", 0, 5, -1, -10, 100, -1862, INT_MIN, INT_MAX);
	/* 245 */ test_print_int_eight("%-100.100i, %-100.100i, %-100.100i, %-100.100i, %-100.100i, %-100.100i, %-100.100i, %-100.100i", 0, 5, -1, -10, 100, -1862, INT_MIN, INT_MAX);
	/* 246 */ test_print_int_eight("%-+i, %-+i, %-+i, %-+i, %-+i, %-+i, %-+i, %-+i", 0, 5, -1, -10, 100, -1862, INT_MIN, INT_MAX);
	/* 247 */ test_print_int_eight("%-+1i, %-+1i, %-+1i, %-+1i, %-+1i, %-+1i, %-+1i, %-+1i", 0, 5, -1, -10, 100, -1862, INT_MIN, INT_MAX);
	/* 248 */ test_print_int_eight("%-+5i, %-+5i, %-+5i, %-+5i, %-+5i, %-+5i, %-+5i, %-+5i", 0, 5, -1, -10, 100, -1862, INT_MIN, INT_MAX);
	/* 249 */ test_print_int_eight("%-+10i, %-+10i, %-+10i, %-+10i, %-+10i, %-+10i, %-+10i, %-+10i", 0, 5, -1, -10, 100, -1862, INT_MIN, INT_MAX);
	/* 250 */ test_print_int_eight("%-+100i, %-+100i, %-+100i, %-+100i, %-+100i, %-+100i, %-+100i, %-+100i", 0, 5, -1, -10, 100, -1862, INT_MIN, INT_MAX);
	/* 251 */ test_print_int_eight("%-+.i, %-+.i, %-+.i, %-+.i, %-+.i, %-+.i, %-+.i, %-+.i", 0, 5, -1, -10, 100, -1862, INT_MIN, INT_MAX);
	/* 252 */ test_print_int_eight("%-+.0i, %-+.0i, %-+.0i, %-+.0i, %-+.0i, %-+.0i, %-+.0i, %-+.0i", 0, 5, -1, -10, 100, -1862, INT_MIN, INT_MAX);
	/* 253 */ test_print_int_eight("%-+.1i, %-+.1i, %-+.1i, %-+.1i, %-+.1i, %-+.1i, %-+.1i, %-+.1i", 0, 5, -1, -10, 100, -1862, INT_MIN, INT_MAX);
	/* 254 */ test_print_int_eight("%-+.5i, %-+.5i, %-+.5i, %-+.5i, %-+.5i, %-+.5i, %-+.5i, %-+.5i", 0, 5, -1, -10, 100, -1862, INT_MIN, INT_MAX);
	/* 255 */ test_print_int_eight("%-+.10i, %-+.10i, %-+.10i, %-+.10i, %-+.10i, %-+.10i, %-+.10i, %-+.10i", 0, 5, -1, -10, 100, -1862, INT_MIN, INT_MAX);
	/* 256 */ test_print_int_eight("%-+.100i, %-+.100i, %-+.100i, %-+.100i, %-+.100i, %-+.100i, %-+.100i, %-+.100i", 0, 5, -1, -10, 100, -1862, INT_MIN, INT_MAX);
	/* 257 */ test_print_int_eight("%-+1.i, %-+1.i, %-+1.i, %-+1.i, %-+1.i, %-+1.i, %-+1.i, %-+1.i", 0, 5, -1, -10, 100, -1862, INT_MIN, INT_MAX);
	/* 258 */ test_print_int_eight("%-+1.0i, %-+1.0i, %-+1.0i, %-+1.0i, %-+1.0i, %-+1.0i, %-+1.0i, %-+1.0i", 0, 5, -1, -10, 100, -1862, INT_MIN, INT_MAX);
	/* 259 */ test_print_int_eight("%-+1.1i, %-+1.1i, %-+1.1i, %-+1.1i, %-+1.1i, %-+1.1i, %-+1.1i, %-+1.1i", 0, 5, -1, -10, 100, -1862, INT_MIN, INT_MAX);
	/* 260 */ test_print_int_eight("%-+1.5i, %-+1.5i, %-+1.5i, %-+1.5i, %-+1.5i, %-+1.5i, %-+1.5i, %-+1.5i", 0, 5, -1, -10, 100, -1862, INT_MIN, INT_MAX);
	/* 261 */ test_print_int_eight("%-+1.10i, %-+1.10i, %-+1.10i, %-+1.10i, %-+1.10i, %-+1.10i, %-+1.10i, %-+1.10i", 0, 5, -1, -10, 100, -1862, INT_MIN, INT_MAX);
	/* 262 */ test_print_int_eight("%-+1.100i, %-+1.100i, %-+1.100i, %-+1.100i, %-+1.100i, %-+1.100i, %-+1.100i, %-+1.100i", 0, 5, -1, -10, 100, -1862, INT_MIN, INT_MAX);
	/* 263 */ test_print_int_eight("%-+5.i, %-+5.i, %-+5.i, %-+5.i, %-+5.i, %-+5.i, %-+5.i, %-+5.i", 0, 5, -1, -10, 100, -1862, INT_MIN, INT_MAX);
	/* 264 */ test_print_int_eight("%-+5.0i, %-+5.0i, %-+5.0i, %-+5.0i, %-+5.0i, %-+5.0i, %-+5.0i, %-+5.0i", 0, 5, -1, -10, 100, -1862, INT_MIN, INT_MAX);
	/* 265 */ test_print_int_eight("%-+5.1i, %-+5.1i, %-+5.1i, %-+5.1i, %-+5.1i, %-+5.1i, %-+5.1i, %-+5.1i", 0, 5, -1, -10, 100, -1862, INT_MIN, INT_MAX);
	/* 266 */ test_print_int_eight("%-+5.5i, %-+5.5i, %-+5.5i, %-+5.5i, %-+5.5i, %-+5.5i, %-+5.5i, %-+5.5i", 0, 5, -1, -10, 100, -1862, INT_MIN, INT_MAX);
	/* 267 */ test_print_int_eight("%-+5.10i, %-+5.10i, %-+5.10i, %-+5.10i, %-+5.10i, %-+5.10i, %-+5.10i, %-+5.10i", 0, 5, -1, -10, 100, -1862, INT_MIN, INT_MAX);
	/* 268 */ test_print_int_eight("%-+5.100i, %-+5.100i, %-+5.100i, %-+5.100i, %-+5.100i, %-+5.100i, %-+5.100i, %-+5.100i", 0, 5, -1, -10, 100, -1862, INT_MIN, INT_MAX);
	/* 269 */ test_print_int_eight("%-+10.i, %-+10.i, %-+10.i, %-+10.i, %-+10.i, %-+10.i, %-+10.i, %-+10.i", 0, 5, -1, -10, 100, -1862, INT_MIN, INT_MAX);
	/* 270 */ test_print_int_eight("%-+10.0i, %-+10.0i, %-+10.0i, %-+10.0i, %-+10.0i, %-+10.0i, %-+10.0i, %-+10.0i", 0, 5, -1, -10, 100, -1862, INT_MIN, INT_MAX);
	/* 271 */ test_print_int_eight("%-+10.1i, %-+10.1i, %-+10.1i, %-+10.1i, %-+10.1i, %-+10.1i, %-+10.1i, %-+10.1i", 0, 5, -1, -10, 100, -1862, INT_MIN, INT_MAX);
	/* 272 */ test_print_int_eight("%-+10.5i, %-+10.5i, %-+10.5i, %-+10.5i, %-+10.5i, %-+10.5i, %-+10.5i, %-+10.5i", 0, 5, -1, -10, 100, -1862, INT_MIN, INT_MAX);
	/* 273 */ test_print_int_eight("%-+10.10i, %-+10.10i, %-+10.10i, %-+10.10i, %-+10.10i, %-+10.10i, %-+10.10i, %-+10.10i", 0, 5, -1, -10, 100, -1862, INT_MIN, INT_MAX);
	/* 274 */ test_print_int_eight("%-+10.100i, %-+10.100i, %-+10.100i, %-+10.100i, %-+10.100i, %-+10.100i, %-+10.100i, %-+10.100i", 0, 5, -1, -10, 100, -1862, INT_MIN, INT_MAX);
	/* 275 */ test_print_int_eight("%-+100.i, %-+100.i, %-+100.i, %-+100.i, %-+100.i, %-+100.i, %-+100.i, %-+100.i", 0, 5, -1, -10, 100, -1862, INT_MIN, INT_MAX);
	/* 276 */ test_print_int_eight("%-+100.0i, %-+100.0i, %-+100.0i, %-+100.0i, %-+100.0i, %-+100.0i, %-+100.0i, %-+100.0i", 0, 5, -1, -10, 100, -1862, INT_MIN, INT_MAX);
	/* 277 */ test_print_int_eight("%-+100.1i, %-+100.1i, %-+100.1i, %-+100.1i, %-+100.1i, %-+100.1i, %-+100.1i, %-+100.1i", 0, 5, -1, -10, 100, -1862, INT_MIN, INT_MAX);
	/* 278 */ test_print_int_eight("%-+100.5i, %-+100.5i, %-+100.5i, %-+100.5i, %-+100.5i, %-+100.5i, %-+100.5i, %-+100.5i", 0, 5, -1, -10, 100, -1862, INT_MIN, INT_MAX);
	/* 279 */ test_print_int_eight("%-+100.10i, %-+100.10i, %-+100.10i, %-+100.10i, %-+100.10i, %-+100.10i, %-+100.10i, %-+100.10i", 0, 5, -1, -10, 100, -1862, INT_MIN, INT_MAX);
	/* 280 */ test_print_int_eight("%-+100.100i, %-+100.100i, %-+100.100i, %-+100.100i, %-+100.100i, %-+100.100i, %-+100.100i, %-+100.100i", 0, 5, -1, -10, 100, -1862, INT_MIN, INT_MAX);
	/* 281 */ test_print_int_eight("%- i, %- i, %- i, %- i, %- i, %- i, %- i, %- i", 0, 5, -1, -10, 100, -1862, INT_MIN, INT_MAX);
	/* 282 */ test_print_int_eight("%- 1i, %- 1i, %- 1i, %- 1i, %- 1i, %- 1i, %- 1i, %- 1i", 0, 5, -1, -10, 100, -1862, INT_MIN, INT_MAX);
	/* 283 */ test_print_int_eight("%- 5i, %- 5i, %- 5i, %- 5i, %- 5i, %- 5i, %- 5i, %- 5i", 0, 5, -1, -10, 100, -1862, INT_MIN, INT_MAX);
	/* 284 */ test_print_int_eight("%- 10i, %- 10i, %- 10i, %- 10i, %- 10i, %- 10i, %- 10i, %- 10i", 0, 5, -1, -10, 100, -1862, INT_MIN, INT_MAX);
	/* 285 */ test_print_int_eight("%- 100i, %- 100i, %- 100i, %- 100i, %- 100i, %- 100i, %- 100i, %- 100i", 0, 5, -1, -10, 100, -1862, INT_MIN, INT_MAX);
	/* 286 */ test_print_int_eight("%- .i, %- .i, %- .i, %- .i, %- .i, %- .i, %- .i, %- .i", 0, 5, -1, -10, 100, -1862, INT_MIN, INT_MAX);
	/* 287 */ test_print_int_eight("%- .0i, %- .0i, %- .0i, %- .0i, %- .0i, %- .0i, %- .0i, %- .0i", 0, 5, -1, -10, 100, -1862, INT_MIN, INT_MAX);
	/* 288 */ test_print_int_eight("%- .1i, %- .1i, %- .1i, %- .1i, %- .1i, %- .1i, %- .1i, %- .1i", 0, 5, -1, -10, 100, -1862, INT_MIN, INT_MAX);
	/* 289 */ test_print_int_eight("%- .5i, %- .5i, %- .5i, %- .5i, %- .5i, %- .5i, %- .5i, %- .5i", 0, 5, -1, -10, 100, -1862, INT_MIN, INT_MAX);
	/* 290 */ test_print_int_eight("%- .10i, %- .10i, %- .10i, %- .10i, %- .10i, %- .10i, %- .10i, %- .10i", 0, 5, -1, -10, 100, -1862, INT_MIN, INT_MAX);
	/* 291 */ test_print_int_eight("%- .100i, %- .100i, %- .100i, %- .100i, %- .100i, %- .100i, %- .100i, %- .100i", 0, 5, -1, -10, 100, -1862, INT_MIN, INT_MAX);
	/* 292 */ test_print_int_eight("%- 1.i, %- 1.i, %- 1.i, %- 1.i, %- 1.i, %- 1.i, %- 1.i, %- 1.i", 0, 5, -1, -10, 100, -1862, INT_MIN, INT_MAX);
	/* 293 */ test_print_int_eight("%- 1.0i, %- 1.0i, %- 1.0i, %- 1.0i, %- 1.0i, %- 1.0i, %- 1.0i, %- 1.0i", 0, 5, -1, -10, 100, -1862, INT_MIN, INT_MAX);
	/* 294 */ test_print_int_eight("%- 1.1i, %- 1.1i, %- 1.1i, %- 1.1i, %- 1.1i, %- 1.1i, %- 1.1i, %- 1.1i", 0, 5, -1, -10, 100, -1862, INT_MIN, INT_MAX);
	/* 295 */ test_print_int_eight("%- 1.5i, %- 1.5i, %- 1.5i, %- 1.5i, %- 1.5i, %- 1.5i, %- 1.5i, %- 1.5i", 0, 5, -1, -10, 100, -1862, INT_MIN, INT_MAX);
	/* 296 */ test_print_int_eight("%- 1.10i, %- 1.10i, %- 1.10i, %- 1.10i, %- 1.10i, %- 1.10i, %- 1.10i, %- 1.10i", 0, 5, -1, -10, 100, -1862, INT_MIN, INT_MAX);
	/* 297 */ test_print_int_eight("%- 1.100i, %- 1.100i, %- 1.100i, %- 1.100i, %- 1.100i, %- 1.100i, %- 1.100i, %- 1.100i", 0, 5, -1, -10, 100, -1862, INT_MIN, INT_MAX);
	/* 298 */ test_print_int_eight("%- 5.i, %- 5.i, %- 5.i, %- 5.i, %- 5.i, %- 5.i, %- 5.i, %- 5.i", 0, 5, -1, -10, 100, -1862, INT_MIN, INT_MAX);
	/* 299 */ test_print_int_eight("%- 5.0i, %- 5.0i, %- 5.0i, %- 5.0i, %- 5.0i, %- 5.0i, %- 5.0i, %- 5.0i", 0, 5, -1, -10, 100, -1862, INT_MIN, INT_MAX);
	/* 300 */ test_print_int_eight("%- 5.1i, %- 5.1i, %- 5.1i, %- 5.1i, %- 5.1i, %- 5.1i, %- 5.1i, %- 5.1i", 0, 5, -1, -10, 100, -1862, INT_MIN, INT_MAX);
	/* 301 */ test_print_int_eight("%- 5.5i, %- 5.5i, %- 5.5i, %- 5.5i, %- 5.5i, %- 5.5i, %- 5.5i, %- 5.5i", 0, 5, -1, -10, 100, -1862, INT_MIN, INT_MAX);
	/* 302 */ test_print_int_eight("%- 5.10i, %- 5.10i, %- 5.10i, %- 5.10i, %- 5.10i, %- 5.10i, %- 5.10i, %- 5.10i", 0, 5, -1, -10, 100, -1862, INT_MIN, INT_MAX);
	/* 303 */ test_print_int_eight("%- 5.100i, %- 5.100i, %- 5.100i, %- 5.100i, %- 5.100i, %- 5.100i, %- 5.100i, %- 5.100i", 0, 5, -1, -10, 100, -1862, INT_MIN, INT_MAX);
	/* 304 */ test_print_int_eight("%- 10.i, %- 10.i, %- 10.i, %- 10.i, %- 10.i, %- 10.i, %- 10.i, %- 10.i", 0, 5, -1, -10, 100, -1862, INT_MIN, INT_MAX);
	/* 305 */ test_print_int_eight("%- 10.0i, %- 10.0i, %- 10.0i, %- 10.0i, %- 10.0i, %- 10.0i, %- 10.0i, %- 10.0i", 0, 5, -1, -10, 100, -1862, INT_MIN, INT_MAX);
	/* 306 */ test_print_int_eight("%- 10.1i, %- 10.1i, %- 10.1i, %- 10.1i, %- 10.1i, %- 10.1i, %- 10.1i, %- 10.1i", 0, 5, -1, -10, 100, -1862, INT_MIN, INT_MAX);
	/* 307 */ test_print_int_eight("%- 10.5i, %- 10.5i, %- 10.5i, %- 10.5i, %- 10.5i, %- 10.5i, %- 10.5i, %- 10.5i", 0, 5, -1, -10, 100, -1862, INT_MIN, INT_MAX);
	/* 308 */ test_print_int_eight("%- 10.10i, %- 10.10i, %- 10.10i, %- 10.10i, %- 10.10i, %- 10.10i, %- 10.10i, %- 10.10i", 0, 5, -1, -10, 100, -1862, INT_MIN, INT_MAX);
	/* 309 */ test_print_int_eight("%- 10.100i, %- 10.100i, %- 10.100i, %- 10.100i, %- 10.100i, %- 10.100i, %- 10.100i, %- 10.100i", 0, 5, -1, -10, 100, -1862, INT_MIN, INT_MAX);
	/* 310 */ test_print_int_eight("%- 100.i, %- 100.i, %- 100.i, %- 100.i, %- 100.i, %- 100.i, %- 100.i, %- 100.i", 0, 5, -1, -10, 100, -1862, INT_MIN, INT_MAX);
	/* 311 */ test_print_int_eight("%- 100.0i, %- 100.0i, %- 100.0i, %- 100.0i, %- 100.0i, %- 100.0i, %- 100.0i, %- 100.0i", 0, 5, -1, -10, 100, -1862, INT_MIN, INT_MAX);
	/* 312 */ test_print_int_eight("%- 100.1i, %- 100.1i, %- 100.1i, %- 100.1i, %- 100.1i, %- 100.1i, %- 100.1i, %- 100.1i", 0, 5, -1, -10, 100, -1862, INT_MIN, INT_MAX);
	/* 313 */ test_print_int_eight("%- 100.5i, %- 100.5i, %- 100.5i, %- 100.5i, %- 100.5i, %- 100.5i, %- 100.5i, %- 100.5i", 0, 5, -1, -10, 100, -1862, INT_MIN, INT_MAX);
	/* 314 */ test_print_int_eight("%- 100.10i, %- 100.10i, %- 100.10i, %- 100.10i, %- 100.10i, %- 100.10i, %- 100.10i, %- 100.10i", 0, 5, -1, -10, 100, -1862, INT_MIN, INT_MAX);
	/* 315 */ test_print_int_eight("%- 100.100i, %- 100.100i, %- 100.100i, %- 100.100i, %- 100.100i, %- 100.100i, %- 100.100i, %- 100.100i", 0, 5, -1, -10, 100, -1862, INT_MIN, INT_MAX);
}

void test_u() {
	g_current_test_id = 'u';
	/* 1 */ test_print_long_ten("%u, %u, %u, %u, %u, %u, %u, %u, %u, %u", 0, 5, -1, -10, 100, -1862, 0xABCDE, INT_MIN, INT_MAX, UINT_MAX);
	/* 2 */ test_print_long_ten("%1u, %1u, %1u, %1u, %1u, %1u, %1u, %1u, %1u, %1u", 0, 5, -1, -10, 100, -1862, 0xABCDE, INT_MIN, INT_MAX, UINT_MAX);
	/* 3 */ test_print_long_ten("%5u, %5u, %5u, %5u, %5u, %5u, %5u, %5u, %5u, %5u", 0, 5, -1, -10, 100, -1862, 0xABCDE, INT_MIN, INT_MAX, UINT_MAX);
	/* 4 */ test_print_long_ten("%10u, %10u, %10u, %10u, %10u, %10u, %10u, %10u, %10u, %10u", 0, 5, -1, -10, 100, -1862, 0xABCDE, INT_MIN, INT_MAX, UINT_MAX);
	/* 5 */ test_print_long_ten("%100u, %100u, %100u, %100u, %100u, %100u, %100u, %100u, %100u, %100u", 0, 5, -1, -10, 100, -1862, 0xABCDE, INT_MIN, INT_MAX, UINT_MAX);
	/* 6 */ test_print_long_ten("%.u, %.u, %.u, %.u, %.u, %.u, %.u, %.u, %.u, %.u", 0, 5, -1, -10, 100, -1862, 0xABCDE, INT_MIN, INT_MAX, UINT_MAX);
	/* 7 */ test_print_long_ten("%.0u, %.0u, %.0u, %.0u, %.0u, %.0u, %.0u, %.0u, %.0u, %.0u", 0, 5, -1, -10, 100, -1862, 0xABCDE, INT_MIN, INT_MAX, UINT_MAX);
	/* 8 */ test_print_long_ten("%.1u, %.1u, %.1u, %.1u, %.1u, %.1u, %.1u, %.1u, %.1u, %.1u", 0, 5, -1, -10, 100, -1862, 0xABCDE, INT_MIN, INT_MAX, UINT_MAX);
	/* 9 */ test_print_long_ten("%.5u, %.5u, %.5u, %.5u, %.5u, %.5u, %.5u, %.5u, %.5u, %.5u", 0, 5, -1, -10, 100, -1862, 0xABCDE, INT_MIN, INT_MAX, UINT_MAX);
	/* 10 */ test_print_long_ten("%.10u, %.10u, %.10u, %.10u, %.10u, %.10u, %.10u, %.10u, %.10u, %.10u", 0, 5, -1, -10, 100, -1862, 0xABCDE, INT_MIN, INT_MAX, UINT_MAX);
	/* 11 */ test_print_long_ten("%.100u, %.100u, %.100u, %.100u, %.100u, %.100u, %.100u, %.100u, %.100u, %.100u", 0, 5, -1, -10, 100, -1862, 0xABCDE, INT_MIN, INT_MAX, UINT_MAX);
	/* 12 */ test_print_long_ten("%1.u, %1.u, %1.u, %1.u, %1.u, %1.u, %1.u, %1.u, %1.u, %1.u", 0, 5, -1, -10, 100, -1862, 0xABCDE, INT_MIN, INT_MAX, UINT_MAX);
	/* 13 */ test_print_long_ten("%1.0u, %1.0u, %1.0u, %1.0u, %1.0u, %1.0u, %1.0u, %1.0u, %1.0u, %1.0u", 0, 5, -1, -10, 100, -1862, 0xABCDE, INT_MIN, INT_MAX, UINT_MAX);
	/* 14 */ test_print_long_ten("%1.1u, %1.1u, %1.1u, %1.1u, %1.1u, %1.1u, %1.1u, %1.1u, %1.1u, %1.1u", 0, 5, -1, -10, 100, -1862, 0xABCDE, INT_MIN, INT_MAX, UINT_MAX);
	/* 15 */ test_print_long_ten("%1.5u, %1.5u, %1.5u, %1.5u, %1.5u, %1.5u, %1.5u, %1.5u, %1.5u, %1.5u", 0, 5, -1, -10, 100, -1862, 0xABCDE, INT_MIN, INT_MAX, UINT_MAX);
	/* 16 */ test_print_long_ten("%1.10u, %1.10u, %1.10u, %1.10u, %1.10u, %1.10u, %1.10u, %1.10u, %1.10u, %1.10u", 0, 5, -1, -10, 100, -1862, 0xABCDE, INT_MIN, INT_MAX, UINT_MAX);
	/* 17 */ test_print_long_ten("%1.100u, %1.100u, %1.100u, %1.100u, %1.100u, %1.100u, %1.100u, %1.100u, %1.100u, %1.100u", 0, 5, -1, -10, 100, -1862, 0xABCDE, INT_MIN, INT_MAX, UINT_MAX);
	/* 18 */ test_print_long_ten("%5.u, %5.u, %5.u, %5.u, %5.u, %5.u, %5.u, %5.u, %5.u, %5.u", 0, 5, -1, -10, 100, -1862, 0xABCDE, INT_MIN, INT_MAX, UINT_MAX);
	/* 19 */ test_print_long_ten("%5.0u, %5.0u, %5.0u, %5.0u, %5.0u, %5.0u, %5.0u, %5.0u, %5.0u, %5.0u", 0, 5, -1, -10, 100, -1862, 0xABCDE, INT_MIN, INT_MAX, UINT_MAX);
	/* 20 */ test_print_long_ten("%5.1u, %5.1u, %5.1u, %5.1u, %5.1u, %5.1u, %5.1u, %5.1u, %5.1u, %5.1u", 0, 5, -1, -10, 100, -1862, 0xABCDE, INT_MIN, INT_MAX, UINT_MAX);
	/* 21 */ test_print_long_ten("%5.5u, %5.5u, %5.5u, %5.5u, %5.5u, %5.5u, %5.5u, %5.5u, %5.5u, %5.5u", 0, 5, -1, -10, 100, -1862, 0xABCDE, INT_MIN, INT_MAX, UINT_MAX);
	/* 22 */ test_print_long_ten("%5.10u, %5.10u, %5.10u, %5.10u, %5.10u, %5.10u, %5.10u, %5.10u, %5.10u, %5.10u", 0, 5, -1, -10, 100, -1862, 0xABCDE, INT_MIN, INT_MAX, UINT_MAX);
	/* 23 */ test_print_long_ten("%5.100u, %5.100u, %5.100u, %5.100u, %5.100u, %5.100u, %5.100u, %5.100u, %5.100u, %5.100u", 0, 5, -1, -10, 100, -1862, 0xABCDE, INT_MIN, INT_MAX, UINT_MAX);
	/* 24 */ test_print_long_ten("%10.u, %10.u, %10.u, %10.u, %10.u, %10.u, %10.u, %10.u, %10.u, %10.u", 0, 5, -1, -10, 100, -1862, 0xABCDE, INT_MIN, INT_MAX, UINT_MAX);
	/* 25 */ test_print_long_ten("%10.0u, %10.0u, %10.0u, %10.0u, %10.0u, %10.0u, %10.0u, %10.0u, %10.0u, %10.0u", 0, 5, -1, -10, 100, -1862, 0xABCDE, INT_MIN, INT_MAX, UINT_MAX);
	/* 26 */ test_print_long_ten("%10.1u, %10.1u, %10.1u, %10.1u, %10.1u, %10.1u, %10.1u, %10.1u, %10.1u, %10.1u", 0, 5, -1, -10, 100, -1862, 0xABCDE, INT_MIN, INT_MAX, UINT_MAX);
	/* 27 */ test_print_long_ten("%10.5u, %10.5u, %10.5u, %10.5u, %10.5u, %10.5u, %10.5u, %10.5u, %10.5u, %10.5u", 0, 5, -1, -10, 100, -1862, 0xABCDE, INT_MIN, INT_MAX, UINT_MAX);
	/* 28 */ test_print_long_ten("%10.10u, %10.10u, %10.10u, %10.10u, %10.10u, %10.10u, %10.10u, %10.10u, %10.10u, %10.10u", 0, 5, -1, -10, 100, -1862, 0xABCDE, INT_MIN, INT_MAX, UINT_MAX);
	/* 29 */ test_print_long_ten("%10.100u, %10.100u, %10.100u, %10.100u, %10.100u, %10.100u, %10.100u, %10.100u, %10.100u, %10.100u", 0, 5, -1, -10, 100, -1862, 0xABCDE, INT_MIN, INT_MAX, UINT_MAX);
	/* 30 */ test_print_long_ten("%100.u, %100.u, %100.u, %100.u, %100.u, %100.u, %100.u, %100.u, %100.u, %100.u", 0, 5, -1, -10, 100, -1862, 0xABCDE, INT_MIN, INT_MAX, UINT_MAX);
	/* 31 */ test_print_long_ten("%100.0u, %100.0u, %100.0u, %100.0u, %100.0u, %100.0u, %100.0u, %100.0u, %100.0u, %100.0u", 0, 5, -1, -10, 100, -1862, 0xABCDE, INT_MIN, INT_MAX, UINT_MAX);
	/* 32 */ test_print_long_ten("%100.1u, %100.1u, %100.1u, %100.1u, %100.1u, %100.1u, %100.1u, %100.1u, %100.1u, %100.1u", 0, 5, -1, -10, 100, -1862, 0xABCDE, INT_MIN, INT_MAX, UINT_MAX);
	/* 33 */ test_print_long_ten("%100.5u, %100.5u, %100.5u, %100.5u, %100.5u, %100.5u, %100.5u, %100.5u, %100.5u, %100.5u", 0, 5, -1, -10, 100, -1862, 0xABCDE, INT_MIN, INT_MAX, UINT_MAX);
	/* 34 */ test_print_long_ten("%100.10u, %100.10u, %100.10u, %100.10u, %100.10u, %100.10u, %100.10u, %100.10u, %100.10u, %100.10u", 0, 5, -1, -10, 100, -1862, 0xABCDE, INT_MIN, INT_MAX, UINT_MAX);
	/* 35 */ test_print_long_ten("%100.100u, %100.100u, %100.100u, %100.100u, %100.100u, %100.100u, %100.100u, %100.100u, %100.100u, %100.100u", 0, 5, -1, -10, 100, -1862, 0xABCDE, INT_MIN, INT_MAX, UINT_MAX);
	/* 36 */ test_print_long_ten("%0u, %0u, %0u, %0u, %0u, %0u, %0u, %0u, %0u, %0u", 0, 5, -1, -10, 100, -1862, 0xABCDE, INT_MIN, INT_MAX, UINT_MAX);
	/* 37 */ test_print_long_ten("%01u, %01u, %01u, %01u, %01u, %01u, %01u, %01u, %01u, %01u", 0, 5, -1, -10, 100, -1862, 0xABCDE, INT_MIN, INT_MAX, UINT_MAX);
	/* 38 */ test_print_long_ten("%05u, %05u, %05u, %05u, %05u, %05u, %05u, %05u, %05u, %05u", 0, 5, -1, -10, 100, -1862, 0xABCDE, INT_MIN, INT_MAX, UINT_MAX);
	/* 39 */ test_print_long_ten("%010u, %010u, %010u, %010u, %010u, %010u, %010u, %010u, %010u, %010u", 0, 5, -1, -10, 100, -1862, 0xABCDE, INT_MIN, INT_MAX, UINT_MAX);
	/* 40 */ test_print_long_ten("%0100u, %0100u, %0100u, %0100u, %0100u, %0100u, %0100u, %0100u, %0100u, %0100u", 0, 5, -1, -10, 100, -1862, 0xABCDE, INT_MIN, INT_MAX, UINT_MAX);
	/* 41 */ test_print_long_ten("%0.u, %0.u, %0.u, %0.u, %0.u, %0.u, %0.u, %0.u, %0.u, %0.u", 0, 5, -1, -10, 100, -1862, 0xABCDE, INT_MIN, INT_MAX, UINT_MAX);
	/* 42 */ test_print_long_ten("%0.0u, %0.0u, %0.0u, %0.0u, %0.0u, %0.0u, %0.0u, %0.0u, %0.0u, %0.0u", 0, 5, -1, -10, 100, -1862, 0xABCDE, INT_MIN, INT_MAX, UINT_MAX);
	/* 43 */ test_print_long_ten("%0.1u, %0.1u, %0.1u, %0.1u, %0.1u, %0.1u, %0.1u, %0.1u, %0.1u, %0.1u", 0, 5, -1, -10, 100, -1862, 0xABCDE, INT_MIN, INT_MAX, UINT_MAX);
	/* 44 */ test_print_long_ten("%0.5u, %0.5u, %0.5u, %0.5u, %0.5u, %0.5u, %0.5u, %0.5u, %0.5u, %0.5u", 0, 5, -1, -10, 100, -1862, 0xABCDE, INT_MIN, INT_MAX, UINT_MAX);
	/* 45 */ test_print_long_ten("%0.10u, %0.10u, %0.10u, %0.10u, %0.10u, %0.10u, %0.10u, %0.10u, %0.10u, %0.10u", 0, 5, -1, -10, 100, -1862, 0xABCDE, INT_MIN, INT_MAX, UINT_MAX);
	/* 46 */ test_print_long_ten("%0.100u, %0.100u, %0.100u, %0.100u, %0.100u, %0.100u, %0.100u, %0.100u, %0.100u, %0.100u", 0, 5, -1, -10, 100, -1862, 0xABCDE, INT_MIN, INT_MAX, UINT_MAX);
	/* 47 */ test_print_long_ten("%01.u, %01.u, %01.u, %01.u, %01.u, %01.u, %01.u, %01.u, %01.u, %01.u", 0, 5, -1, -10, 100, -1862, 0xABCDE, INT_MIN, INT_MAX, UINT_MAX);
	/* 48 */ test_print_long_ten("%01.0u, %01.0u, %01.0u, %01.0u, %01.0u, %01.0u, %01.0u, %01.0u, %01.0u, %01.0u", 0, 5, -1, -10, 100, -1862, 0xABCDE, INT_MIN, INT_MAX, UINT_MAX);
	/* 49 */ test_print_long_ten("%01.1u, %01.1u, %01.1u, %01.1u, %01.1u, %01.1u, %01.1u, %01.1u, %01.1u, %01.1u", 0, 5, -1, -10, 100, -1862, 0xABCDE, INT_MIN, INT_MAX, UINT_MAX);
	/* 50 */ test_print_long_ten("%01.5u, %01.5u, %01.5u, %01.5u, %01.5u, %01.5u, %01.5u, %01.5u, %01.5u, %01.5u", 0, 5, -1, -10, 100, -1862, 0xABCDE, INT_MIN, INT_MAX, UINT_MAX);
	/* 51 */ test_print_long_ten("%01.10u, %01.10u, %01.10u, %01.10u, %01.10u, %01.10u, %01.10u, %01.10u, %01.10u, %01.10u", 0, 5, -1, -10, 100, -1862, 0xABCDE, INT_MIN, INT_MAX, UINT_MAX);
	/* 52 */ test_print_long_ten("%01.100u, %01.100u, %01.100u, %01.100u, %01.100u, %01.100u, %01.100u, %01.100u, %01.100u, %01.100u", 0, 5, -1, -10, 100, -1862, 0xABCDE, INT_MIN, INT_MAX, UINT_MAX);
	/* 53 */ test_print_long_ten("%05.u, %05.u, %05.u, %05.u, %05.u, %05.u, %05.u, %05.u, %05.u, %05.u", 0, 5, -1, -10, 100, -1862, 0xABCDE, INT_MIN, INT_MAX, UINT_MAX);
	/* 54 */ test_print_long_ten("%05.0u, %05.0u, %05.0u, %05.0u, %05.0u, %05.0u, %05.0u, %05.0u, %05.0u, %05.0u", 0, 5, -1, -10, 100, -1862, 0xABCDE, INT_MIN, INT_MAX, UINT_MAX);
	/* 55 */ test_print_long_ten("%05.1u, %05.1u, %05.1u, %05.1u, %05.1u, %05.1u, %05.1u, %05.1u, %05.1u, %05.1u", 0, 5, -1, -10, 100, -1862, 0xABCDE, INT_MIN, INT_MAX, UINT_MAX);
	/* 56 */ test_print_long_ten("%05.5u, %05.5u, %05.5u, %05.5u, %05.5u, %05.5u, %05.5u, %05.5u, %05.5u, %05.5u", 0, 5, -1, -10, 100, -1862, 0xABCDE, INT_MIN, INT_MAX, UINT_MAX);
	/* 57 */ test_print_long_ten("%05.10u, %05.10u, %05.10u, %05.10u, %05.10u, %05.10u, %05.10u, %05.10u, %05.10u, %05.10u", 0, 5, -1, -10, 100, -1862, 0xABCDE, INT_MIN, INT_MAX, UINT_MAX);
	/* 58 */ test_print_long_ten("%05.100u, %05.100u, %05.100u, %05.100u, %05.100u, %05.100u, %05.100u, %05.100u, %05.100u, %05.100u", 0, 5, -1, -10, 100, -1862, 0xABCDE, INT_MIN, INT_MAX, UINT_MAX);
	/* 59 */ test_print_long_ten("%010.u, %010.u, %010.u, %010.u, %010.u, %010.u, %010.u, %010.u, %010.u, %010.u", 0, 5, -1, -10, 100, -1862, 0xABCDE, INT_MIN, INT_MAX, UINT_MAX);
	/* 60 */ test_print_long_ten("%010.0u, %010.0u, %010.0u, %010.0u, %010.0u, %010.0u, %010.0u, %010.0u, %010.0u, %010.0u", 0, 5, -1, -10, 100, -1862, 0xABCDE, INT_MIN, INT_MAX, UINT_MAX);
	/* 61 */ test_print_long_ten("%010.1u, %010.1u, %010.1u, %010.1u, %010.1u, %010.1u, %010.1u, %010.1u, %010.1u, %010.1u", 0, 5, -1, -10, 100, -1862, 0xABCDE, INT_MIN, INT_MAX, UINT_MAX);
	/* 62 */ test_print_long_ten("%010.5u, %010.5u, %010.5u, %010.5u, %010.5u, %010.5u, %010.5u, %010.5u, %010.5u, %010.5u", 0, 5, -1, -10, 100, -1862, 0xABCDE, INT_MIN, INT_MAX, UINT_MAX);
	/* 63 */ test_print_long_ten("%010.10u, %010.10u, %010.10u, %010.10u, %010.10u, %010.10u, %010.10u, %010.10u, %010.10u, %010.10u", 0, 5, -1, -10, 100, -1862, 0xABCDE, INT_MIN, INT_MAX, UINT_MAX);
	/* 64 */ test_print_long_ten("%010.100u, %010.100u, %010.100u, %010.100u, %010.100u, %010.100u, %010.100u, %010.100u, %010.100u, %010.100u", 0, 5, -1, -10, 100, -1862, 0xABCDE, INT_MIN, INT_MAX, UINT_MAX);
	/* 65 */ test_print_long_ten("%0100.u, %0100.u, %0100.u, %0100.u, %0100.u, %0100.u, %0100.u, %0100.u, %0100.u, %0100.u", 0, 5, -1, -10, 100, -1862, 0xABCDE, INT_MIN, INT_MAX, UINT_MAX);
	/* 66 */ test_print_long_ten("%0100.0u, %0100.0u, %0100.0u, %0100.0u, %0100.0u, %0100.0u, %0100.0u, %0100.0u, %0100.0u, %0100.0u", 0, 5, -1, -10, 100, -1862, 0xABCDE, INT_MIN, INT_MAX, UINT_MAX);
	/* 67 */ test_print_long_ten("%0100.1u, %0100.1u, %0100.1u, %0100.1u, %0100.1u, %0100.1u, %0100.1u, %0100.1u, %0100.1u, %0100.1u", 0, 5, -1, -10, 100, -1862, 0xABCDE, INT_MIN, INT_MAX, UINT_MAX);
	/* 68 */ test_print_long_ten("%0100.5u, %0100.5u, %0100.5u, %0100.5u, %0100.5u, %0100.5u, %0100.5u, %0100.5u, %0100.5u, %0100.5u", 0, 5, -1, -10, 100, -1862, 0xABCDE, INT_MIN, INT_MAX, UINT_MAX);
	/* 69 */ test_print_long_ten("%0100.10u, %0100.10u, %0100.10u, %0100.10u, %0100.10u, %0100.10u, %0100.10u, %0100.10u, %0100.10u, %0100.10u", 0, 5, -1, -10, 100, -1862, 0xABCDE, INT_MIN, INT_MAX, UINT_MAX);
	/* 70 */ test_print_long_ten("%0100.100u, %0100.100u, %0100.100u, %0100.100u, %0100.100u, %0100.100u, %0100.100u, %0100.100u, %0100.100u, %0100.100u", 0, 5, -1, -10, 100, -1862, 0xABCDE, INT_MIN, INT_MAX, UINT_MAX);
	/* 71 */ test_print_long_ten("%-u, %-u, %-u, %-u, %-u, %-u, %-u, %-u, %-u, %-u", 0, 5, -1, -10, 100, -1862, 0xABCDE, INT_MIN, INT_MAX, UINT_MAX);
	/* 72 */ test_print_long_ten("%-1u, %-1u, %-1u, %-1u, %-1u, %-1u, %-1u, %-1u, %-1u, %-1u", 0, 5, -1, -10, 100, -1862, 0xABCDE, INT_MIN, INT_MAX, UINT_MAX);
	/* 73 */ test_print_long_ten("%-5u, %-5u, %-5u, %-5u, %-5u, %-5u, %-5u, %-5u, %-5u, %-5u", 0, 5, -1, -10, 100, -1862, 0xABCDE, INT_MIN, INT_MAX, UINT_MAX);
	/* 74 */ test_print_long_ten("%-10u, %-10u, %-10u, %-10u, %-10u, %-10u, %-10u, %-10u, %-10u, %-10u", 0, 5, -1, -10, 100, -1862, 0xABCDE, INT_MIN, INT_MAX, UINT_MAX);
	/* 75 */ test_print_long_ten("%-100u, %-100u, %-100u, %-100u, %-100u, %-100u, %-100u, %-100u, %-100u, %-100u", 0, 5, -1, -10, 100, -1862, 0xABCDE, INT_MIN, INT_MAX, UINT_MAX);
	/* 76 */ test_print_long_ten("%-.u, %-.u, %-.u, %-.u, %-.u, %-.u, %-.u, %-.u, %-.u, %-.u", 0, 5, -1, -10, 100, -1862, 0xABCDE, INT_MIN, INT_MAX, UINT_MAX);
	/* 77 */ test_print_long_ten("%-.0u, %-.0u, %-.0u, %-.0u, %-.0u, %-.0u, %-.0u, %-.0u, %-.0u, %-.0u", 0, 5, -1, -10, 100, -1862, 0xABCDE, INT_MIN, INT_MAX, UINT_MAX);
	/* 78 */ test_print_long_ten("%-.1u, %-.1u, %-.1u, %-.1u, %-.1u, %-.1u, %-.1u, %-.1u, %-.1u, %-.1u", 0, 5, -1, -10, 100, -1862, 0xABCDE, INT_MIN, INT_MAX, UINT_MAX);
	/* 79 */ test_print_long_ten("%-.5u, %-.5u, %-.5u, %-.5u, %-.5u, %-.5u, %-.5u, %-.5u, %-.5u, %-.5u", 0, 5, -1, -10, 100, -1862, 0xABCDE, INT_MIN, INT_MAX, UINT_MAX);
	/* 80 */ test_print_long_ten("%-.10u, %-.10u, %-.10u, %-.10u, %-.10u, %-.10u, %-.10u, %-.10u, %-.10u, %-.10u", 0, 5, -1, -10, 100, -1862, 0xABCDE, INT_MIN, INT_MAX, UINT_MAX);
	/* 81 */ test_print_long_ten("%-.100u, %-.100u, %-.100u, %-.100u, %-.100u, %-.100u, %-.100u, %-.100u, %-.100u, %-.100u", 0, 5, -1, -10, 100, -1862, 0xABCDE, INT_MIN, INT_MAX, UINT_MAX);
	/* 82 */ test_print_long_ten("%-1.u, %-1.u, %-1.u, %-1.u, %-1.u, %-1.u, %-1.u, %-1.u, %-1.u, %-1.u", 0, 5, -1, -10, 100, -1862, 0xABCDE, INT_MIN, INT_MAX, UINT_MAX);
	/* 83 */ test_print_long_ten("%-1.0u, %-1.0u, %-1.0u, %-1.0u, %-1.0u, %-1.0u, %-1.0u, %-1.0u, %-1.0u, %-1.0u", 0, 5, -1, -10, 100, -1862, 0xABCDE, INT_MIN, INT_MAX, UINT_MAX);
	/* 84 */ test_print_long_ten("%-1.1u, %-1.1u, %-1.1u, %-1.1u, %-1.1u, %-1.1u, %-1.1u, %-1.1u, %-1.1u, %-1.1u", 0, 5, -1, -10, 100, -1862, 0xABCDE, INT_MIN, INT_MAX, UINT_MAX);
	/* 85 */ test_print_long_ten("%-1.5u, %-1.5u, %-1.5u, %-1.5u, %-1.5u, %-1.5u, %-1.5u, %-1.5u, %-1.5u, %-1.5u", 0, 5, -1, -10, 100, -1862, 0xABCDE, INT_MIN, INT_MAX, UINT_MAX);
	/* 86 */ test_print_long_ten("%-1.10u, %-1.10u, %-1.10u, %-1.10u, %-1.10u, %-1.10u, %-1.10u, %-1.10u, %-1.10u, %-1.10u", 0, 5, -1, -10, 100, -1862, 0xABCDE, INT_MIN, INT_MAX, UINT_MAX);
	/* 87 */ test_print_long_ten("%-1.100u, %-1.100u, %-1.100u, %-1.100u, %-1.100u, %-1.100u, %-1.100u, %-1.100u, %-1.100u, %-1.100u", 0, 5, -1, -10, 100, -1862, 0xABCDE, INT_MIN, INT_MAX, UINT_MAX);
	/* 88 */ test_print_long_ten("%-5.u, %-5.u, %-5.u, %-5.u, %-5.u, %-5.u, %-5.u, %-5.u, %-5.u, %-5.u", 0, 5, -1, -10, 100, -1862, 0xABCDE, INT_MIN, INT_MAX, UINT_MAX);
	/* 89 */ test_print_long_ten("%-5.0u, %-5.0u, %-5.0u, %-5.0u, %-5.0u, %-5.0u, %-5.0u, %-5.0u, %-5.0u, %-5.0u", 0, 5, -1, -10, 100, -1862, 0xABCDE, INT_MIN, INT_MAX, UINT_MAX);
	/* 90 */ test_print_long_ten("%-5.1u, %-5.1u, %-5.1u, %-5.1u, %-5.1u, %-5.1u, %-5.1u, %-5.1u, %-5.1u, %-5.1u", 0, 5, -1, -10, 100, -1862, 0xABCDE, INT_MIN, INT_MAX, UINT_MAX);
	/* 91 */ test_print_long_ten("%-5.5u, %-5.5u, %-5.5u, %-5.5u, %-5.5u, %-5.5u, %-5.5u, %-5.5u, %-5.5u, %-5.5u", 0, 5, -1, -10, 100, -1862, 0xABCDE, INT_MIN, INT_MAX, UINT_MAX);
	/* 92 */ test_print_long_ten("%-5.10u, %-5.10u, %-5.10u, %-5.10u, %-5.10u, %-5.10u, %-5.10u, %-5.10u, %-5.10u, %-5.10u", 0, 5, -1, -10, 100, -1862, 0xABCDE, INT_MIN, INT_MAX, UINT_MAX);
	/* 93 */ test_print_long_ten("%-5.100u, %-5.100u, %-5.100u, %-5.100u, %-5.100u, %-5.100u, %-5.100u, %-5.100u, %-5.100u, %-5.100u", 0, 5, -1, -10, 100, -1862, 0xABCDE, INT_MIN, INT_MAX, UINT_MAX);
	/* 94 */ test_print_long_ten("%-10.u, %-10.u, %-10.u, %-10.u, %-10.u, %-10.u, %-10.u, %-10.u, %-10.u, %-10.u", 0, 5, -1, -10, 100, -1862, 0xABCDE, INT_MIN, INT_MAX, UINT_MAX);
	/* 95 */ test_print_long_ten("%-10.0u, %-10.0u, %-10.0u, %-10.0u, %-10.0u, %-10.0u, %-10.0u, %-10.0u, %-10.0u, %-10.0u", 0, 5, -1, -10, 100, -1862, 0xABCDE, INT_MIN, INT_MAX, UINT_MAX);
	/* 96 */ test_print_long_ten("%-10.1u, %-10.1u, %-10.1u, %-10.1u, %-10.1u, %-10.1u, %-10.1u, %-10.1u, %-10.1u, %-10.1u", 0, 5, -1, -10, 100, -1862, 0xABCDE, INT_MIN, INT_MAX, UINT_MAX);
	/* 97 */ test_print_long_ten("%-10.5u, %-10.5u, %-10.5u, %-10.5u, %-10.5u, %-10.5u, %-10.5u, %-10.5u, %-10.5u, %-10.5u", 0, 5, -1, -10, 100, -1862, 0xABCDE, INT_MIN, INT_MAX, UINT_MAX);
	/* 98 */ test_print_long_ten("%-10.10u, %-10.10u, %-10.10u, %-10.10u, %-10.10u, %-10.10u, %-10.10u, %-10.10u, %-10.10u, %-10.10u", 0, 5, -1, -10, 100, -1862, 0xABCDE, INT_MIN, INT_MAX, UINT_MAX);
	/* 99 */ test_print_long_ten("%-10.100u, %-10.100u, %-10.100u, %-10.100u, %-10.100u, %-10.100u, %-10.100u, %-10.100u, %-10.100u, %-10.100u", 0, 5, -1, -10, 100, -1862, 0xABCDE, INT_MIN, INT_MAX, UINT_MAX);
	/* 100 */ test_print_long_ten("%-100.u, %-100.u, %-100.u, %-100.u, %-100.u, %-100.u, %-100.u, %-100.u, %-100.u, %-100.u", 0, 5, -1, -10, 100, -1862, 0xABCDE, INT_MIN, INT_MAX, UINT_MAX);
	/* 101 */ test_print_long_ten("%-100.0u, %-100.0u, %-100.0u, %-100.0u, %-100.0u, %-100.0u, %-100.0u, %-100.0u, %-100.0u, %-100.0u", 0, 5, -1, -10, 100, -1862, 0xABCDE, INT_MIN, INT_MAX, UINT_MAX);
	/* 102 */ test_print_long_ten("%-100.1u, %-100.1u, %-100.1u, %-100.1u, %-100.1u, %-100.1u, %-100.1u, %-100.1u, %-100.1u, %-100.1u", 0, 5, -1, -10, 100, -1862, 0xABCDE, INT_MIN, INT_MAX, UINT_MAX);
	/* 103 */ test_print_long_ten("%-100.5u, %-100.5u, %-100.5u, %-100.5u, %-100.5u, %-100.5u, %-100.5u, %-100.5u, %-100.5u, %-100.5u", 0, 5, -1, -10, 100, -1862, 0xABCDE, INT_MIN, INT_MAX, UINT_MAX);
	/* 104 */ test_print_long_ten("%-100.10u, %-100.10u, %-100.10u, %-100.10u, %-100.10u, %-100.10u, %-100.10u, %-100.10u, %-100.10u, %-100.10u", 0, 5, -1, -10, 100, -1862, 0xABCDE, INT_MIN, INT_MAX, UINT_MAX);
	/* 105 */ test_print_long_ten("%-100.100u, %-100.100u, %-100.100u, %-100.100u, %-100.100u, %-100.100u, %-100.100u, %-100.100u, %-100.100u, %-100.100u", 0, 5, -1, -10, 100, -1862, 0xABCDE, INT_MIN, INT_MAX, UINT_MAX);
}

void test_x() {
	g_current_test_id = 'x';
	/* 1 */ test_print_long_ten("%x, %x, %x, %x, %x, %x, %x, %x, %x, %x", 0, 5, -1, -10, 0x1234, -1862, 0xABCDE, INT_MIN, INT_MAX, UINT_MAX);
	/* 2 */ test_print_long_ten("%1x, %1x, %1x, %1x, %1x, %1x, %1x, %1x, %1x, %1x", 0, 5, -1, -10, 0x1234, -1862, 0xABCDE, INT_MIN, INT_MAX, UINT_MAX);
	/* 3 */ test_print_long_ten("%5x, %5x, %5x, %5x, %5x, %5x, %5x, %5x, %5x, %5x", 0, 5, -1, -10, 0x1234, -1862, 0xABCDE, INT_MIN, INT_MAX, UINT_MAX);
	/* 4 */ test_print_long_ten("%10x, %10x, %10x, %10x, %10x, %10x, %10x, %10x, %10x, %10x", 0, 5, -1, -10, 0x1234, -1862, 0xABCDE, INT_MIN, INT_MAX, UINT_MAX);
	/* 5 */ test_print_long_ten("%100x, %100x, %100x, %100x, %100x, %100x, %100x, %100x, %100x, %100x", 0, 5, -1, -10, 0x1234, -1862, 0xABCDE, INT_MIN, INT_MAX, UINT_MAX);
	/* 6 */ test_print_long_ten("%.x, %.x, %.x, %.x, %.x, %.x, %.x, %.x, %.x, %.x", 0, 5, -1, -10, 0x1234, -1862, 0xABCDE, INT_MIN, INT_MAX, UINT_MAX);
	/* 7 */ test_print_long_ten("%.0x, %.0x, %.0x, %.0x, %.0x, %.0x, %.0x, %.0x, %.0x, %.0x", 0, 5, -1, -10, 0x1234, -1862, 0xABCDE, INT_MIN, INT_MAX, UINT_MAX);
	/* 8 */ test_print_long_ten("%.1x, %.1x, %.1x, %.1x, %.1x, %.1x, %.1x, %.1x, %.1x, %.1x", 0, 5, -1, -10, 0x1234, -1862, 0xABCDE, INT_MIN, INT_MAX, UINT_MAX);
	/* 9 */ test_print_long_ten("%.5x, %.5x, %.5x, %.5x, %.5x, %.5x, %.5x, %.5x, %.5x, %.5x", 0, 5, -1, -10, 0x1234, -1862, 0xABCDE, INT_MIN, INT_MAX, UINT_MAX);
	/* 10 */ test_print_long_ten("%.10x, %.10x, %.10x, %.10x, %.10x, %.10x, %.10x, %.10x, %.10x, %.10x", 0, 5, -1, -10, 0x1234, -1862, 0xABCDE, INT_MIN, INT_MAX, UINT_MAX);
	/* 11 */ test_print_long_ten("%.100x, %.100x, %.100x, %.100x, %.100x, %.100x, %.100x, %.100x, %.100x, %.100x", 0, 5, -1, -10, 0x1234, -1862, 0xABCDE, INT_MIN, INT_MAX, UINT_MAX);
	/* 12 */ test_print_long_ten("%1.x, %1.x, %1.x, %1.x, %1.x, %1.x, %1.x, %1.x, %1.x, %1.x", 0, 5, -1, -10, 0x1234, -1862, 0xABCDE, INT_MIN, INT_MAX, UINT_MAX);
	/* 13 */ test_print_long_ten("%1.0x, %1.0x, %1.0x, %1.0x, %1.0x, %1.0x, %1.0x, %1.0x, %1.0x, %1.0x", 0, 5, -1, -10, 0x1234, -1862, 0xABCDE, INT_MIN, INT_MAX, UINT_MAX);
	/* 14 */ test_print_long_ten("%1.1x, %1.1x, %1.1x, %1.1x, %1.1x, %1.1x, %1.1x, %1.1x, %1.1x, %1.1x", 0, 5, -1, -10, 0x1234, -1862, 0xABCDE, INT_MIN, INT_MAX, UINT_MAX);
	/* 15 */ test_print_long_ten("%1.5x, %1.5x, %1.5x, %1.5x, %1.5x, %1.5x, %1.5x, %1.5x, %1.5x, %1.5x", 0, 5, -1, -10, 0x1234, -1862, 0xABCDE, INT_MIN, INT_MAX, UINT_MAX);
	/* 16 */ test_print_long_ten("%1.10x, %1.10x, %1.10x, %1.10x, %1.10x, %1.10x, %1.10x, %1.10x, %1.10x, %1.10x", 0, 5, -1, -10, 0x1234, -1862, 0xABCDE, INT_MIN, INT_MAX, UINT_MAX);
	/* 17 */ test_print_long_ten("%1.100x, %1.100x, %1.100x, %1.100x, %1.100x, %1.100x, %1.100x, %1.100x, %1.100x, %1.100x", 0, 5, -1, -10, 0x1234, -1862, 0xABCDE, INT_MIN, INT_MAX, UINT_MAX);
	/* 18 */ test_print_long_ten("%5.x, %5.x, %5.x, %5.x, %5.x, %5.x, %5.x, %5.x, %5.x, %5.x", 0, 5, -1, -10, 0x1234, -1862, 0xABCDE, INT_MIN, INT_MAX, UINT_MAX);
	/* 19 */ test_print_long_ten("%5.0x, %5.0x, %5.0x, %5.0x, %5.0x, %5.0x, %5.0x, %5.0x, %5.0x, %5.0x", 0, 5, -1, -10, 0x1234, -1862, 0xABCDE, INT_MIN, INT_MAX, UINT_MAX);
	/* 20 */ test_print_long_ten("%5.1x, %5.1x, %5.1x, %5.1x, %5.1x, %5.1x, %5.1x, %5.1x, %5.1x, %5.1x", 0, 5, -1, -10, 0x1234, -1862, 0xABCDE, INT_MIN, INT_MAX, UINT_MAX);
	/* 21 */ test_print_long_ten("%5.5x, %5.5x, %5.5x, %5.5x, %5.5x, %5.5x, %5.5x, %5.5x, %5.5x, %5.5x", 0, 5, -1, -10, 0x1234, -1862, 0xABCDE, INT_MIN, INT_MAX, UINT_MAX);
	/* 22 */ test_print_long_ten("%5.10x, %5.10x, %5.10x, %5.10x, %5.10x, %5.10x, %5.10x, %5.10x, %5.10x, %5.10x", 0, 5, -1, -10, 0x1234, -1862, 0xABCDE, INT_MIN, INT_MAX, UINT_MAX);
	/* 23 */ test_print_long_ten("%5.100x, %5.100x, %5.100x, %5.100x, %5.100x, %5.100x, %5.100x, %5.100x, %5.100x, %5.100x", 0, 5, -1, -10, 0x1234, -1862, 0xABCDE, INT_MIN, INT_MAX, UINT_MAX);
	/* 24 */ test_print_long_ten("%10.x, %10.x, %10.x, %10.x, %10.x, %10.x, %10.x, %10.x, %10.x, %10.x", 0, 5, -1, -10, 0x1234, -1862, 0xABCDE, INT_MIN, INT_MAX, UINT_MAX);
	/* 25 */ test_print_long_ten("%10.0x, %10.0x, %10.0x, %10.0x, %10.0x, %10.0x, %10.0x, %10.0x, %10.0x, %10.0x", 0, 5, -1, -10, 0x1234, -1862, 0xABCDE, INT_MIN, INT_MAX, UINT_MAX);
	/* 26 */ test_print_long_ten("%10.1x, %10.1x, %10.1x, %10.1x, %10.1x, %10.1x, %10.1x, %10.1x, %10.1x, %10.1x", 0, 5, -1, -10, 0x1234, -1862, 0xABCDE, INT_MIN, INT_MAX, UINT_MAX);
	/* 27 */ test_print_long_ten("%10.5x, %10.5x, %10.5x, %10.5x, %10.5x, %10.5x, %10.5x, %10.5x, %10.5x, %10.5x", 0, 5, -1, -10, 0x1234, -1862, 0xABCDE, INT_MIN, INT_MAX, UINT_MAX);
	/* 28 */ test_print_long_ten("%10.10x, %10.10x, %10.10x, %10.10x, %10.10x, %10.10x, %10.10x, %10.10x, %10.10x, %10.10x", 0, 5, -1, -10, 0x1234, -1862, 0xABCDE, INT_MIN, INT_MAX, UINT_MAX);
	/* 29 */ test_print_long_ten("%10.100x, %10.100x, %10.100x, %10.100x, %10.100x, %10.100x, %10.100x, %10.100x, %10.100x, %10.100x", 0, 5, -1, -10, 0x1234, -1862, 0xABCDE, INT_MIN, INT_MAX, UINT_MAX);
	/* 30 */ test_print_long_ten("%100.x, %100.x, %100.x, %100.x, %100.x, %100.x, %100.x, %100.x, %100.x, %100.x", 0, 5, -1, -10, 0x1234, -1862, 0xABCDE, INT_MIN, INT_MAX, UINT_MAX);
	/* 31 */ test_print_long_ten("%100.0x, %100.0x, %100.0x, %100.0x, %100.0x, %100.0x, %100.0x, %100.0x, %100.0x, %100.0x", 0, 5, -1, -10, 0x1234, -1862, 0xABCDE, INT_MIN, INT_MAX, UINT_MAX);
	/* 32 */ test_print_long_ten("%100.1x, %100.1x, %100.1x, %100.1x, %100.1x, %100.1x, %100.1x, %100.1x, %100.1x, %100.1x", 0, 5, -1, -10, 0x1234, -1862, 0xABCDE, INT_MIN, INT_MAX, UINT_MAX);
	/* 33 */ test_print_long_ten("%100.5x, %100.5x, %100.5x, %100.5x, %100.5x, %100.5x, %100.5x, %100.5x, %100.5x, %100.5x", 0, 5, -1, -10, 0x1234, -1862, 0xABCDE, INT_MIN, INT_MAX, UINT_MAX);
	/* 34 */ test_print_long_ten("%100.10x, %100.10x, %100.10x, %100.10x, %100.10x, %100.10x, %100.10x, %100.10x, %100.10x, %100.10x", 0, 5, -1, -10, 0x1234, -1862, 0xABCDE, INT_MIN, INT_MAX, UINT_MAX);
	/* 35 */ test_print_long_ten("%100.100x, %100.100x, %100.100x, %100.100x, %100.100x, %100.100x, %100.100x, %100.100x, %100.100x, %100.100x", 0, 5, -1, -10, 0x1234, -1862, 0xABCDE, INT_MIN, INT_MAX, UINT_MAX);
	/* 36 */ test_print_long_ten("%#x, %#x, %#x, %#x, %#x, %#x, %#x, %#x, %#x, %#x", 0, 5, -1, -10, 0x1234, -1862, 0xABCDE, INT_MIN, INT_MAX, UINT_MAX);
	/* 37 */ test_print_long_ten("%#1x, %#1x, %#1x, %#1x, %#1x, %#1x, %#1x, %#1x, %#1x, %#1x", 0, 5, -1, -10, 0x1234, -1862, 0xABCDE, INT_MIN, INT_MAX, UINT_MAX);
	/* 38 */ test_print_long_ten("%#5x, %#5x, %#5x, %#5x, %#5x, %#5x, %#5x, %#5x, %#5x, %#5x", 0, 5, -1, -10, 0x1234, -1862, 0xABCDE, INT_MIN, INT_MAX, UINT_MAX);
	/* 39 */ test_print_long_ten("%#10x, %#10x, %#10x, %#10x, %#10x, %#10x, %#10x, %#10x, %#10x, %#10x", 0, 5, -1, -10, 0x1234, -1862, 0xABCDE, INT_MIN, INT_MAX, UINT_MAX);
	/* 40 */ test_print_long_ten("%#100x, %#100x, %#100x, %#100x, %#100x, %#100x, %#100x, %#100x, %#100x, %#100x", 0, 5, -1, -10, 0x1234, -1862, 0xABCDE, INT_MIN, INT_MAX, UINT_MAX);
	/* 41 */ test_print_long_ten("%#.x, %#.x, %#.x, %#.x, %#.x, %#.x, %#.x, %#.x, %#.x, %#.x", 0, 5, -1, -10, 0x1234, -1862, 0xABCDE, INT_MIN, INT_MAX, UINT_MAX);
	/* 42 */ test_print_long_ten("%#.0x, %#.0x, %#.0x, %#.0x, %#.0x, %#.0x, %#.0x, %#.0x, %#.0x, %#.0x", 0, 5, -1, -10, 0x1234, -1862, 0xABCDE, INT_MIN, INT_MAX, UINT_MAX);
	/* 43 */ test_print_long_ten("%#.1x, %#.1x, %#.1x, %#.1x, %#.1x, %#.1x, %#.1x, %#.1x, %#.1x, %#.1x", 0, 5, -1, -10, 0x1234, -1862, 0xABCDE, INT_MIN, INT_MAX, UINT_MAX);
	/* 44 */ test_print_long_ten("%#.5x, %#.5x, %#.5x, %#.5x, %#.5x, %#.5x, %#.5x, %#.5x, %#.5x, %#.5x", 0, 5, -1, -10, 0x1234, -1862, 0xABCDE, INT_MIN, INT_MAX, UINT_MAX);
	/* 45 */ test_print_long_ten("%#.10x, %#.10x, %#.10x, %#.10x, %#.10x, %#.10x, %#.10x, %#.10x, %#.10x, %#.10x", 0, 5, -1, -10, 0x1234, -1862, 0xABCDE, INT_MIN, INT_MAX, UINT_MAX);
	/* 46 */ test_print_long_ten("%#.100x, %#.100x, %#.100x, %#.100x, %#.100x, %#.100x, %#.100x, %#.100x, %#.100x, %#.100x", 0, 5, -1, -10, 0x1234, -1862, 0xABCDE, INT_MIN, INT_MAX, UINT_MAX);
	/* 47 */ test_print_long_ten("%#1.x, %#1.x, %#1.x, %#1.x, %#1.x, %#1.x, %#1.x, %#1.x, %#1.x, %#1.x", 0, 5, -1, -10, 0x1234, -1862, 0xABCDE, INT_MIN, INT_MAX, UINT_MAX);
	/* 48 */ test_print_long_ten("%#1.0x, %#1.0x, %#1.0x, %#1.0x, %#1.0x, %#1.0x, %#1.0x, %#1.0x, %#1.0x, %#1.0x", 0, 5, -1, -10, 0x1234, -1862, 0xABCDE, INT_MIN, INT_MAX, UINT_MAX);
	/* 49 */ test_print_long_ten("%#1.1x, %#1.1x, %#1.1x, %#1.1x, %#1.1x, %#1.1x, %#1.1x, %#1.1x, %#1.1x, %#1.1x", 0, 5, -1, -10, 0x1234, -1862, 0xABCDE, INT_MIN, INT_MAX, UINT_MAX);
	/* 50 */ test_print_long_ten("%#1.5x, %#1.5x, %#1.5x, %#1.5x, %#1.5x, %#1.5x, %#1.5x, %#1.5x, %#1.5x, %#1.5x", 0, 5, -1, -10, 0x1234, -1862, 0xABCDE, INT_MIN, INT_MAX, UINT_MAX);
	/* 51 */ test_print_long_ten("%#1.10x, %#1.10x, %#1.10x, %#1.10x, %#1.10x, %#1.10x, %#1.10x, %#1.10x, %#1.10x, %#1.10x", 0, 5, -1, -10, 0x1234, -1862, 0xABCDE, INT_MIN, INT_MAX, UINT_MAX);
	/* 52 */ test_print_long_ten("%#1.100x, %#1.100x, %#1.100x, %#1.100x, %#1.100x, %#1.100x, %#1.100x, %#1.100x, %#1.100x, %#1.100x", 0, 5, -1, -10, 0x1234, -1862, 0xABCDE, INT_MIN, INT_MAX, UINT_MAX);
	/* 53 */ test_print_long_ten("%#5.x, %#5.x, %#5.x, %#5.x, %#5.x, %#5.x, %#5.x, %#5.x, %#5.x, %#5.x", 0, 5, -1, -10, 0x1234, -1862, 0xABCDE, INT_MIN, INT_MAX, UINT_MAX);
	/* 54 */ test_print_long_ten("%#5.0x, %#5.0x, %#5.0x, %#5.0x, %#5.0x, %#5.0x, %#5.0x, %#5.0x, %#5.0x, %#5.0x", 0, 5, -1, -10, 0x1234, -1862, 0xABCDE, INT_MIN, INT_MAX, UINT_MAX);
	/* 55 */ test_print_long_ten("%#5.1x, %#5.1x, %#5.1x, %#5.1x, %#5.1x, %#5.1x, %#5.1x, %#5.1x, %#5.1x, %#5.1x", 0, 5, -1, -10, 0x1234, -1862, 0xABCDE, INT_MIN, INT_MAX, UINT_MAX);
	/* 56 */ test_print_long_ten("%#5.5x, %#5.5x, %#5.5x, %#5.5x, %#5.5x, %#5.5x, %#5.5x, %#5.5x, %#5.5x, %#5.5x", 0, 5, -1, -10, 0x1234, -1862, 0xABCDE, INT_MIN, INT_MAX, UINT_MAX);
	/* 57 */ test_print_long_ten("%#5.10x, %#5.10x, %#5.10x, %#5.10x, %#5.10x, %#5.10x, %#5.10x, %#5.10x, %#5.10x, %#5.10x", 0, 5, -1, -10, 0x1234, -1862, 0xABCDE, INT_MIN, INT_MAX, UINT_MAX);
	/* 58 */ test_print_long_ten("%#5.100x, %#5.100x, %#5.100x, %#5.100x, %#5.100x, %#5.100x, %#5.100x, %#5.100x, %#5.100x, %#5.100x", 0, 5, -1, -10, 0x1234, -1862, 0xABCDE, INT_MIN, INT_MAX, UINT_MAX);
	/* 59 */ test_print_long_ten("%#10.x, %#10.x, %#10.x, %#10.x, %#10.x, %#10.x, %#10.x, %#10.x, %#10.x, %#10.x", 0, 5, -1, -10, 0x1234, -1862, 0xABCDE, INT_MIN, INT_MAX, UINT_MAX);
	/* 60 */ test_print_long_ten("%#10.0x, %#10.0x, %#10.0x, %#10.0x, %#10.0x, %#10.0x, %#10.0x, %#10.0x, %#10.0x, %#10.0x", 0, 5, -1, -10, 0x1234, -1862, 0xABCDE, INT_MIN, INT_MAX, UINT_MAX);
	/* 61 */ test_print_long_ten("%#10.1x, %#10.1x, %#10.1x, %#10.1x, %#10.1x, %#10.1x, %#10.1x, %#10.1x, %#10.1x, %#10.1x", 0, 5, -1, -10, 0x1234, -1862, 0xABCDE, INT_MIN, INT_MAX, UINT_MAX);
	/* 62 */ test_print_long_ten("%#10.5x, %#10.5x, %#10.5x, %#10.5x, %#10.5x, %#10.5x, %#10.5x, %#10.5x, %#10.5x, %#10.5x", 0, 5, -1, -10, 0x1234, -1862, 0xABCDE, INT_MIN, INT_MAX, UINT_MAX);
	/* 63 */ test_print_long_ten("%#10.10x, %#10.10x, %#10.10x, %#10.10x, %#10.10x, %#10.10x, %#10.10x, %#10.10x, %#10.10x, %#10.10x", 0, 5, -1, -10, 0x1234, -1862, 0xABCDE, INT_MIN, INT_MAX, UINT_MAX);
	/* 64 */ test_print_long_ten("%#10.100x, %#10.100x, %#10.100x, %#10.100x, %#10.100x, %#10.100x, %#10.100x, %#10.100x, %#10.100x, %#10.100x", 0, 5, -1, -10, 0x1234, -1862, 0xABCDE, INT_MIN, INT_MAX, UINT_MAX);
	/* 65 */ test_print_long_ten("%#100.x, %#100.x, %#100.x, %#100.x, %#100.x, %#100.x, %#100.x, %#100.x, %#100.x, %#100.x", 0, 5, -1, -10, 0x1234, -1862, 0xABCDE, INT_MIN, INT_MAX, UINT_MAX);
	/* 66 */ test_print_long_ten("%#100.0x, %#100.0x, %#100.0x, %#100.0x, %#100.0x, %#100.0x, %#100.0x, %#100.0x, %#100.0x, %#100.0x", 0, 5, -1, -10, 0x1234, -1862, 0xABCDE, INT_MIN, INT_MAX, UINT_MAX);
	/* 67 */ test_print_long_ten("%#100.1x, %#100.1x, %#100.1x, %#100.1x, %#100.1x, %#100.1x, %#100.1x, %#100.1x, %#100.1x, %#100.1x", 0, 5, -1, -10, 0x1234, -1862, 0xABCDE, INT_MIN, INT_MAX, UINT_MAX);
	/* 68 */ test_print_long_ten("%#100.5x, %#100.5x, %#100.5x, %#100.5x, %#100.5x, %#100.5x, %#100.5x, %#100.5x, %#100.5x, %#100.5x", 0, 5, -1, -10, 0x1234, -1862, 0xABCDE, INT_MIN, INT_MAX, UINT_MAX);
	/* 69 */ test_print_long_ten("%#100.10x, %#100.10x, %#100.10x, %#100.10x, %#100.10x, %#100.10x, %#100.10x, %#100.10x, %#100.10x, %#100.10x", 0, 5, -1, -10, 0x1234, -1862, 0xABCDE, INT_MIN, INT_MAX, UINT_MAX);
	/* 70 */ test_print_long_ten("%#100.100x, %#100.100x, %#100.100x, %#100.100x, %#100.100x, %#100.100x, %#100.100x, %#100.100x, %#100.100x, %#100.100x", 0, 5, -1, -10, 0x1234, -1862, 0xABCDE, INT_MIN, INT_MAX, UINT_MAX);
	/* 71 */ test_print_long_ten("%0x, %0x, %0x, %0x, %0x, %0x, %0x, %0x, %0x, %0x", 0, 5, -1, -10, 0x1234, -1862, 0xABCDE, INT_MIN, INT_MAX, UINT_MAX);
	/* 72 */ test_print_long_ten("%01x, %01x, %01x, %01x, %01x, %01x, %01x, %01x, %01x, %01x", 0, 5, -1, -10, 0x1234, -1862, 0xABCDE, INT_MIN, INT_MAX, UINT_MAX);
	/* 73 */ test_print_long_ten("%05x, %05x, %05x, %05x, %05x, %05x, %05x, %05x, %05x, %05x", 0, 5, -1, -10, 0x1234, -1862, 0xABCDE, INT_MIN, INT_MAX, UINT_MAX);
	/* 74 */ test_print_long_ten("%010x, %010x, %010x, %010x, %010x, %010x, %010x, %010x, %010x, %010x", 0, 5, -1, -10, 0x1234, -1862, 0xABCDE, INT_MIN, INT_MAX, UINT_MAX);
	/* 75 */ test_print_long_ten("%0100x, %0100x, %0100x, %0100x, %0100x, %0100x, %0100x, %0100x, %0100x, %0100x", 0, 5, -1, -10, 0x1234, -1862, 0xABCDE, INT_MIN, INT_MAX, UINT_MAX);
	/* 76 */ test_print_long_ten("%0.x, %0.x, %0.x, %0.x, %0.x, %0.x, %0.x, %0.x, %0.x, %0.x", 0, 5, -1, -10, 0x1234, -1862, 0xABCDE, INT_MIN, INT_MAX, UINT_MAX);
	/* 77 */ test_print_long_ten("%0.0x, %0.0x, %0.0x, %0.0x, %0.0x, %0.0x, %0.0x, %0.0x, %0.0x, %0.0x", 0, 5, -1, -10, 0x1234, -1862, 0xABCDE, INT_MIN, INT_MAX, UINT_MAX);
	/* 78 */ test_print_long_ten("%0.1x, %0.1x, %0.1x, %0.1x, %0.1x, %0.1x, %0.1x, %0.1x, %0.1x, %0.1x", 0, 5, -1, -10, 0x1234, -1862, 0xABCDE, INT_MIN, INT_MAX, UINT_MAX);
	/* 79 */ test_print_long_ten("%0.5x, %0.5x, %0.5x, %0.5x, %0.5x, %0.5x, %0.5x, %0.5x, %0.5x, %0.5x", 0, 5, -1, -10, 0x1234, -1862, 0xABCDE, INT_MIN, INT_MAX, UINT_MAX);
	/* 80 */ test_print_long_ten("%0.10x, %0.10x, %0.10x, %0.10x, %0.10x, %0.10x, %0.10x, %0.10x, %0.10x, %0.10x", 0, 5, -1, -10, 0x1234, -1862, 0xABCDE, INT_MIN, INT_MAX, UINT_MAX);
	/* 81 */ test_print_long_ten("%0.100x, %0.100x, %0.100x, %0.100x, %0.100x, %0.100x, %0.100x, %0.100x, %0.100x, %0.100x", 0, 5, -1, -10, 0x1234, -1862, 0xABCDE, INT_MIN, INT_MAX, UINT_MAX);
	/* 82 */ test_print_long_ten("%01.x, %01.x, %01.x, %01.x, %01.x, %01.x, %01.x, %01.x, %01.x, %01.x", 0, 5, -1, -10, 0x1234, -1862, 0xABCDE, INT_MIN, INT_MAX, UINT_MAX);
	/* 83 */ test_print_long_ten("%01.0x, %01.0x, %01.0x, %01.0x, %01.0x, %01.0x, %01.0x, %01.0x, %01.0x, %01.0x", 0, 5, -1, -10, 0x1234, -1862, 0xABCDE, INT_MIN, INT_MAX, UINT_MAX);
	/* 84 */ test_print_long_ten("%01.1x, %01.1x, %01.1x, %01.1x, %01.1x, %01.1x, %01.1x, %01.1x, %01.1x, %01.1x", 0, 5, -1, -10, 0x1234, -1862, 0xABCDE, INT_MIN, INT_MAX, UINT_MAX);
	/* 85 */ test_print_long_ten("%01.5x, %01.5x, %01.5x, %01.5x, %01.5x, %01.5x, %01.5x, %01.5x, %01.5x, %01.5x", 0, 5, -1, -10, 0x1234, -1862, 0xABCDE, INT_MIN, INT_MAX, UINT_MAX);
	/* 86 */ test_print_long_ten("%01.10x, %01.10x, %01.10x, %01.10x, %01.10x, %01.10x, %01.10x, %01.10x, %01.10x, %01.10x", 0, 5, -1, -10, 0x1234, -1862, 0xABCDE, INT_MIN, INT_MAX, UINT_MAX);
	/* 87 */ test_print_long_ten("%01.100x, %01.100x, %01.100x, %01.100x, %01.100x, %01.100x, %01.100x, %01.100x, %01.100x, %01.100x", 0, 5, -1, -10, 0x1234, -1862, 0xABCDE, INT_MIN, INT_MAX, UINT_MAX);
	/* 88 */ test_print_long_ten("%05.x, %05.x, %05.x, %05.x, %05.x, %05.x, %05.x, %05.x, %05.x, %05.x", 0, 5, -1, -10, 0x1234, -1862, 0xABCDE, INT_MIN, INT_MAX, UINT_MAX);
	/* 89 */ test_print_long_ten("%05.0x, %05.0x, %05.0x, %05.0x, %05.0x, %05.0x, %05.0x, %05.0x, %05.0x, %05.0x", 0, 5, -1, -10, 0x1234, -1862, 0xABCDE, INT_MIN, INT_MAX, UINT_MAX);
	/* 90 */ test_print_long_ten("%05.1x, %05.1x, %05.1x, %05.1x, %05.1x, %05.1x, %05.1x, %05.1x, %05.1x, %05.1x", 0, 5, -1, -10, 0x1234, -1862, 0xABCDE, INT_MIN, INT_MAX, UINT_MAX);
	/* 91 */ test_print_long_ten("%05.5x, %05.5x, %05.5x, %05.5x, %05.5x, %05.5x, %05.5x, %05.5x, %05.5x, %05.5x", 0, 5, -1, -10, 0x1234, -1862, 0xABCDE, INT_MIN, INT_MAX, UINT_MAX);
	/* 92 */ test_print_long_ten("%05.10x, %05.10x, %05.10x, %05.10x, %05.10x, %05.10x, %05.10x, %05.10x, %05.10x, %05.10x", 0, 5, -1, -10, 0x1234, -1862, 0xABCDE, INT_MIN, INT_MAX, UINT_MAX);
	/* 93 */ test_print_long_ten("%05.100x, %05.100x, %05.100x, %05.100x, %05.100x, %05.100x, %05.100x, %05.100x, %05.100x, %05.100x", 0, 5, -1, -10, 0x1234, -1862, 0xABCDE, INT_MIN, INT_MAX, UINT_MAX);
	/* 94 */ test_print_long_ten("%010.x, %010.x, %010.x, %010.x, %010.x, %010.x, %010.x, %010.x, %010.x, %010.x", 0, 5, -1, -10, 0x1234, -1862, 0xABCDE, INT_MIN, INT_MAX, UINT_MAX);
	/* 95 */ test_print_long_ten("%010.0x, %010.0x, %010.0x, %010.0x, %010.0x, %010.0x, %010.0x, %010.0x, %010.0x, %010.0x", 0, 5, -1, -10, 0x1234, -1862, 0xABCDE, INT_MIN, INT_MAX, UINT_MAX);
	/* 96 */ test_print_long_ten("%010.1x, %010.1x, %010.1x, %010.1x, %010.1x, %010.1x, %010.1x, %010.1x, %010.1x, %010.1x", 0, 5, -1, -10, 0x1234, -1862, 0xABCDE, INT_MIN, INT_MAX, UINT_MAX);
	/* 97 */ test_print_long_ten("%010.5x, %010.5x, %010.5x, %010.5x, %010.5x, %010.5x, %010.5x, %010.5x, %010.5x, %010.5x", 0, 5, -1, -10, 0x1234, -1862, 0xABCDE, INT_MIN, INT_MAX, UINT_MAX);
	/* 98 */ test_print_long_ten("%010.10x, %010.10x, %010.10x, %010.10x, %010.10x, %010.10x, %010.10x, %010.10x, %010.10x, %010.10x", 0, 5, -1, -10, 0x1234, -1862, 0xABCDE, INT_MIN, INT_MAX, UINT_MAX);
	/* 99 */ test_print_long_ten("%010.100x, %010.100x, %010.100x, %010.100x, %010.100x, %010.100x, %010.100x, %010.100x, %010.100x, %010.100x", 0, 5, -1, -10, 0x1234, -1862, 0xABCDE, INT_MIN, INT_MAX, UINT_MAX);
	/* 100 */ test_print_long_ten("%0100.x, %0100.x, %0100.x, %0100.x, %0100.x, %0100.x, %0100.x, %0100.x, %0100.x, %0100.x", 0, 5, -1, -10, 0x1234, -1862, 0xABCDE, INT_MIN, INT_MAX, UINT_MAX);
	/* 101 */ test_print_long_ten("%0100.0x, %0100.0x, %0100.0x, %0100.0x, %0100.0x, %0100.0x, %0100.0x, %0100.0x, %0100.0x, %0100.0x", 0, 5, -1, -10, 0x1234, -1862, 0xABCDE, INT_MIN, INT_MAX, UINT_MAX);
	/* 102 */ test_print_long_ten("%0100.1x, %0100.1x, %0100.1x, %0100.1x, %0100.1x, %0100.1x, %0100.1x, %0100.1x, %0100.1x, %0100.1x", 0, 5, -1, -10, 0x1234, -1862, 0xABCDE, INT_MIN, INT_MAX, UINT_MAX);
	/* 103 */ test_print_long_ten("%0100.5x, %0100.5x, %0100.5x, %0100.5x, %0100.5x, %0100.5x, %0100.5x, %0100.5x, %0100.5x, %0100.5x", 0, 5, -1, -10, 0x1234, -1862, 0xABCDE, INT_MIN, INT_MAX, UINT_MAX);
	/* 104 */ test_print_long_ten("%0100.10x, %0100.10x, %0100.10x, %0100.10x, %0100.10x, %0100.10x, %0100.10x, %0100.10x, %0100.10x, %0100.10x", 0, 5, -1, -10, 0x1234, -1862, 0xABCDE, INT_MIN, INT_MAX, UINT_MAX);
	/* 105 */ test_print_long_ten("%0100.100x, %0100.100x, %0100.100x, %0100.100x, %0100.100x, %0100.100x, %0100.100x, %0100.100x, %0100.100x, %0100.100x", 0, 5, -1, -10, 0x1234, -1862, 0xABCDE, INT_MIN, INT_MAX, UINT_MAX);
	/* 106 */ test_print_long_ten("%0#x, %0#x, %0#x, %0#x, %0#x, %0#x, %0#x, %0#x, %0#x, %0#x", 0, 5, -1, -10, 0x1234, -1862, 0xABCDE, INT_MIN, INT_MAX, UINT_MAX);
	/* 107 */ test_print_long_ten("%0#1x, %0#1x, %0#1x, %0#1x, %0#1x, %0#1x, %0#1x, %0#1x, %0#1x, %0#1x", 0, 5, -1, -10, 0x1234, -1862, 0xABCDE, INT_MIN, INT_MAX, UINT_MAX);
	/* 108 */ test_print_long_ten("%0#5x, %0#5x, %0#5x, %0#5x, %0#5x, %0#5x, %0#5x, %0#5x, %0#5x, %0#5x", 0, 5, -1, -10, 0x1234, -1862, 0xABCDE, INT_MIN, INT_MAX, UINT_MAX);
	/* 109 */ test_print_long_ten("%0#10x, %0#10x, %0#10x, %0#10x, %0#10x, %0#10x, %0#10x, %0#10x, %0#10x, %0#10x", 0, 5, -1, -10, 0x1234, -1862, 0xABCDE, INT_MIN, INT_MAX, UINT_MAX);
	/* 110 */ test_print_long_ten("%0#100x, %0#100x, %0#100x, %0#100x, %0#100x, %0#100x, %0#100x, %0#100x, %0#100x, %0#100x", 0, 5, -1, -10, 0x1234, -1862, 0xABCDE, INT_MIN, INT_MAX, UINT_MAX);
	/* 111 */ test_print_long_ten("%0#.x, %0#.x, %0#.x, %0#.x, %0#.x, %0#.x, %0#.x, %0#.x, %0#.x, %0#.x", 0, 5, -1, -10, 0x1234, -1862, 0xABCDE, INT_MIN, INT_MAX, UINT_MAX);
	/* 112 */ test_print_long_ten("%0#.0x, %0#.0x, %0#.0x, %0#.0x, %0#.0x, %0#.0x, %0#.0x, %0#.0x, %0#.0x, %0#.0x", 0, 5, -1, -10, 0x1234, -1862, 0xABCDE, INT_MIN, INT_MAX, UINT_MAX);
	/* 113 */ test_print_long_ten("%0#.1x, %0#.1x, %0#.1x, %0#.1x, %0#.1x, %0#.1x, %0#.1x, %0#.1x, %0#.1x, %0#.1x", 0, 5, -1, -10, 0x1234, -1862, 0xABCDE, INT_MIN, INT_MAX, UINT_MAX);
	/* 114 */ test_print_long_ten("%0#.5x, %0#.5x, %0#.5x, %0#.5x, %0#.5x, %0#.5x, %0#.5x, %0#.5x, %0#.5x, %0#.5x", 0, 5, -1, -10, 0x1234, -1862, 0xABCDE, INT_MIN, INT_MAX, UINT_MAX);
	/* 115 */ test_print_long_ten("%0#.10x, %0#.10x, %0#.10x, %0#.10x, %0#.10x, %0#.10x, %0#.10x, %0#.10x, %0#.10x, %0#.10x", 0, 5, -1, -10, 0x1234, -1862, 0xABCDE, INT_MIN, INT_MAX, UINT_MAX);
	/* 116 */ test_print_long_ten("%0#.100x, %0#.100x, %0#.100x, %0#.100x, %0#.100x, %0#.100x, %0#.100x, %0#.100x, %0#.100x, %0#.100x", 0, 5, -1, -10, 0x1234, -1862, 0xABCDE, INT_MIN, INT_MAX, UINT_MAX);
	/* 117 */ test_print_long_ten("%0#1.x, %0#1.x, %0#1.x, %0#1.x, %0#1.x, %0#1.x, %0#1.x, %0#1.x, %0#1.x, %0#1.x", 0, 5, -1, -10, 0x1234, -1862, 0xABCDE, INT_MIN, INT_MAX, UINT_MAX);
	/* 118 */ test_print_long_ten("%0#1.0x, %0#1.0x, %0#1.0x, %0#1.0x, %0#1.0x, %0#1.0x, %0#1.0x, %0#1.0x, %0#1.0x, %0#1.0x", 0, 5, -1, -10, 0x1234, -1862, 0xABCDE, INT_MIN, INT_MAX, UINT_MAX);
	/* 119 */ test_print_long_ten("%0#1.1x, %0#1.1x, %0#1.1x, %0#1.1x, %0#1.1x, %0#1.1x, %0#1.1x, %0#1.1x, %0#1.1x, %0#1.1x", 0, 5, -1, -10, 0x1234, -1862, 0xABCDE, INT_MIN, INT_MAX, UINT_MAX);
	/* 120 */ test_print_long_ten("%0#1.5x, %0#1.5x, %0#1.5x, %0#1.5x, %0#1.5x, %0#1.5x, %0#1.5x, %0#1.5x, %0#1.5x, %0#1.5x", 0, 5, -1, -10, 0x1234, -1862, 0xABCDE, INT_MIN, INT_MAX, UINT_MAX);
	/* 121 */ test_print_long_ten("%0#1.10x, %0#1.10x, %0#1.10x, %0#1.10x, %0#1.10x, %0#1.10x, %0#1.10x, %0#1.10x, %0#1.10x, %0#1.10x", 0, 5, -1, -10, 0x1234, -1862, 0xABCDE, INT_MIN, INT_MAX, UINT_MAX);
	/* 122 */ test_print_long_ten("%0#1.100x, %0#1.100x, %0#1.100x, %0#1.100x, %0#1.100x, %0#1.100x, %0#1.100x, %0#1.100x, %0#1.100x, %0#1.100x", 0, 5, -1, -10, 0x1234, -1862, 0xABCDE, INT_MIN, INT_MAX, UINT_MAX);
	/* 123 */ test_print_long_ten("%0#5.x, %0#5.x, %0#5.x, %0#5.x, %0#5.x, %0#5.x, %0#5.x, %0#5.x, %0#5.x, %0#5.x", 0, 5, -1, -10, 0x1234, -1862, 0xABCDE, INT_MIN, INT_MAX, UINT_MAX);
	/* 124 */ test_print_long_ten("%0#5.0x, %0#5.0x, %0#5.0x, %0#5.0x, %0#5.0x, %0#5.0x, %0#5.0x, %0#5.0x, %0#5.0x, %0#5.0x", 0, 5, -1, -10, 0x1234, -1862, 0xABCDE, INT_MIN, INT_MAX, UINT_MAX);
	/* 125 */ test_print_long_ten("%0#5.1x, %0#5.1x, %0#5.1x, %0#5.1x, %0#5.1x, %0#5.1x, %0#5.1x, %0#5.1x, %0#5.1x, %0#5.1x", 0, 5, -1, -10, 0x1234, -1862, 0xABCDE, INT_MIN, INT_MAX, UINT_MAX);
	/* 126 */ test_print_long_ten("%0#5.5x, %0#5.5x, %0#5.5x, %0#5.5x, %0#5.5x, %0#5.5x, %0#5.5x, %0#5.5x, %0#5.5x, %0#5.5x", 0, 5, -1, -10, 0x1234, -1862, 0xABCDE, INT_MIN, INT_MAX, UINT_MAX);
	/* 127 */ test_print_long_ten("%0#5.10x, %0#5.10x, %0#5.10x, %0#5.10x, %0#5.10x, %0#5.10x, %0#5.10x, %0#5.10x, %0#5.10x, %0#5.10x", 0, 5, -1, -10, 0x1234, -1862, 0xABCDE, INT_MIN, INT_MAX, UINT_MAX);
	/* 128 */ test_print_long_ten("%0#5.100x, %0#5.100x, %0#5.100x, %0#5.100x, %0#5.100x, %0#5.100x, %0#5.100x, %0#5.100x, %0#5.100x, %0#5.100x", 0, 5, -1, -10, 0x1234, -1862, 0xABCDE, INT_MIN, INT_MAX, UINT_MAX);
	/* 129 */ test_print_long_ten("%0#10.x, %0#10.x, %0#10.x, %0#10.x, %0#10.x, %0#10.x, %0#10.x, %0#10.x, %0#10.x, %0#10.x", 0, 5, -1, -10, 0x1234, -1862, 0xABCDE, INT_MIN, INT_MAX, UINT_MAX);
	/* 130 */ test_print_long_ten("%0#10.0x, %0#10.0x, %0#10.0x, %0#10.0x, %0#10.0x, %0#10.0x, %0#10.0x, %0#10.0x, %0#10.0x, %0#10.0x", 0, 5, -1, -10, 0x1234, -1862, 0xABCDE, INT_MIN, INT_MAX, UINT_MAX);
	/* 131 */ test_print_long_ten("%0#10.1x, %0#10.1x, %0#10.1x, %0#10.1x, %0#10.1x, %0#10.1x, %0#10.1x, %0#10.1x, %0#10.1x, %0#10.1x", 0, 5, -1, -10, 0x1234, -1862, 0xABCDE, INT_MIN, INT_MAX, UINT_MAX);
	/* 132 */ test_print_long_ten("%0#10.5x, %0#10.5x, %0#10.5x, %0#10.5x, %0#10.5x, %0#10.5x, %0#10.5x, %0#10.5x, %0#10.5x, %0#10.5x", 0, 5, -1, -10, 0x1234, -1862, 0xABCDE, INT_MIN, INT_MAX, UINT_MAX);
	/* 133 */ test_print_long_ten("%0#10.10x, %0#10.10x, %0#10.10x, %0#10.10x, %0#10.10x, %0#10.10x, %0#10.10x, %0#10.10x, %0#10.10x, %0#10.10x", 0, 5, -1, -10, 0x1234, -1862, 0xABCDE, INT_MIN, INT_MAX, UINT_MAX);
	/* 134 */ test_print_long_ten("%0#10.100x, %0#10.100x, %0#10.100x, %0#10.100x, %0#10.100x, %0#10.100x, %0#10.100x, %0#10.100x, %0#10.100x, %0#10.100x", 0, 5, -1, -10, 0x1234, -1862, 0xABCDE, INT_MIN, INT_MAX, UINT_MAX);
	/* 135 */ test_print_long_ten("%0#100.x, %0#100.x, %0#100.x, %0#100.x, %0#100.x, %0#100.x, %0#100.x, %0#100.x, %0#100.x, %0#100.x", 0, 5, -1, -10, 0x1234, -1862, 0xABCDE, INT_MIN, INT_MAX, UINT_MAX);
	/* 136 */ test_print_long_ten("%0#100.0x, %0#100.0x, %0#100.0x, %0#100.0x, %0#100.0x, %0#100.0x, %0#100.0x, %0#100.0x, %0#100.0x, %0#100.0x", 0, 5, -1, -10, 0x1234, -1862, 0xABCDE, INT_MIN, INT_MAX, UINT_MAX);
	/* 137 */ test_print_long_ten("%0#100.1x, %0#100.1x, %0#100.1x, %0#100.1x, %0#100.1x, %0#100.1x, %0#100.1x, %0#100.1x, %0#100.1x, %0#100.1x", 0, 5, -1, -10, 0x1234, -1862, 0xABCDE, INT_MIN, INT_MAX, UINT_MAX);
	/* 138 */ test_print_long_ten("%0#100.5x, %0#100.5x, %0#100.5x, %0#100.5x, %0#100.5x, %0#100.5x, %0#100.5x, %0#100.5x, %0#100.5x, %0#100.5x", 0, 5, -1, -10, 0x1234, -1862, 0xABCDE, INT_MIN, INT_MAX, UINT_MAX);
	/* 139 */ test_print_long_ten("%0#100.10x, %0#100.10x, %0#100.10x, %0#100.10x, %0#100.10x, %0#100.10x, %0#100.10x, %0#100.10x, %0#100.10x, %0#100.10x", 0, 5, -1, -10, 0x1234, -1862, 0xABCDE, INT_MIN, INT_MAX, UINT_MAX);
	/* 140 */ test_print_long_ten("%0#100.100x, %0#100.100x, %0#100.100x, %0#100.100x, %0#100.100x, %0#100.100x, %0#100.100x, %0#100.100x, %0#100.100x, %0#100.100x", 0, 5, -1, -10, 0x1234, -1862, 0xABCDE, INT_MIN, INT_MAX, UINT_MAX);
	/* 141 */ test_print_long_ten("%-x, %-x, %-x, %-x, %-x, %-x, %-x, %-x, %-x, %-x", 0, 5, -1, -10, 0x1234, -1862, 0xABCDE, INT_MIN, INT_MAX, UINT_MAX);
	/* 142 */ test_print_long_ten("%-1x, %-1x, %-1x, %-1x, %-1x, %-1x, %-1x, %-1x, %-1x, %-1x", 0, 5, -1, -10, 0x1234, -1862, 0xABCDE, INT_MIN, INT_MAX, UINT_MAX);
	/* 143 */ test_print_long_ten("%-5x, %-5x, %-5x, %-5x, %-5x, %-5x, %-5x, %-5x, %-5x, %-5x", 0, 5, -1, -10, 0x1234, -1862, 0xABCDE, INT_MIN, INT_MAX, UINT_MAX);
	/* 144 */ test_print_long_ten("%-10x, %-10x, %-10x, %-10x, %-10x, %-10x, %-10x, %-10x, %-10x, %-10x", 0, 5, -1, -10, 0x1234, -1862, 0xABCDE, INT_MIN, INT_MAX, UINT_MAX);
	/* 145 */ test_print_long_ten("%-100x, %-100x, %-100x, %-100x, %-100x, %-100x, %-100x, %-100x, %-100x, %-100x", 0, 5, -1, -10, 0x1234, -1862, 0xABCDE, INT_MIN, INT_MAX, UINT_MAX);
	/* 146 */ test_print_long_ten("%-.x, %-.x, %-.x, %-.x, %-.x, %-.x, %-.x, %-.x, %-.x, %-.x", 0, 5, -1, -10, 0x1234, -1862, 0xABCDE, INT_MIN, INT_MAX, UINT_MAX);
	/* 147 */ test_print_long_ten("%-.0x, %-.0x, %-.0x, %-.0x, %-.0x, %-.0x, %-.0x, %-.0x, %-.0x, %-.0x", 0, 5, -1, -10, 0x1234, -1862, 0xABCDE, INT_MIN, INT_MAX, UINT_MAX);
	/* 148 */ test_print_long_ten("%-.1x, %-.1x, %-.1x, %-.1x, %-.1x, %-.1x, %-.1x, %-.1x, %-.1x, %-.1x", 0, 5, -1, -10, 0x1234, -1862, 0xABCDE, INT_MIN, INT_MAX, UINT_MAX);
	/* 149 */ test_print_long_ten("%-.5x, %-.5x, %-.5x, %-.5x, %-.5x, %-.5x, %-.5x, %-.5x, %-.5x, %-.5x", 0, 5, -1, -10, 0x1234, -1862, 0xABCDE, INT_MIN, INT_MAX, UINT_MAX);
	/* 150 */ test_print_long_ten("%-.10x, %-.10x, %-.10x, %-.10x, %-.10x, %-.10x, %-.10x, %-.10x, %-.10x, %-.10x", 0, 5, -1, -10, 0x1234, -1862, 0xABCDE, INT_MIN, INT_MAX, UINT_MAX);
	/* 151 */ test_print_long_ten("%-.100x, %-.100x, %-.100x, %-.100x, %-.100x, %-.100x, %-.100x, %-.100x, %-.100x, %-.100x", 0, 5, -1, -10, 0x1234, -1862, 0xABCDE, INT_MIN, INT_MAX, UINT_MAX);
	/* 152 */ test_print_long_ten("%-1.x, %-1.x, %-1.x, %-1.x, %-1.x, %-1.x, %-1.x, %-1.x, %-1.x, %-1.x", 0, 5, -1, -10, 0x1234, -1862, 0xABCDE, INT_MIN, INT_MAX, UINT_MAX);
	/* 153 */ test_print_long_ten("%-1.0x, %-1.0x, %-1.0x, %-1.0x, %-1.0x, %-1.0x, %-1.0x, %-1.0x, %-1.0x, %-1.0x", 0, 5, -1, -10, 0x1234, -1862, 0xABCDE, INT_MIN, INT_MAX, UINT_MAX);
	/* 154 */ test_print_long_ten("%-1.1x, %-1.1x, %-1.1x, %-1.1x, %-1.1x, %-1.1x, %-1.1x, %-1.1x, %-1.1x, %-1.1x", 0, 5, -1, -10, 0x1234, -1862, 0xABCDE, INT_MIN, INT_MAX, UINT_MAX);
	/* 155 */ test_print_long_ten("%-1.5x, %-1.5x, %-1.5x, %-1.5x, %-1.5x, %-1.5x, %-1.5x, %-1.5x, %-1.5x, %-1.5x", 0, 5, -1, -10, 0x1234, -1862, 0xABCDE, INT_MIN, INT_MAX, UINT_MAX);
	/* 156 */ test_print_long_ten("%-1.10x, %-1.10x, %-1.10x, %-1.10x, %-1.10x, %-1.10x, %-1.10x, %-1.10x, %-1.10x, %-1.10x", 0, 5, -1, -10, 0x1234, -1862, 0xABCDE, INT_MIN, INT_MAX, UINT_MAX);
	/* 157 */ test_print_long_ten("%-1.100x, %-1.100x, %-1.100x, %-1.100x, %-1.100x, %-1.100x, %-1.100x, %-1.100x, %-1.100x, %-1.100x", 0, 5, -1, -10, 0x1234, -1862, 0xABCDE, INT_MIN, INT_MAX, UINT_MAX);
	/* 158 */ test_print_long_ten("%-5.x, %-5.x, %-5.x, %-5.x, %-5.x, %-5.x, %-5.x, %-5.x, %-5.x, %-5.x", 0, 5, -1, -10, 0x1234, -1862, 0xABCDE, INT_MIN, INT_MAX, UINT_MAX);
	/* 159 */ test_print_long_ten("%-5.0x, %-5.0x, %-5.0x, %-5.0x, %-5.0x, %-5.0x, %-5.0x, %-5.0x, %-5.0x, %-5.0x", 0, 5, -1, -10, 0x1234, -1862, 0xABCDE, INT_MIN, INT_MAX, UINT_MAX);
	/* 160 */ test_print_long_ten("%-5.1x, %-5.1x, %-5.1x, %-5.1x, %-5.1x, %-5.1x, %-5.1x, %-5.1x, %-5.1x, %-5.1x", 0, 5, -1, -10, 0x1234, -1862, 0xABCDE, INT_MIN, INT_MAX, UINT_MAX);
	/* 161 */ test_print_long_ten("%-5.5x, %-5.5x, %-5.5x, %-5.5x, %-5.5x, %-5.5x, %-5.5x, %-5.5x, %-5.5x, %-5.5x", 0, 5, -1, -10, 0x1234, -1862, 0xABCDE, INT_MIN, INT_MAX, UINT_MAX);
	/* 162 */ test_print_long_ten("%-5.10x, %-5.10x, %-5.10x, %-5.10x, %-5.10x, %-5.10x, %-5.10x, %-5.10x, %-5.10x, %-5.10x", 0, 5, -1, -10, 0x1234, -1862, 0xABCDE, INT_MIN, INT_MAX, UINT_MAX);
	/* 163 */ test_print_long_ten("%-5.100x, %-5.100x, %-5.100x, %-5.100x, %-5.100x, %-5.100x, %-5.100x, %-5.100x, %-5.100x, %-5.100x", 0, 5, -1, -10, 0x1234, -1862, 0xABCDE, INT_MIN, INT_MAX, UINT_MAX);
	/* 164 */ test_print_long_ten("%-10.x, %-10.x, %-10.x, %-10.x, %-10.x, %-10.x, %-10.x, %-10.x, %-10.x, %-10.x", 0, 5, -1, -10, 0x1234, -1862, 0xABCDE, INT_MIN, INT_MAX, UINT_MAX);
	/* 165 */ test_print_long_ten("%-10.0x, %-10.0x, %-10.0x, %-10.0x, %-10.0x, %-10.0x, %-10.0x, %-10.0x, %-10.0x, %-10.0x", 0, 5, -1, -10, 0x1234, -1862, 0xABCDE, INT_MIN, INT_MAX, UINT_MAX);
	/* 166 */ test_print_long_ten("%-10.1x, %-10.1x, %-10.1x, %-10.1x, %-10.1x, %-10.1x, %-10.1x, %-10.1x, %-10.1x, %-10.1x", 0, 5, -1, -10, 0x1234, -1862, 0xABCDE, INT_MIN, INT_MAX, UINT_MAX);
	/* 167 */ test_print_long_ten("%-10.5x, %-10.5x, %-10.5x, %-10.5x, %-10.5x, %-10.5x, %-10.5x, %-10.5x, %-10.5x, %-10.5x", 0, 5, -1, -10, 0x1234, -1862, 0xABCDE, INT_MIN, INT_MAX, UINT_MAX);
	/* 168 */ test_print_long_ten("%-10.10x, %-10.10x, %-10.10x, %-10.10x, %-10.10x, %-10.10x, %-10.10x, %-10.10x, %-10.10x, %-10.10x", 0, 5, -1, -10, 0x1234, -1862, 0xABCDE, INT_MIN, INT_MAX, UINT_MAX);
	/* 169 */ test_print_long_ten("%-10.100x, %-10.100x, %-10.100x, %-10.100x, %-10.100x, %-10.100x, %-10.100x, %-10.100x, %-10.100x, %-10.100x", 0, 5, -1, -10, 0x1234, -1862, 0xABCDE, INT_MIN, INT_MAX, UINT_MAX);
	/* 170 */ test_print_long_ten("%-100.x, %-100.x, %-100.x, %-100.x, %-100.x, %-100.x, %-100.x, %-100.x, %-100.x, %-100.x", 0, 5, -1, -10, 0x1234, -1862, 0xABCDE, INT_MIN, INT_MAX, UINT_MAX);
	/* 171 */ test_print_long_ten("%-100.0x, %-100.0x, %-100.0x, %-100.0x, %-100.0x, %-100.0x, %-100.0x, %-100.0x, %-100.0x, %-100.0x", 0, 5, -1, -10, 0x1234, -1862, 0xABCDE, INT_MIN, INT_MAX, UINT_MAX);
	/* 172 */ test_print_long_ten("%-100.1x, %-100.1x, %-100.1x, %-100.1x, %-100.1x, %-100.1x, %-100.1x, %-100.1x, %-100.1x, %-100.1x", 0, 5, -1, -10, 0x1234, -1862, 0xABCDE, INT_MIN, INT_MAX, UINT_MAX);
	/* 173 */ test_print_long_ten("%-100.5x, %-100.5x, %-100.5x, %-100.5x, %-100.5x, %-100.5x, %-100.5x, %-100.5x, %-100.5x, %-100.5x", 0, 5, -1, -10, 0x1234, -1862, 0xABCDE, INT_MIN, INT_MAX, UINT_MAX);
	/* 174 */ test_print_long_ten("%-100.10x, %-100.10x, %-100.10x, %-100.10x, %-100.10x, %-100.10x, %-100.10x, %-100.10x, %-100.10x, %-100.10x", 0, 5, -1, -10, 0x1234, -1862, 0xABCDE, INT_MIN, INT_MAX, UINT_MAX);
	/* 175 */ test_print_long_ten("%-100.100x, %-100.100x, %-100.100x, %-100.100x, %-100.100x, %-100.100x, %-100.100x, %-100.100x, %-100.100x, %-100.100x", 0, 5, -1, -10, 0x1234, -1862, 0xABCDE, INT_MIN, INT_MAX, UINT_MAX);
	/* 176 */ test_print_long_ten("%-#x, %-#x, %-#x, %-#x, %-#x, %-#x, %-#x, %-#x, %-#x, %-#x", 0, 5, -1, -10, 0x1234, -1862, 0xABCDE, INT_MIN, INT_MAX, UINT_MAX);
	/* 177 */ test_print_long_ten("%-#1x, %-#1x, %-#1x, %-#1x, %-#1x, %-#1x, %-#1x, %-#1x, %-#1x, %-#1x", 0, 5, -1, -10, 0x1234, -1862, 0xABCDE, INT_MIN, INT_MAX, UINT_MAX);
	/* 178 */ test_print_long_ten("%-#5x, %-#5x, %-#5x, %-#5x, %-#5x, %-#5x, %-#5x, %-#5x, %-#5x, %-#5x", 0, 5, -1, -10, 0x1234, -1862, 0xABCDE, INT_MIN, INT_MAX, UINT_MAX);
	/* 179 */ test_print_long_ten("%-#10x, %-#10x, %-#10x, %-#10x, %-#10x, %-#10x, %-#10x, %-#10x, %-#10x, %-#10x", 0, 5, -1, -10, 0x1234, -1862, 0xABCDE, INT_MIN, INT_MAX, UINT_MAX);
	/* 180 */ test_print_long_ten("%-#100x, %-#100x, %-#100x, %-#100x, %-#100x, %-#100x, %-#100x, %-#100x, %-#100x, %-#100x", 0, 5, -1, -10, 0x1234, -1862, 0xABCDE, INT_MIN, INT_MAX, UINT_MAX);
	/* 181 */ test_print_long_ten("%-#.x, %-#.x, %-#.x, %-#.x, %-#.x, %-#.x, %-#.x, %-#.x, %-#.x, %-#.x", 0, 5, -1, -10, 0x1234, -1862, 0xABCDE, INT_MIN, INT_MAX, UINT_MAX);
	/* 182 */ test_print_long_ten("%-#.0x, %-#.0x, %-#.0x, %-#.0x, %-#.0x, %-#.0x, %-#.0x, %-#.0x, %-#.0x, %-#.0x", 0, 5, -1, -10, 0x1234, -1862, 0xABCDE, INT_MIN, INT_MAX, UINT_MAX);
	/* 183 */ test_print_long_ten("%-#.1x, %-#.1x, %-#.1x, %-#.1x, %-#.1x, %-#.1x, %-#.1x, %-#.1x, %-#.1x, %-#.1x", 0, 5, -1, -10, 0x1234, -1862, 0xABCDE, INT_MIN, INT_MAX, UINT_MAX);
	/* 184 */ test_print_long_ten("%-#.5x, %-#.5x, %-#.5x, %-#.5x, %-#.5x, %-#.5x, %-#.5x, %-#.5x, %-#.5x, %-#.5x", 0, 5, -1, -10, 0x1234, -1862, 0xABCDE, INT_MIN, INT_MAX, UINT_MAX);
	/* 185 */ test_print_long_ten("%-#.10x, %-#.10x, %-#.10x, %-#.10x, %-#.10x, %-#.10x, %-#.10x, %-#.10x, %-#.10x, %-#.10x", 0, 5, -1, -10, 0x1234, -1862, 0xABCDE, INT_MIN, INT_MAX, UINT_MAX);
	/* 186 */ test_print_long_ten("%-#.100x, %-#.100x, %-#.100x, %-#.100x, %-#.100x, %-#.100x, %-#.100x, %-#.100x, %-#.100x, %-#.100x", 0, 5, -1, -10, 0x1234, -1862, 0xABCDE, INT_MIN, INT_MAX, UINT_MAX);
	/* 187 */ test_print_long_ten("%-#1.x, %-#1.x, %-#1.x, %-#1.x, %-#1.x, %-#1.x, %-#1.x, %-#1.x, %-#1.x, %-#1.x", 0, 5, -1, -10, 0x1234, -1862, 0xABCDE, INT_MIN, INT_MAX, UINT_MAX);
	/* 188 */ test_print_long_ten("%-#1.0x, %-#1.0x, %-#1.0x, %-#1.0x, %-#1.0x, %-#1.0x, %-#1.0x, %-#1.0x, %-#1.0x, %-#1.0x", 0, 5, -1, -10, 0x1234, -1862, 0xABCDE, INT_MIN, INT_MAX, UINT_MAX);
	/* 189 */ test_print_long_ten("%-#1.1x, %-#1.1x, %-#1.1x, %-#1.1x, %-#1.1x, %-#1.1x, %-#1.1x, %-#1.1x, %-#1.1x, %-#1.1x", 0, 5, -1, -10, 0x1234, -1862, 0xABCDE, INT_MIN, INT_MAX, UINT_MAX);
	/* 190 */ test_print_long_ten("%-#1.5x, %-#1.5x, %-#1.5x, %-#1.5x, %-#1.5x, %-#1.5x, %-#1.5x, %-#1.5x, %-#1.5x, %-#1.5x", 0, 5, -1, -10, 0x1234, -1862, 0xABCDE, INT_MIN, INT_MAX, UINT_MAX);
	/* 191 */ test_print_long_ten("%-#1.10x, %-#1.10x, %-#1.10x, %-#1.10x, %-#1.10x, %-#1.10x, %-#1.10x, %-#1.10x, %-#1.10x, %-#1.10x", 0, 5, -1, -10, 0x1234, -1862, 0xABCDE, INT_MIN, INT_MAX, UINT_MAX);
	/* 192 */ test_print_long_ten("%-#1.100x, %-#1.100x, %-#1.100x, %-#1.100x, %-#1.100x, %-#1.100x, %-#1.100x, %-#1.100x, %-#1.100x, %-#1.100x", 0, 5, -1, -10, 0x1234, -1862, 0xABCDE, INT_MIN, INT_MAX, UINT_MAX);
	/* 193 */ test_print_long_ten("%-#5.x, %-#5.x, %-#5.x, %-#5.x, %-#5.x, %-#5.x, %-#5.x, %-#5.x, %-#5.x, %-#5.x", 0, 5, -1, -10, 0x1234, -1862, 0xABCDE, INT_MIN, INT_MAX, UINT_MAX);
	/* 194 */ test_print_long_ten("%-#5.0x, %-#5.0x, %-#5.0x, %-#5.0x, %-#5.0x, %-#5.0x, %-#5.0x, %-#5.0x, %-#5.0x, %-#5.0x", 0, 5, -1, -10, 0x1234, -1862, 0xABCDE, INT_MIN, INT_MAX, UINT_MAX);
	/* 195 */ test_print_long_ten("%-#5.1x, %-#5.1x, %-#5.1x, %-#5.1x, %-#5.1x, %-#5.1x, %-#5.1x, %-#5.1x, %-#5.1x, %-#5.1x", 0, 5, -1, -10, 0x1234, -1862, 0xABCDE, INT_MIN, INT_MAX, UINT_MAX);
	/* 196 */ test_print_long_ten("%-#5.5x, %-#5.5x, %-#5.5x, %-#5.5x, %-#5.5x, %-#5.5x, %-#5.5x, %-#5.5x, %-#5.5x, %-#5.5x", 0, 5, -1, -10, 0x1234, -1862, 0xABCDE, INT_MIN, INT_MAX, UINT_MAX);
	/* 197 */ test_print_long_ten("%-#5.10x, %-#5.10x, %-#5.10x, %-#5.10x, %-#5.10x, %-#5.10x, %-#5.10x, %-#5.10x, %-#5.10x, %-#5.10x", 0, 5, -1, -10, 0x1234, -1862, 0xABCDE, INT_MIN, INT_MAX, UINT_MAX);
	/* 198 */ test_print_long_ten("%-#5.100x, %-#5.100x, %-#5.100x, %-#5.100x, %-#5.100x, %-#5.100x, %-#5.100x, %-#5.100x, %-#5.100x, %-#5.100x", 0, 5, -1, -10, 0x1234, -1862, 0xABCDE, INT_MIN, INT_MAX, UINT_MAX);
	/* 199 */ test_print_long_ten("%-#10.x, %-#10.x, %-#10.x, %-#10.x, %-#10.x, %-#10.x, %-#10.x, %-#10.x, %-#10.x, %-#10.x", 0, 5, -1, -10, 0x1234, -1862, 0xABCDE, INT_MIN, INT_MAX, UINT_MAX);
	/* 200 */ test_print_long_ten("%-#10.0x, %-#10.0x, %-#10.0x, %-#10.0x, %-#10.0x, %-#10.0x, %-#10.0x, %-#10.0x, %-#10.0x, %-#10.0x", 0, 5, -1, -10, 0x1234, -1862, 0xABCDE, INT_MIN, INT_MAX, UINT_MAX);
	/* 201 */ test_print_long_ten("%-#10.1x, %-#10.1x, %-#10.1x, %-#10.1x, %-#10.1x, %-#10.1x, %-#10.1x, %-#10.1x, %-#10.1x, %-#10.1x", 0, 5, -1, -10, 0x1234, -1862, 0xABCDE, INT_MIN, INT_MAX, UINT_MAX);
	/* 202 */ test_print_long_ten("%-#10.5x, %-#10.5x, %-#10.5x, %-#10.5x, %-#10.5x, %-#10.5x, %-#10.5x, %-#10.5x, %-#10.5x, %-#10.5x", 0, 5, -1, -10, 0x1234, -1862, 0xABCDE, INT_MIN, INT_MAX, UINT_MAX);
	/* 203 */ test_print_long_ten("%-#10.10x, %-#10.10x, %-#10.10x, %-#10.10x, %-#10.10x, %-#10.10x, %-#10.10x, %-#10.10x, %-#10.10x, %-#10.10x", 0, 5, -1, -10, 0x1234, -1862, 0xABCDE, INT_MIN, INT_MAX, UINT_MAX);
	/* 204 */ test_print_long_ten("%-#10.100x, %-#10.100x, %-#10.100x, %-#10.100x, %-#10.100x, %-#10.100x, %-#10.100x, %-#10.100x, %-#10.100x, %-#10.100x", 0, 5, -1, -10, 0x1234, -1862, 0xABCDE, INT_MIN, INT_MAX, UINT_MAX);
	/* 205 */ test_print_long_ten("%-#100.x, %-#100.x, %-#100.x, %-#100.x, %-#100.x, %-#100.x, %-#100.x, %-#100.x, %-#100.x, %-#100.x", 0, 5, -1, -10, 0x1234, -1862, 0xABCDE, INT_MIN, INT_MAX, UINT_MAX);
	/* 206 */ test_print_long_ten("%-#100.0x, %-#100.0x, %-#100.0x, %-#100.0x, %-#100.0x, %-#100.0x, %-#100.0x, %-#100.0x, %-#100.0x, %-#100.0x", 0, 5, -1, -10, 0x1234, -1862, 0xABCDE, INT_MIN, INT_MAX, UINT_MAX);
	/* 207 */ test_print_long_ten("%-#100.1x, %-#100.1x, %-#100.1x, %-#100.1x, %-#100.1x, %-#100.1x, %-#100.1x, %-#100.1x, %-#100.1x, %-#100.1x", 0, 5, -1, -10, 0x1234, -1862, 0xABCDE, INT_MIN, INT_MAX, UINT_MAX);
	/* 208 */ test_print_long_ten("%-#100.5x, %-#100.5x, %-#100.5x, %-#100.5x, %-#100.5x, %-#100.5x, %-#100.5x, %-#100.5x, %-#100.5x, %-#100.5x", 0, 5, -1, -10, 0x1234, -1862, 0xABCDE, INT_MIN, INT_MAX, UINT_MAX);
	/* 209 */ test_print_long_ten("%-#100.10x, %-#100.10x, %-#100.10x, %-#100.10x, %-#100.10x, %-#100.10x, %-#100.10x, %-#100.10x, %-#100.10x, %-#100.10x", 0, 5, -1, -10, 0x1234, -1862, 0xABCDE, INT_MIN, INT_MAX, UINT_MAX);
	/* 210 */ test_print_long_ten("%-#100.100x, %-#100.100x, %-#100.100x, %-#100.100x, %-#100.100x, %-#100.100x, %-#100.100x, %-#100.100x, %-#100.100x, %-#100.100x", 0, 5, -1, -10, 0x1234, -1862, 0xABCDE, INT_MIN, INT_MAX, UINT_MAX);
}

void test_X() {
	g_current_test_id = 'X';
	/* 1 */ test_print_long_ten("%X, %X, %X, %X, %X, %X, %X, %X, %X, %X", 0, 5, -1, -10, 0x1234, -1862, 0xABCDE, INT_MIN, INT_MAX, UINT_MAX);
	/* 2 */ test_print_long_ten("%1X, %1X, %1X, %1X, %1X, %1X, %1X, %1X, %1X, %1X", 0, 5, -1, -10, 0x1234, -1862, 0xABCDE, INT_MIN, INT_MAX, UINT_MAX);
	/* 3 */ test_print_long_ten("%5X, %5X, %5X, %5X, %5X, %5X, %5X, %5X, %5X, %5X", 0, 5, -1, -10, 0x1234, -1862, 0xABCDE, INT_MIN, INT_MAX, UINT_MAX);
	/* 4 */ test_print_long_ten("%10X, %10X, %10X, %10X, %10X, %10X, %10X, %10X, %10X, %10X", 0, 5, -1, -10, 0x1234, -1862, 0xABCDE, INT_MIN, INT_MAX, UINT_MAX);
	/* 5 */ test_print_long_ten("%100X, %100X, %100X, %100X, %100X, %100X, %100X, %100X, %100X, %100X", 0, 5, -1, -10, 0x1234, -1862, 0xABCDE, INT_MIN, INT_MAX, UINT_MAX);
	/* 6 */ test_print_long_ten("%.X, %.X, %.X, %.X, %.X, %.X, %.X, %.X, %.X, %.X", 0, 5, -1, -10, 0x1234, -1862, 0xABCDE, INT_MIN, INT_MAX, UINT_MAX);
	/* 7 */ test_print_long_ten("%.0X, %.0X, %.0X, %.0X, %.0X, %.0X, %.0X, %.0X, %.0X, %.0X", 0, 5, -1, -10, 0x1234, -1862, 0xABCDE, INT_MIN, INT_MAX, UINT_MAX);
	/* 8 */ test_print_long_ten("%.1X, %.1X, %.1X, %.1X, %.1X, %.1X, %.1X, %.1X, %.1X, %.1X", 0, 5, -1, -10, 0x1234, -1862, 0xABCDE, INT_MIN, INT_MAX, UINT_MAX);
	/* 9 */ test_print_long_ten("%.5X, %.5X, %.5X, %.5X, %.5X, %.5X, %.5X, %.5X, %.5X, %.5X", 0, 5, -1, -10, 0x1234, -1862, 0xABCDE, INT_MIN, INT_MAX, UINT_MAX);
	/* 10 */ test_print_long_ten("%.10X, %.10X, %.10X, %.10X, %.10X, %.10X, %.10X, %.10X, %.10X, %.10X", 0, 5, -1, -10, 0x1234, -1862, 0xABCDE, INT_MIN, INT_MAX, UINT_MAX);
	/* 11 */ test_print_long_ten("%.100X, %.100X, %.100X, %.100X, %.100X, %.100X, %.100X, %.100X, %.100X, %.100X", 0, 5, -1, -10, 0x1234, -1862, 0xABCDE, INT_MIN, INT_MAX, UINT_MAX);
	/* 12 */ test_print_long_ten("%1.X, %1.X, %1.X, %1.X, %1.X, %1.X, %1.X, %1.X, %1.X, %1.X", 0, 5, -1, -10, 0x1234, -1862, 0xABCDE, INT_MIN, INT_MAX, UINT_MAX);
	/* 13 */ test_print_long_ten("%1.0X, %1.0X, %1.0X, %1.0X, %1.0X, %1.0X, %1.0X, %1.0X, %1.0X, %1.0X", 0, 5, -1, -10, 0x1234, -1862, 0xABCDE, INT_MIN, INT_MAX, UINT_MAX);
	/* 14 */ test_print_long_ten("%1.1X, %1.1X, %1.1X, %1.1X, %1.1X, %1.1X, %1.1X, %1.1X, %1.1X, %1.1X", 0, 5, -1, -10, 0x1234, -1862, 0xABCDE, INT_MIN, INT_MAX, UINT_MAX);
	/* 15 */ test_print_long_ten("%1.5X, %1.5X, %1.5X, %1.5X, %1.5X, %1.5X, %1.5X, %1.5X, %1.5X, %1.5X", 0, 5, -1, -10, 0x1234, -1862, 0xABCDE, INT_MIN, INT_MAX, UINT_MAX);
	/* 16 */ test_print_long_ten("%1.10X, %1.10X, %1.10X, %1.10X, %1.10X, %1.10X, %1.10X, %1.10X, %1.10X, %1.10X", 0, 5, -1, -10, 0x1234, -1862, 0xABCDE, INT_MIN, INT_MAX, UINT_MAX);
	/* 17 */ test_print_long_ten("%1.100X, %1.100X, %1.100X, %1.100X, %1.100X, %1.100X, %1.100X, %1.100X, %1.100X, %1.100X", 0, 5, -1, -10, 0x1234, -1862, 0xABCDE, INT_MIN, INT_MAX, UINT_MAX);
	/* 18 */ test_print_long_ten("%5.X, %5.X, %5.X, %5.X, %5.X, %5.X, %5.X, %5.X, %5.X, %5.X", 0, 5, -1, -10, 0x1234, -1862, 0xABCDE, INT_MIN, INT_MAX, UINT_MAX);
	/* 19 */ test_print_long_ten("%5.0X, %5.0X, %5.0X, %5.0X, %5.0X, %5.0X, %5.0X, %5.0X, %5.0X, %5.0X", 0, 5, -1, -10, 0x1234, -1862, 0xABCDE, INT_MIN, INT_MAX, UINT_MAX);
	/* 20 */ test_print_long_ten("%5.1X, %5.1X, %5.1X, %5.1X, %5.1X, %5.1X, %5.1X, %5.1X, %5.1X, %5.1X", 0, 5, -1, -10, 0x1234, -1862, 0xABCDE, INT_MIN, INT_MAX, UINT_MAX);
	/* 21 */ test_print_long_ten("%5.5X, %5.5X, %5.5X, %5.5X, %5.5X, %5.5X, %5.5X, %5.5X, %5.5X, %5.5X", 0, 5, -1, -10, 0x1234, -1862, 0xABCDE, INT_MIN, INT_MAX, UINT_MAX);
	/* 22 */ test_print_long_ten("%5.10X, %5.10X, %5.10X, %5.10X, %5.10X, %5.10X, %5.10X, %5.10X, %5.10X, %5.10X", 0, 5, -1, -10, 0x1234, -1862, 0xABCDE, INT_MIN, INT_MAX, UINT_MAX);
	/* 23 */ test_print_long_ten("%5.100X, %5.100X, %5.100X, %5.100X, %5.100X, %5.100X, %5.100X, %5.100X, %5.100X, %5.100X", 0, 5, -1, -10, 0x1234, -1862, 0xABCDE, INT_MIN, INT_MAX, UINT_MAX);
	/* 24 */ test_print_long_ten("%10.X, %10.X, %10.X, %10.X, %10.X, %10.X, %10.X, %10.X, %10.X, %10.X", 0, 5, -1, -10, 0x1234, -1862, 0xABCDE, INT_MIN, INT_MAX, UINT_MAX);
	/* 25 */ test_print_long_ten("%10.0X, %10.0X, %10.0X, %10.0X, %10.0X, %10.0X, %10.0X, %10.0X, %10.0X, %10.0X", 0, 5, -1, -10, 0x1234, -1862, 0xABCDE, INT_MIN, INT_MAX, UINT_MAX);
	/* 26 */ test_print_long_ten("%10.1X, %10.1X, %10.1X, %10.1X, %10.1X, %10.1X, %10.1X, %10.1X, %10.1X, %10.1X", 0, 5, -1, -10, 0x1234, -1862, 0xABCDE, INT_MIN, INT_MAX, UINT_MAX);
	/* 27 */ test_print_long_ten("%10.5X, %10.5X, %10.5X, %10.5X, %10.5X, %10.5X, %10.5X, %10.5X, %10.5X, %10.5X", 0, 5, -1, -10, 0x1234, -1862, 0xABCDE, INT_MIN, INT_MAX, UINT_MAX);
	/* 28 */ test_print_long_ten("%10.10X, %10.10X, %10.10X, %10.10X, %10.10X, %10.10X, %10.10X, %10.10X, %10.10X, %10.10X", 0, 5, -1, -10, 0x1234, -1862, 0xABCDE, INT_MIN, INT_MAX, UINT_MAX);
	/* 29 */ test_print_long_ten("%10.100X, %10.100X, %10.100X, %10.100X, %10.100X, %10.100X, %10.100X, %10.100X, %10.100X, %10.100X", 0, 5, -1, -10, 0x1234, -1862, 0xABCDE, INT_MIN, INT_MAX, UINT_MAX);
	/* 30 */ test_print_long_ten("%100.X, %100.X, %100.X, %100.X, %100.X, %100.X, %100.X, %100.X, %100.X, %100.X", 0, 5, -1, -10, 0x1234, -1862, 0xABCDE, INT_MIN, INT_MAX, UINT_MAX);
	/* 31 */ test_print_long_ten("%100.0X, %100.0X, %100.0X, %100.0X, %100.0X, %100.0X, %100.0X, %100.0X, %100.0X, %100.0X", 0, 5, -1, -10, 0x1234, -1862, 0xABCDE, INT_MIN, INT_MAX, UINT_MAX);
	/* 32 */ test_print_long_ten("%100.1X, %100.1X, %100.1X, %100.1X, %100.1X, %100.1X, %100.1X, %100.1X, %100.1X, %100.1X", 0, 5, -1, -10, 0x1234, -1862, 0xABCDE, INT_MIN, INT_MAX, UINT_MAX);
	/* 33 */ test_print_long_ten("%100.5X, %100.5X, %100.5X, %100.5X, %100.5X, %100.5X, %100.5X, %100.5X, %100.5X, %100.5X", 0, 5, -1, -10, 0x1234, -1862, 0xABCDE, INT_MIN, INT_MAX, UINT_MAX);
	/* 34 */ test_print_long_ten("%100.10X, %100.10X, %100.10X, %100.10X, %100.10X, %100.10X, %100.10X, %100.10X, %100.10X, %100.10X", 0, 5, -1, -10, 0x1234, -1862, 0xABCDE, INT_MIN, INT_MAX, UINT_MAX);
	/* 35 */ test_print_long_ten("%100.100X, %100.100X, %100.100X, %100.100X, %100.100X, %100.100X, %100.100X, %100.100X, %100.100X, %100.100X", 0, 5, -1, -10, 0x1234, -1862, 0xABCDE, INT_MIN, INT_MAX, UINT_MAX);
	/* 36 */ test_print_long_ten("%#X, %#X, %#X, %#X, %#X, %#X, %#X, %#X, %#X, %#X", 0, 5, -1, -10, 0x1234, -1862, 0xABCDE, INT_MIN, INT_MAX, UINT_MAX);
	/* 37 */ test_print_long_ten("%#1X, %#1X, %#1X, %#1X, %#1X, %#1X, %#1X, %#1X, %#1X, %#1X", 0, 5, -1, -10, 0x1234, -1862, 0xABCDE, INT_MIN, INT_MAX, UINT_MAX);
	/* 38 */ test_print_long_ten("%#5X, %#5X, %#5X, %#5X, %#5X, %#5X, %#5X, %#5X, %#5X, %#5X", 0, 5, -1, -10, 0x1234, -1862, 0xABCDE, INT_MIN, INT_MAX, UINT_MAX);
	/* 39 */ test_print_long_ten("%#10X, %#10X, %#10X, %#10X, %#10X, %#10X, %#10X, %#10X, %#10X, %#10X", 0, 5, -1, -10, 0x1234, -1862, 0xABCDE, INT_MIN, INT_MAX, UINT_MAX);
	/* 40 */ test_print_long_ten("%#100X, %#100X, %#100X, %#100X, %#100X, %#100X, %#100X, %#100X, %#100X, %#100X", 0, 5, -1, -10, 0x1234, -1862, 0xABCDE, INT_MIN, INT_MAX, UINT_MAX);
	/* 41 */ test_print_long_ten("%#.X, %#.X, %#.X, %#.X, %#.X, %#.X, %#.X, %#.X, %#.X, %#.X", 0, 5, -1, -10, 0x1234, -1862, 0xABCDE, INT_MIN, INT_MAX, UINT_MAX);
	/* 42 */ test_print_long_ten("%#.0X, %#.0X, %#.0X, %#.0X, %#.0X, %#.0X, %#.0X, %#.0X, %#.0X, %#.0X", 0, 5, -1, -10, 0x1234, -1862, 0xABCDE, INT_MIN, INT_MAX, UINT_MAX);
	/* 43 */ test_print_long_ten("%#.1X, %#.1X, %#.1X, %#.1X, %#.1X, %#.1X, %#.1X, %#.1X, %#.1X, %#.1X", 0, 5, -1, -10, 0x1234, -1862, 0xABCDE, INT_MIN, INT_MAX, UINT_MAX);
	/* 44 */ test_print_long_ten("%#.5X, %#.5X, %#.5X, %#.5X, %#.5X, %#.5X, %#.5X, %#.5X, %#.5X, %#.5X", 0, 5, -1, -10, 0x1234, -1862, 0xABCDE, INT_MIN, INT_MAX, UINT_MAX);
	/* 45 */ test_print_long_ten("%#.10X, %#.10X, %#.10X, %#.10X, %#.10X, %#.10X, %#.10X, %#.10X, %#.10X, %#.10X", 0, 5, -1, -10, 0x1234, -1862, 0xABCDE, INT_MIN, INT_MAX, UINT_MAX);
	/* 46 */ test_print_long_ten("%#.100X, %#.100X, %#.100X, %#.100X, %#.100X, %#.100X, %#.100X, %#.100X, %#.100X, %#.100X", 0, 5, -1, -10, 0x1234, -1862, 0xABCDE, INT_MIN, INT_MAX, UINT_MAX);
	/* 47 */ test_print_long_ten("%#1.X, %#1.X, %#1.X, %#1.X, %#1.X, %#1.X, %#1.X, %#1.X, %#1.X, %#1.X", 0, 5, -1, -10, 0x1234, -1862, 0xABCDE, INT_MIN, INT_MAX, UINT_MAX);
	/* 48 */ test_print_long_ten("%#1.0X, %#1.0X, %#1.0X, %#1.0X, %#1.0X, %#1.0X, %#1.0X, %#1.0X, %#1.0X, %#1.0X", 0, 5, -1, -10, 0x1234, -1862, 0xABCDE, INT_MIN, INT_MAX, UINT_MAX);
	/* 49 */ test_print_long_ten("%#1.1X, %#1.1X, %#1.1X, %#1.1X, %#1.1X, %#1.1X, %#1.1X, %#1.1X, %#1.1X, %#1.1X", 0, 5, -1, -10, 0x1234, -1862, 0xABCDE, INT_MIN, INT_MAX, UINT_MAX);
	/* 50 */ test_print_long_ten("%#1.5X, %#1.5X, %#1.5X, %#1.5X, %#1.5X, %#1.5X, %#1.5X, %#1.5X, %#1.5X, %#1.5X", 0, 5, -1, -10, 0x1234, -1862, 0xABCDE, INT_MIN, INT_MAX, UINT_MAX);
	/* 51 */ test_print_long_ten("%#1.10X, %#1.10X, %#1.10X, %#1.10X, %#1.10X, %#1.10X, %#1.10X, %#1.10X, %#1.10X, %#1.10X", 0, 5, -1, -10, 0x1234, -1862, 0xABCDE, INT_MIN, INT_MAX, UINT_MAX);
	/* 52 */ test_print_long_ten("%#1.100X, %#1.100X, %#1.100X, %#1.100X, %#1.100X, %#1.100X, %#1.100X, %#1.100X, %#1.100X, %#1.100X", 0, 5, -1, -10, 0x1234, -1862, 0xABCDE, INT_MIN, INT_MAX, UINT_MAX);
	/* 53 */ test_print_long_ten("%#5.X, %#5.X, %#5.X, %#5.X, %#5.X, %#5.X, %#5.X, %#5.X, %#5.X, %#5.X", 0, 5, -1, -10, 0x1234, -1862, 0xABCDE, INT_MIN, INT_MAX, UINT_MAX);
	/* 54 */ test_print_long_ten("%#5.0X, %#5.0X, %#5.0X, %#5.0X, %#5.0X, %#5.0X, %#5.0X, %#5.0X, %#5.0X, %#5.0X", 0, 5, -1, -10, 0x1234, -1862, 0xABCDE, INT_MIN, INT_MAX, UINT_MAX);
	/* 55 */ test_print_long_ten("%#5.1X, %#5.1X, %#5.1X, %#5.1X, %#5.1X, %#5.1X, %#5.1X, %#5.1X, %#5.1X, %#5.1X", 0, 5, -1, -10, 0x1234, -1862, 0xABCDE, INT_MIN, INT_MAX, UINT_MAX);
	/* 56 */ test_print_long_ten("%#5.5X, %#5.5X, %#5.5X, %#5.5X, %#5.5X, %#5.5X, %#5.5X, %#5.5X, %#5.5X, %#5.5X", 0, 5, -1, -10, 0x1234, -1862, 0xABCDE, INT_MIN, INT_MAX, UINT_MAX);
	/* 57 */ test_print_long_ten("%#5.10X, %#5.10X, %#5.10X, %#5.10X, %#5.10X, %#5.10X, %#5.10X, %#5.10X, %#5.10X, %#5.10X", 0, 5, -1, -10, 0x1234, -1862, 0xABCDE, INT_MIN, INT_MAX, UINT_MAX);
	/* 58 */ test_print_long_ten("%#5.100X, %#5.100X, %#5.100X, %#5.100X, %#5.100X, %#5.100X, %#5.100X, %#5.100X, %#5.100X, %#5.100X", 0, 5, -1, -10, 0x1234, -1862, 0xABCDE, INT_MIN, INT_MAX, UINT_MAX);
	/* 59 */ test_print_long_ten("%#10.X, %#10.X, %#10.X, %#10.X, %#10.X, %#10.X, %#10.X, %#10.X, %#10.X, %#10.X", 0, 5, -1, -10, 0x1234, -1862, 0xABCDE, INT_MIN, INT_MAX, UINT_MAX);
	/* 60 */ test_print_long_ten("%#10.0X, %#10.0X, %#10.0X, %#10.0X, %#10.0X, %#10.0X, %#10.0X, %#10.0X, %#10.0X, %#10.0X", 0, 5, -1, -10, 0x1234, -1862, 0xABCDE, INT_MIN, INT_MAX, UINT_MAX);
	/* 61 */ test_print_long_ten("%#10.1X, %#10.1X, %#10.1X, %#10.1X, %#10.1X, %#10.1X, %#10.1X, %#10.1X, %#10.1X, %#10.1X", 0, 5, -1, -10, 0x1234, -1862, 0xABCDE, INT_MIN, INT_MAX, UINT_MAX);
	/* 62 */ test_print_long_ten("%#10.5X, %#10.5X, %#10.5X, %#10.5X, %#10.5X, %#10.5X, %#10.5X, %#10.5X, %#10.5X, %#10.5X", 0, 5, -1, -10, 0x1234, -1862, 0xABCDE, INT_MIN, INT_MAX, UINT_MAX);
	/* 63 */ test_print_long_ten("%#10.10X, %#10.10X, %#10.10X, %#10.10X, %#10.10X, %#10.10X, %#10.10X, %#10.10X, %#10.10X, %#10.10X", 0, 5, -1, -10, 0x1234, -1862, 0xABCDE, INT_MIN, INT_MAX, UINT_MAX);
	/* 64 */ test_print_long_ten("%#10.100X, %#10.100X, %#10.100X, %#10.100X, %#10.100X, %#10.100X, %#10.100X, %#10.100X, %#10.100X, %#10.100X", 0, 5, -1, -10, 0x1234, -1862, 0xABCDE, INT_MIN, INT_MAX, UINT_MAX);
	/* 65 */ test_print_long_ten("%#100.X, %#100.X, %#100.X, %#100.X, %#100.X, %#100.X, %#100.X, %#100.X, %#100.X, %#100.X", 0, 5, -1, -10, 0x1234, -1862, 0xABCDE, INT_MIN, INT_MAX, UINT_MAX);
	/* 66 */ test_print_long_ten("%#100.0X, %#100.0X, %#100.0X, %#100.0X, %#100.0X, %#100.0X, %#100.0X, %#100.0X, %#100.0X, %#100.0X", 0, 5, -1, -10, 0x1234, -1862, 0xABCDE, INT_MIN, INT_MAX, UINT_MAX);
	/* 67 */ test_print_long_ten("%#100.1X, %#100.1X, %#100.1X, %#100.1X, %#100.1X, %#100.1X, %#100.1X, %#100.1X, %#100.1X, %#100.1X", 0, 5, -1, -10, 0x1234, -1862, 0xABCDE, INT_MIN, INT_MAX, UINT_MAX);
	/* 68 */ test_print_long_ten("%#100.5X, %#100.5X, %#100.5X, %#100.5X, %#100.5X, %#100.5X, %#100.5X, %#100.5X, %#100.5X, %#100.5X", 0, 5, -1, -10, 0x1234, -1862, 0xABCDE, INT_MIN, INT_MAX, UINT_MAX);
	/* 69 */ test_print_long_ten("%#100.10X, %#100.10X, %#100.10X, %#100.10X, %#100.10X, %#100.10X, %#100.10X, %#100.10X, %#100.10X, %#100.10X", 0, 5, -1, -10, 0x1234, -1862, 0xABCDE, INT_MIN, INT_MAX, UINT_MAX);
	/* 70 */ test_print_long_ten("%#100.100X, %#100.100X, %#100.100X, %#100.100X, %#100.100X, %#100.100X, %#100.100X, %#100.100X, %#100.100X, %#100.100X", 0, 5, -1, -10, 0x1234, -1862, 0xABCDE, INT_MIN, INT_MAX, UINT_MAX);
	/* 71 */ test_print_long_ten("%0X, %0X, %0X, %0X, %0X, %0X, %0X, %0X, %0X, %0X", 0, 5, -1, -10, 0x1234, -1862, 0xABCDE, INT_MIN, INT_MAX, UINT_MAX);
	/* 72 */ test_print_long_ten("%01X, %01X, %01X, %01X, %01X, %01X, %01X, %01X, %01X, %01X", 0, 5, -1, -10, 0x1234, -1862, 0xABCDE, INT_MIN, INT_MAX, UINT_MAX);
	/* 73 */ test_print_long_ten("%05X, %05X, %05X, %05X, %05X, %05X, %05X, %05X, %05X, %05X", 0, 5, -1, -10, 0x1234, -1862, 0xABCDE, INT_MIN, INT_MAX, UINT_MAX);
	/* 74 */ test_print_long_ten("%010X, %010X, %010X, %010X, %010X, %010X, %010X, %010X, %010X, %010X", 0, 5, -1, -10, 0x1234, -1862, 0xABCDE, INT_MIN, INT_MAX, UINT_MAX);
	/* 75 */ test_print_long_ten("%0100X, %0100X, %0100X, %0100X, %0100X, %0100X, %0100X, %0100X, %0100X, %0100X", 0, 5, -1, -10, 0x1234, -1862, 0xABCDE, INT_MIN, INT_MAX, UINT_MAX);
	/* 76 */ test_print_long_ten("%0.X, %0.X, %0.X, %0.X, %0.X, %0.X, %0.X, %0.X, %0.X, %0.X", 0, 5, -1, -10, 0x1234, -1862, 0xABCDE, INT_MIN, INT_MAX, UINT_MAX);
	/* 77 */ test_print_long_ten("%0.0X, %0.0X, %0.0X, %0.0X, %0.0X, %0.0X, %0.0X, %0.0X, %0.0X, %0.0X", 0, 5, -1, -10, 0x1234, -1862, 0xABCDE, INT_MIN, INT_MAX, UINT_MAX);
	/* 78 */ test_print_long_ten("%0.1X, %0.1X, %0.1X, %0.1X, %0.1X, %0.1X, %0.1X, %0.1X, %0.1X, %0.1X", 0, 5, -1, -10, 0x1234, -1862, 0xABCDE, INT_MIN, INT_MAX, UINT_MAX);
	/* 79 */ test_print_long_ten("%0.5X, %0.5X, %0.5X, %0.5X, %0.5X, %0.5X, %0.5X, %0.5X, %0.5X, %0.5X", 0, 5, -1, -10, 0x1234, -1862, 0xABCDE, INT_MIN, INT_MAX, UINT_MAX);
	/* 80 */ test_print_long_ten("%0.10X, %0.10X, %0.10X, %0.10X, %0.10X, %0.10X, %0.10X, %0.10X, %0.10X, %0.10X", 0, 5, -1, -10, 0x1234, -1862, 0xABCDE, INT_MIN, INT_MAX, UINT_MAX);
	/* 81 */ test_print_long_ten("%0.100X, %0.100X, %0.100X, %0.100X, %0.100X, %0.100X, %0.100X, %0.100X, %0.100X, %0.100X", 0, 5, -1, -10, 0x1234, -1862, 0xABCDE, INT_MIN, INT_MAX, UINT_MAX);
	/* 82 */ test_print_long_ten("%01.X, %01.X, %01.X, %01.X, %01.X, %01.X, %01.X, %01.X, %01.X, %01.X", 0, 5, -1, -10, 0x1234, -1862, 0xABCDE, INT_MIN, INT_MAX, UINT_MAX);
	/* 83 */ test_print_long_ten("%01.0X, %01.0X, %01.0X, %01.0X, %01.0X, %01.0X, %01.0X, %01.0X, %01.0X, %01.0X", 0, 5, -1, -10, 0x1234, -1862, 0xABCDE, INT_MIN, INT_MAX, UINT_MAX);
	/* 84 */ test_print_long_ten("%01.1X, %01.1X, %01.1X, %01.1X, %01.1X, %01.1X, %01.1X, %01.1X, %01.1X, %01.1X", 0, 5, -1, -10, 0x1234, -1862, 0xABCDE, INT_MIN, INT_MAX, UINT_MAX);
	/* 85 */ test_print_long_ten("%01.5X, %01.5X, %01.5X, %01.5X, %01.5X, %01.5X, %01.5X, %01.5X, %01.5X, %01.5X", 0, 5, -1, -10, 0x1234, -1862, 0xABCDE, INT_MIN, INT_MAX, UINT_MAX);
	/* 86 */ test_print_long_ten("%01.10X, %01.10X, %01.10X, %01.10X, %01.10X, %01.10X, %01.10X, %01.10X, %01.10X, %01.10X", 0, 5, -1, -10, 0x1234, -1862, 0xABCDE, INT_MIN, INT_MAX, UINT_MAX);
	/* 87 */ test_print_long_ten("%01.100X, %01.100X, %01.100X, %01.100X, %01.100X, %01.100X, %01.100X, %01.100X, %01.100X, %01.100X", 0, 5, -1, -10, 0x1234, -1862, 0xABCDE, INT_MIN, INT_MAX, UINT_MAX);
	/* 88 */ test_print_long_ten("%05.X, %05.X, %05.X, %05.X, %05.X, %05.X, %05.X, %05.X, %05.X, %05.X", 0, 5, -1, -10, 0x1234, -1862, 0xABCDE, INT_MIN, INT_MAX, UINT_MAX);
	/* 89 */ test_print_long_ten("%05.0X, %05.0X, %05.0X, %05.0X, %05.0X, %05.0X, %05.0X, %05.0X, %05.0X, %05.0X", 0, 5, -1, -10, 0x1234, -1862, 0xABCDE, INT_MIN, INT_MAX, UINT_MAX);
	/* 90 */ test_print_long_ten("%05.1X, %05.1X, %05.1X, %05.1X, %05.1X, %05.1X, %05.1X, %05.1X, %05.1X, %05.1X", 0, 5, -1, -10, 0x1234, -1862, 0xABCDE, INT_MIN, INT_MAX, UINT_MAX);
	/* 91 */ test_print_long_ten("%05.5X, %05.5X, %05.5X, %05.5X, %05.5X, %05.5X, %05.5X, %05.5X, %05.5X, %05.5X", 0, 5, -1, -10, 0x1234, -1862, 0xABCDE, INT_MIN, INT_MAX, UINT_MAX);
	/* 92 */ test_print_long_ten("%05.10X, %05.10X, %05.10X, %05.10X, %05.10X, %05.10X, %05.10X, %05.10X, %05.10X, %05.10X", 0, 5, -1, -10, 0x1234, -1862, 0xABCDE, INT_MIN, INT_MAX, UINT_MAX);
	/* 93 */ test_print_long_ten("%05.100X, %05.100X, %05.100X, %05.100X, %05.100X, %05.100X, %05.100X, %05.100X, %05.100X, %05.100X", 0, 5, -1, -10, 0x1234, -1862, 0xABCDE, INT_MIN, INT_MAX, UINT_MAX);
	/* 94 */ test_print_long_ten("%010.X, %010.X, %010.X, %010.X, %010.X, %010.X, %010.X, %010.X, %010.X, %010.X", 0, 5, -1, -10, 0x1234, -1862, 0xABCDE, INT_MIN, INT_MAX, UINT_MAX);
	/* 95 */ test_print_long_ten("%010.0X, %010.0X, %010.0X, %010.0X, %010.0X, %010.0X, %010.0X, %010.0X, %010.0X, %010.0X", 0, 5, -1, -10, 0x1234, -1862, 0xABCDE, INT_MIN, INT_MAX, UINT_MAX);
	/* 96 */ test_print_long_ten("%010.1X, %010.1X, %010.1X, %010.1X, %010.1X, %010.1X, %010.1X, %010.1X, %010.1X, %010.1X", 0, 5, -1, -10, 0x1234, -1862, 0xABCDE, INT_MIN, INT_MAX, UINT_MAX);
	/* 97 */ test_print_long_ten("%010.5X, %010.5X, %010.5X, %010.5X, %010.5X, %010.5X, %010.5X, %010.5X, %010.5X, %010.5X", 0, 5, -1, -10, 0x1234, -1862, 0xABCDE, INT_MIN, INT_MAX, UINT_MAX);
	/* 98 */ test_print_long_ten("%010.10X, %010.10X, %010.10X, %010.10X, %010.10X, %010.10X, %010.10X, %010.10X, %010.10X, %010.10X", 0, 5, -1, -10, 0x1234, -1862, 0xABCDE, INT_MIN, INT_MAX, UINT_MAX);
	/* 99 */ test_print_long_ten("%010.100X, %010.100X, %010.100X, %010.100X, %010.100X, %010.100X, %010.100X, %010.100X, %010.100X, %010.100X", 0, 5, -1, -10, 0x1234, -1862, 0xABCDE, INT_MIN, INT_MAX, UINT_MAX);
	/* 100 */ test_print_long_ten("%0100.X, %0100.X, %0100.X, %0100.X, %0100.X, %0100.X, %0100.X, %0100.X, %0100.X, %0100.X", 0, 5, -1, -10, 0x1234, -1862, 0xABCDE, INT_MIN, INT_MAX, UINT_MAX);
	/* 101 */ test_print_long_ten("%0100.0X, %0100.0X, %0100.0X, %0100.0X, %0100.0X, %0100.0X, %0100.0X, %0100.0X, %0100.0X, %0100.0X", 0, 5, -1, -10, 0x1234, -1862, 0xABCDE, INT_MIN, INT_MAX, UINT_MAX);
	/* 102 */ test_print_long_ten("%0100.1X, %0100.1X, %0100.1X, %0100.1X, %0100.1X, %0100.1X, %0100.1X, %0100.1X, %0100.1X, %0100.1X", 0, 5, -1, -10, 0x1234, -1862, 0xABCDE, INT_MIN, INT_MAX, UINT_MAX);
	/* 103 */ test_print_long_ten("%0100.5X, %0100.5X, %0100.5X, %0100.5X, %0100.5X, %0100.5X, %0100.5X, %0100.5X, %0100.5X, %0100.5X", 0, 5, -1, -10, 0x1234, -1862, 0xABCDE, INT_MIN, INT_MAX, UINT_MAX);
	/* 104 */ test_print_long_ten("%0100.10X, %0100.10X, %0100.10X, %0100.10X, %0100.10X, %0100.10X, %0100.10X, %0100.10X, %0100.10X, %0100.10X", 0, 5, -1, -10, 0x1234, -1862, 0xABCDE, INT_MIN, INT_MAX, UINT_MAX);
	/* 105 */ test_print_long_ten("%0100.100X, %0100.100X, %0100.100X, %0100.100X, %0100.100X, %0100.100X, %0100.100X, %0100.100X, %0100.100X, %0100.100X", 0, 5, -1, -10, 0x1234, -1862, 0xABCDE, INT_MIN, INT_MAX, UINT_MAX);
	/* 106 */ test_print_long_ten("%0#X, %0#X, %0#X, %0#X, %0#X, %0#X, %0#X, %0#X, %0#X, %0#X", 0, 5, -1, -10, 0x1234, -1862, 0xABCDE, INT_MIN, INT_MAX, UINT_MAX);
	/* 107 */ test_print_long_ten("%0#1X, %0#1X, %0#1X, %0#1X, %0#1X, %0#1X, %0#1X, %0#1X, %0#1X, %0#1X", 0, 5, -1, -10, 0x1234, -1862, 0xABCDE, INT_MIN, INT_MAX, UINT_MAX);
	/* 108 */ test_print_long_ten("%0#5X, %0#5X, %0#5X, %0#5X, %0#5X, %0#5X, %0#5X, %0#5X, %0#5X, %0#5X", 0, 5, -1, -10, 0x1234, -1862, 0xABCDE, INT_MIN, INT_MAX, UINT_MAX);
	/* 109 */ test_print_long_ten("%0#10X, %0#10X, %0#10X, %0#10X, %0#10X, %0#10X, %0#10X, %0#10X, %0#10X, %0#10X", 0, 5, -1, -10, 0x1234, -1862, 0xABCDE, INT_MIN, INT_MAX, UINT_MAX);
	/* 110 */ test_print_long_ten("%0#100X, %0#100X, %0#100X, %0#100X, %0#100X, %0#100X, %0#100X, %0#100X, %0#100X, %0#100X", 0, 5, -1, -10, 0x1234, -1862, 0xABCDE, INT_MIN, INT_MAX, UINT_MAX);
	/* 111 */ test_print_long_ten("%0#.X, %0#.X, %0#.X, %0#.X, %0#.X, %0#.X, %0#.X, %0#.X, %0#.X, %0#.X", 0, 5, -1, -10, 0x1234, -1862, 0xABCDE, INT_MIN, INT_MAX, UINT_MAX);
	/* 112 */ test_print_long_ten("%0#.0X, %0#.0X, %0#.0X, %0#.0X, %0#.0X, %0#.0X, %0#.0X, %0#.0X, %0#.0X, %0#.0X", 0, 5, -1, -10, 0x1234, -1862, 0xABCDE, INT_MIN, INT_MAX, UINT_MAX);
	/* 113 */ test_print_long_ten("%0#.1X, %0#.1X, %0#.1X, %0#.1X, %0#.1X, %0#.1X, %0#.1X, %0#.1X, %0#.1X, %0#.1X", 0, 5, -1, -10, 0x1234, -1862, 0xABCDE, INT_MIN, INT_MAX, UINT_MAX);
	/* 114 */ test_print_long_ten("%0#.5X, %0#.5X, %0#.5X, %0#.5X, %0#.5X, %0#.5X, %0#.5X, %0#.5X, %0#.5X, %0#.5X", 0, 5, -1, -10, 0x1234, -1862, 0xABCDE, INT_MIN, INT_MAX, UINT_MAX);
	/* 115 */ test_print_long_ten("%0#.10X, %0#.10X, %0#.10X, %0#.10X, %0#.10X, %0#.10X, %0#.10X, %0#.10X, %0#.10X, %0#.10X", 0, 5, -1, -10, 0x1234, -1862, 0xABCDE, INT_MIN, INT_MAX, UINT_MAX);
	/* 116 */ test_print_long_ten("%0#.100X, %0#.100X, %0#.100X, %0#.100X, %0#.100X, %0#.100X, %0#.100X, %0#.100X, %0#.100X, %0#.100X", 0, 5, -1, -10, 0x1234, -1862, 0xABCDE, INT_MIN, INT_MAX, UINT_MAX);
	/* 117 */ test_print_long_ten("%0#1.X, %0#1.X, %0#1.X, %0#1.X, %0#1.X, %0#1.X, %0#1.X, %0#1.X, %0#1.X, %0#1.X", 0, 5, -1, -10, 0x1234, -1862, 0xABCDE, INT_MIN, INT_MAX, UINT_MAX);
	/* 118 */ test_print_long_ten("%0#1.0X, %0#1.0X, %0#1.0X, %0#1.0X, %0#1.0X, %0#1.0X, %0#1.0X, %0#1.0X, %0#1.0X, %0#1.0X", 0, 5, -1, -10, 0x1234, -1862, 0xABCDE, INT_MIN, INT_MAX, UINT_MAX);
	/* 119 */ test_print_long_ten("%0#1.1X, %0#1.1X, %0#1.1X, %0#1.1X, %0#1.1X, %0#1.1X, %0#1.1X, %0#1.1X, %0#1.1X, %0#1.1X", 0, 5, -1, -10, 0x1234, -1862, 0xABCDE, INT_MIN, INT_MAX, UINT_MAX);
	/* 120 */ test_print_long_ten("%0#1.5X, %0#1.5X, %0#1.5X, %0#1.5X, %0#1.5X, %0#1.5X, %0#1.5X, %0#1.5X, %0#1.5X, %0#1.5X", 0, 5, -1, -10, 0x1234, -1862, 0xABCDE, INT_MIN, INT_MAX, UINT_MAX);
	/* 121 */ test_print_long_ten("%0#1.10X, %0#1.10X, %0#1.10X, %0#1.10X, %0#1.10X, %0#1.10X, %0#1.10X, %0#1.10X, %0#1.10X, %0#1.10X", 0, 5, -1, -10, 0x1234, -1862, 0xABCDE, INT_MIN, INT_MAX, UINT_MAX);
	/* 122 */ test_print_long_ten("%0#1.100X, %0#1.100X, %0#1.100X, %0#1.100X, %0#1.100X, %0#1.100X, %0#1.100X, %0#1.100X, %0#1.100X, %0#1.100X", 0, 5, -1, -10, 0x1234, -1862, 0xABCDE, INT_MIN, INT_MAX, UINT_MAX);
	/* 123 */ test_print_long_ten("%0#5.X, %0#5.X, %0#5.X, %0#5.X, %0#5.X, %0#5.X, %0#5.X, %0#5.X, %0#5.X, %0#5.X", 0, 5, -1, -10, 0x1234, -1862, 0xABCDE, INT_MIN, INT_MAX, UINT_MAX);
	/* 124 */ test_print_long_ten("%0#5.0X, %0#5.0X, %0#5.0X, %0#5.0X, %0#5.0X, %0#5.0X, %0#5.0X, %0#5.0X, %0#5.0X, %0#5.0X", 0, 5, -1, -10, 0x1234, -1862, 0xABCDE, INT_MIN, INT_MAX, UINT_MAX);
	/* 125 */ test_print_long_ten("%0#5.1X, %0#5.1X, %0#5.1X, %0#5.1X, %0#5.1X, %0#5.1X, %0#5.1X, %0#5.1X, %0#5.1X, %0#5.1X", 0, 5, -1, -10, 0x1234, -1862, 0xABCDE, INT_MIN, INT_MAX, UINT_MAX);
	/* 126 */ test_print_long_ten("%0#5.5X, %0#5.5X, %0#5.5X, %0#5.5X, %0#5.5X, %0#5.5X, %0#5.5X, %0#5.5X, %0#5.5X, %0#5.5X", 0, 5, -1, -10, 0x1234, -1862, 0xABCDE, INT_MIN, INT_MAX, UINT_MAX);
	/* 127 */ test_print_long_ten("%0#5.10X, %0#5.10X, %0#5.10X, %0#5.10X, %0#5.10X, %0#5.10X, %0#5.10X, %0#5.10X, %0#5.10X, %0#5.10X", 0, 5, -1, -10, 0x1234, -1862, 0xABCDE, INT_MIN, INT_MAX, UINT_MAX);
	/* 128 */ test_print_long_ten("%0#5.100X, %0#5.100X, %0#5.100X, %0#5.100X, %0#5.100X, %0#5.100X, %0#5.100X, %0#5.100X, %0#5.100X, %0#5.100X", 0, 5, -1, -10, 0x1234, -1862, 0xABCDE, INT_MIN, INT_MAX, UINT_MAX);
	/* 129 */ test_print_long_ten("%0#10.X, %0#10.X, %0#10.X, %0#10.X, %0#10.X, %0#10.X, %0#10.X, %0#10.X, %0#10.X, %0#10.X", 0, 5, -1, -10, 0x1234, -1862, 0xABCDE, INT_MIN, INT_MAX, UINT_MAX);
	/* 130 */ test_print_long_ten("%0#10.0X, %0#10.0X, %0#10.0X, %0#10.0X, %0#10.0X, %0#10.0X, %0#10.0X, %0#10.0X, %0#10.0X, %0#10.0X", 0, 5, -1, -10, 0x1234, -1862, 0xABCDE, INT_MIN, INT_MAX, UINT_MAX);
	/* 131 */ test_print_long_ten("%0#10.1X, %0#10.1X, %0#10.1X, %0#10.1X, %0#10.1X, %0#10.1X, %0#10.1X, %0#10.1X, %0#10.1X, %0#10.1X", 0, 5, -1, -10, 0x1234, -1862, 0xABCDE, INT_MIN, INT_MAX, UINT_MAX);
	/* 132 */ test_print_long_ten("%0#10.5X, %0#10.5X, %0#10.5X, %0#10.5X, %0#10.5X, %0#10.5X, %0#10.5X, %0#10.5X, %0#10.5X, %0#10.5X", 0, 5, -1, -10, 0x1234, -1862, 0xABCDE, INT_MIN, INT_MAX, UINT_MAX);
	/* 133 */ test_print_long_ten("%0#10.10X, %0#10.10X, %0#10.10X, %0#10.10X, %0#10.10X, %0#10.10X, %0#10.10X, %0#10.10X, %0#10.10X, %0#10.10X", 0, 5, -1, -10, 0x1234, -1862, 0xABCDE, INT_MIN, INT_MAX, UINT_MAX);
	/* 134 */ test_print_long_ten("%0#10.100X, %0#10.100X, %0#10.100X, %0#10.100X, %0#10.100X, %0#10.100X, %0#10.100X, %0#10.100X, %0#10.100X, %0#10.100X", 0, 5, -1, -10, 0x1234, -1862, 0xABCDE, INT_MIN, INT_MAX, UINT_MAX);
	/* 135 */ test_print_long_ten("%0#100.X, %0#100.X, %0#100.X, %0#100.X, %0#100.X, %0#100.X, %0#100.X, %0#100.X, %0#100.X, %0#100.X", 0, 5, -1, -10, 0x1234, -1862, 0xABCDE, INT_MIN, INT_MAX, UINT_MAX);
	/* 136 */ test_print_long_ten("%0#100.0X, %0#100.0X, %0#100.0X, %0#100.0X, %0#100.0X, %0#100.0X, %0#100.0X, %0#100.0X, %0#100.0X, %0#100.0X", 0, 5, -1, -10, 0x1234, -1862, 0xABCDE, INT_MIN, INT_MAX, UINT_MAX);
	/* 137 */ test_print_long_ten("%0#100.1X, %0#100.1X, %0#100.1X, %0#100.1X, %0#100.1X, %0#100.1X, %0#100.1X, %0#100.1X, %0#100.1X, %0#100.1X", 0, 5, -1, -10, 0x1234, -1862, 0xABCDE, INT_MIN, INT_MAX, UINT_MAX);
	/* 138 */ test_print_long_ten("%0#100.5X, %0#100.5X, %0#100.5X, %0#100.5X, %0#100.5X, %0#100.5X, %0#100.5X, %0#100.5X, %0#100.5X, %0#100.5X", 0, 5, -1, -10, 0x1234, -1862, 0xABCDE, INT_MIN, INT_MAX, UINT_MAX);
	/* 139 */ test_print_long_ten("%0#100.10X, %0#100.10X, %0#100.10X, %0#100.10X, %0#100.10X, %0#100.10X, %0#100.10X, %0#100.10X, %0#100.10X, %0#100.10X", 0, 5, -1, -10, 0x1234, -1862, 0xABCDE, INT_MIN, INT_MAX, UINT_MAX);
	/* 140 */ test_print_long_ten("%0#100.100X, %0#100.100X, %0#100.100X, %0#100.100X, %0#100.100X, %0#100.100X, %0#100.100X, %0#100.100X, %0#100.100X, %0#100.100X", 0, 5, -1, -10, 0x1234, -1862, 0xABCDE, INT_MIN, INT_MAX, UINT_MAX);
	/* 141 */ test_print_long_ten("%-X, %-X, %-X, %-X, %-X, %-X, %-X, %-X, %-X, %-X", 0, 5, -1, -10, 0x1234, -1862, 0xABCDE, INT_MIN, INT_MAX, UINT_MAX);
	/* 142 */ test_print_long_ten("%-1X, %-1X, %-1X, %-1X, %-1X, %-1X, %-1X, %-1X, %-1X, %-1X", 0, 5, -1, -10, 0x1234, -1862, 0xABCDE, INT_MIN, INT_MAX, UINT_MAX);
	/* 143 */ test_print_long_ten("%-5X, %-5X, %-5X, %-5X, %-5X, %-5X, %-5X, %-5X, %-5X, %-5X", 0, 5, -1, -10, 0x1234, -1862, 0xABCDE, INT_MIN, INT_MAX, UINT_MAX);
	/* 144 */ test_print_long_ten("%-10X, %-10X, %-10X, %-10X, %-10X, %-10X, %-10X, %-10X, %-10X, %-10X", 0, 5, -1, -10, 0x1234, -1862, 0xABCDE, INT_MIN, INT_MAX, UINT_MAX);
	/* 145 */ test_print_long_ten("%-100X, %-100X, %-100X, %-100X, %-100X, %-100X, %-100X, %-100X, %-100X, %-100X", 0, 5, -1, -10, 0x1234, -1862, 0xABCDE, INT_MIN, INT_MAX, UINT_MAX);
	/* 146 */ test_print_long_ten("%-.X, %-.X, %-.X, %-.X, %-.X, %-.X, %-.X, %-.X, %-.X, %-.X", 0, 5, -1, -10, 0x1234, -1862, 0xABCDE, INT_MIN, INT_MAX, UINT_MAX);
	/* 147 */ test_print_long_ten("%-.0X, %-.0X, %-.0X, %-.0X, %-.0X, %-.0X, %-.0X, %-.0X, %-.0X, %-.0X", 0, 5, -1, -10, 0x1234, -1862, 0xABCDE, INT_MIN, INT_MAX, UINT_MAX);
	/* 148 */ test_print_long_ten("%-.1X, %-.1X, %-.1X, %-.1X, %-.1X, %-.1X, %-.1X, %-.1X, %-.1X, %-.1X", 0, 5, -1, -10, 0x1234, -1862, 0xABCDE, INT_MIN, INT_MAX, UINT_MAX);
	/* 149 */ test_print_long_ten("%-.5X, %-.5X, %-.5X, %-.5X, %-.5X, %-.5X, %-.5X, %-.5X, %-.5X, %-.5X", 0, 5, -1, -10, 0x1234, -1862, 0xABCDE, INT_MIN, INT_MAX, UINT_MAX);
	/* 150 */ test_print_long_ten("%-.10X, %-.10X, %-.10X, %-.10X, %-.10X, %-.10X, %-.10X, %-.10X, %-.10X, %-.10X", 0, 5, -1, -10, 0x1234, -1862, 0xABCDE, INT_MIN, INT_MAX, UINT_MAX);
	/* 151 */ test_print_long_ten("%-.100X, %-.100X, %-.100X, %-.100X, %-.100X, %-.100X, %-.100X, %-.100X, %-.100X, %-.100X", 0, 5, -1, -10, 0x1234, -1862, 0xABCDE, INT_MIN, INT_MAX, UINT_MAX);
	/* 152 */ test_print_long_ten("%-1.X, %-1.X, %-1.X, %-1.X, %-1.X, %-1.X, %-1.X, %-1.X, %-1.X, %-1.X", 0, 5, -1, -10, 0x1234, -1862, 0xABCDE, INT_MIN, INT_MAX, UINT_MAX);
	/* 153 */ test_print_long_ten("%-1.0X, %-1.0X, %-1.0X, %-1.0X, %-1.0X, %-1.0X, %-1.0X, %-1.0X, %-1.0X, %-1.0X", 0, 5, -1, -10, 0x1234, -1862, 0xABCDE, INT_MIN, INT_MAX, UINT_MAX);
	/* 154 */ test_print_long_ten("%-1.1X, %-1.1X, %-1.1X, %-1.1X, %-1.1X, %-1.1X, %-1.1X, %-1.1X, %-1.1X, %-1.1X", 0, 5, -1, -10, 0x1234, -1862, 0xABCDE, INT_MIN, INT_MAX, UINT_MAX);
	/* 155 */ test_print_long_ten("%-1.5X, %-1.5X, %-1.5X, %-1.5X, %-1.5X, %-1.5X, %-1.5X, %-1.5X, %-1.5X, %-1.5X", 0, 5, -1, -10, 0x1234, -1862, 0xABCDE, INT_MIN, INT_MAX, UINT_MAX);
	/* 156 */ test_print_long_ten("%-1.10X, %-1.10X, %-1.10X, %-1.10X, %-1.10X, %-1.10X, %-1.10X, %-1.10X, %-1.10X, %-1.10X", 0, 5, -1, -10, 0x1234, -1862, 0xABCDE, INT_MIN, INT_MAX, UINT_MAX);
	/* 157 */ test_print_long_ten("%-1.100X, %-1.100X, %-1.100X, %-1.100X, %-1.100X, %-1.100X, %-1.100X, %-1.100X, %-1.100X, %-1.100X", 0, 5, -1, -10, 0x1234, -1862, 0xABCDE, INT_MIN, INT_MAX, UINT_MAX);
	/* 158 */ test_print_long_ten("%-5.X, %-5.X, %-5.X, %-5.X, %-5.X, %-5.X, %-5.X, %-5.X, %-5.X, %-5.X", 0, 5, -1, -10, 0x1234, -1862, 0xABCDE, INT_MIN, INT_MAX, UINT_MAX);
	/* 159 */ test_print_long_ten("%-5.0X, %-5.0X, %-5.0X, %-5.0X, %-5.0X, %-5.0X, %-5.0X, %-5.0X, %-5.0X, %-5.0X", 0, 5, -1, -10, 0x1234, -1862, 0xABCDE, INT_MIN, INT_MAX, UINT_MAX);
	/* 160 */ test_print_long_ten("%-5.1X, %-5.1X, %-5.1X, %-5.1X, %-5.1X, %-5.1X, %-5.1X, %-5.1X, %-5.1X, %-5.1X", 0, 5, -1, -10, 0x1234, -1862, 0xABCDE, INT_MIN, INT_MAX, UINT_MAX);
	/* 161 */ test_print_long_ten("%-5.5X, %-5.5X, %-5.5X, %-5.5X, %-5.5X, %-5.5X, %-5.5X, %-5.5X, %-5.5X, %-5.5X", 0, 5, -1, -10, 0x1234, -1862, 0xABCDE, INT_MIN, INT_MAX, UINT_MAX);
	/* 162 */ test_print_long_ten("%-5.10X, %-5.10X, %-5.10X, %-5.10X, %-5.10X, %-5.10X, %-5.10X, %-5.10X, %-5.10X, %-5.10X", 0, 5, -1, -10, 0x1234, -1862, 0xABCDE, INT_MIN, INT_MAX, UINT_MAX);
	/* 163 */ test_print_long_ten("%-5.100X, %-5.100X, %-5.100X, %-5.100X, %-5.100X, %-5.100X, %-5.100X, %-5.100X, %-5.100X, %-5.100X", 0, 5, -1, -10, 0x1234, -1862, 0xABCDE, INT_MIN, INT_MAX, UINT_MAX);
	/* 164 */ test_print_long_ten("%-10.X, %-10.X, %-10.X, %-10.X, %-10.X, %-10.X, %-10.X, %-10.X, %-10.X, %-10.X", 0, 5, -1, -10, 0x1234, -1862, 0xABCDE, INT_MIN, INT_MAX, UINT_MAX);
	/* 165 */ test_print_long_ten("%-10.0X, %-10.0X, %-10.0X, %-10.0X, %-10.0X, %-10.0X, %-10.0X, %-10.0X, %-10.0X, %-10.0X", 0, 5, -1, -10, 0x1234, -1862, 0xABCDE, INT_MIN, INT_MAX, UINT_MAX);
	/* 166 */ test_print_long_ten("%-10.1X, %-10.1X, %-10.1X, %-10.1X, %-10.1X, %-10.1X, %-10.1X, %-10.1X, %-10.1X, %-10.1X", 0, 5, -1, -10, 0x1234, -1862, 0xABCDE, INT_MIN, INT_MAX, UINT_MAX);
	/* 167 */ test_print_long_ten("%-10.5X, %-10.5X, %-10.5X, %-10.5X, %-10.5X, %-10.5X, %-10.5X, %-10.5X, %-10.5X, %-10.5X", 0, 5, -1, -10, 0x1234, -1862, 0xABCDE, INT_MIN, INT_MAX, UINT_MAX);
	/* 168 */ test_print_long_ten("%-10.10X, %-10.10X, %-10.10X, %-10.10X, %-10.10X, %-10.10X, %-10.10X, %-10.10X, %-10.10X, %-10.10X", 0, 5, -1, -10, 0x1234, -1862, 0xABCDE, INT_MIN, INT_MAX, UINT_MAX);
	/* 169 */ test_print_long_ten("%-10.100X, %-10.100X, %-10.100X, %-10.100X, %-10.100X, %-10.100X, %-10.100X, %-10.100X, %-10.100X, %-10.100X", 0, 5, -1, -10, 0x1234, -1862, 0xABCDE, INT_MIN, INT_MAX, UINT_MAX);
	/* 170 */ test_print_long_ten("%-100.X, %-100.X, %-100.X, %-100.X, %-100.X, %-100.X, %-100.X, %-100.X, %-100.X, %-100.X", 0, 5, -1, -10, 0x1234, -1862, 0xABCDE, INT_MIN, INT_MAX, UINT_MAX);
	/* 171 */ test_print_long_ten("%-100.0X, %-100.0X, %-100.0X, %-100.0X, %-100.0X, %-100.0X, %-100.0X, %-100.0X, %-100.0X, %-100.0X", 0, 5, -1, -10, 0x1234, -1862, 0xABCDE, INT_MIN, INT_MAX, UINT_MAX);
	/* 172 */ test_print_long_ten("%-100.1X, %-100.1X, %-100.1X, %-100.1X, %-100.1X, %-100.1X, %-100.1X, %-100.1X, %-100.1X, %-100.1X", 0, 5, -1, -10, 0x1234, -1862, 0xABCDE, INT_MIN, INT_MAX, UINT_MAX);
	/* 173 */ test_print_long_ten("%-100.5X, %-100.5X, %-100.5X, %-100.5X, %-100.5X, %-100.5X, %-100.5X, %-100.5X, %-100.5X, %-100.5X", 0, 5, -1, -10, 0x1234, -1862, 0xABCDE, INT_MIN, INT_MAX, UINT_MAX);
	/* 174 */ test_print_long_ten("%-100.10X, %-100.10X, %-100.10X, %-100.10X, %-100.10X, %-100.10X, %-100.10X, %-100.10X, %-100.10X, %-100.10X", 0, 5, -1, -10, 0x1234, -1862, 0xABCDE, INT_MIN, INT_MAX, UINT_MAX);
	/* 175 */ test_print_long_ten("%-100.100X, %-100.100X, %-100.100X, %-100.100X, %-100.100X, %-100.100X, %-100.100X, %-100.100X, %-100.100X, %-100.100X", 0, 5, -1, -10, 0x1234, -1862, 0xABCDE, INT_MIN, INT_MAX, UINT_MAX);
	/* 176 */ test_print_long_ten("%-#X, %-#X, %-#X, %-#X, %-#X, %-#X, %-#X, %-#X, %-#X, %-#X", 0, 5, -1, -10, 0x1234, -1862, 0xABCDE, INT_MIN, INT_MAX, UINT_MAX);
	/* 177 */ test_print_long_ten("%-#1X, %-#1X, %-#1X, %-#1X, %-#1X, %-#1X, %-#1X, %-#1X, %-#1X, %-#1X", 0, 5, -1, -10, 0x1234, -1862, 0xABCDE, INT_MIN, INT_MAX, UINT_MAX);
	/* 178 */ test_print_long_ten("%-#5X, %-#5X, %-#5X, %-#5X, %-#5X, %-#5X, %-#5X, %-#5X, %-#5X, %-#5X", 0, 5, -1, -10, 0x1234, -1862, 0xABCDE, INT_MIN, INT_MAX, UINT_MAX);
	/* 179 */ test_print_long_ten("%-#10X, %-#10X, %-#10X, %-#10X, %-#10X, %-#10X, %-#10X, %-#10X, %-#10X, %-#10X", 0, 5, -1, -10, 0x1234, -1862, 0xABCDE, INT_MIN, INT_MAX, UINT_MAX);
	/* 180 */ test_print_long_ten("%-#100X, %-#100X, %-#100X, %-#100X, %-#100X, %-#100X, %-#100X, %-#100X, %-#100X, %-#100X", 0, 5, -1, -10, 0x1234, -1862, 0xABCDE, INT_MIN, INT_MAX, UINT_MAX);
	/* 181 */ test_print_long_ten("%-#.X, %-#.X, %-#.X, %-#.X, %-#.X, %-#.X, %-#.X, %-#.X, %-#.X, %-#.X", 0, 5, -1, -10, 0x1234, -1862, 0xABCDE, INT_MIN, INT_MAX, UINT_MAX);
	/* 182 */ test_print_long_ten("%-#.0X, %-#.0X, %-#.0X, %-#.0X, %-#.0X, %-#.0X, %-#.0X, %-#.0X, %-#.0X, %-#.0X", 0, 5, -1, -10, 0x1234, -1862, 0xABCDE, INT_MIN, INT_MAX, UINT_MAX);
	/* 183 */ test_print_long_ten("%-#.1X, %-#.1X, %-#.1X, %-#.1X, %-#.1X, %-#.1X, %-#.1X, %-#.1X, %-#.1X, %-#.1X", 0, 5, -1, -10, 0x1234, -1862, 0xABCDE, INT_MIN, INT_MAX, UINT_MAX);
	/* 184 */ test_print_long_ten("%-#.5X, %-#.5X, %-#.5X, %-#.5X, %-#.5X, %-#.5X, %-#.5X, %-#.5X, %-#.5X, %-#.5X", 0, 5, -1, -10, 0x1234, -1862, 0xABCDE, INT_MIN, INT_MAX, UINT_MAX);
	/* 185 */ test_print_long_ten("%-#.10X, %-#.10X, %-#.10X, %-#.10X, %-#.10X, %-#.10X, %-#.10X, %-#.10X, %-#.10X, %-#.10X", 0, 5, -1, -10, 0x1234, -1862, 0xABCDE, INT_MIN, INT_MAX, UINT_MAX);
	/* 186 */ test_print_long_ten("%-#.100X, %-#.100X, %-#.100X, %-#.100X, %-#.100X, %-#.100X, %-#.100X, %-#.100X, %-#.100X, %-#.100X", 0, 5, -1, -10, 0x1234, -1862, 0xABCDE, INT_MIN, INT_MAX, UINT_MAX);
	/* 187 */ test_print_long_ten("%-#1.X, %-#1.X, %-#1.X, %-#1.X, %-#1.X, %-#1.X, %-#1.X, %-#1.X, %-#1.X, %-#1.X", 0, 5, -1, -10, 0x1234, -1862, 0xABCDE, INT_MIN, INT_MAX, UINT_MAX);
	/* 188 */ test_print_long_ten("%-#1.0X, %-#1.0X, %-#1.0X, %-#1.0X, %-#1.0X, %-#1.0X, %-#1.0X, %-#1.0X, %-#1.0X, %-#1.0X", 0, 5, -1, -10, 0x1234, -1862, 0xABCDE, INT_MIN, INT_MAX, UINT_MAX);
	/* 189 */ test_print_long_ten("%-#1.1X, %-#1.1X, %-#1.1X, %-#1.1X, %-#1.1X, %-#1.1X, %-#1.1X, %-#1.1X, %-#1.1X, %-#1.1X", 0, 5, -1, -10, 0x1234, -1862, 0xABCDE, INT_MIN, INT_MAX, UINT_MAX);
	/* 190 */ test_print_long_ten("%-#1.5X, %-#1.5X, %-#1.5X, %-#1.5X, %-#1.5X, %-#1.5X, %-#1.5X, %-#1.5X, %-#1.5X, %-#1.5X", 0, 5, -1, -10, 0x1234, -1862, 0xABCDE, INT_MIN, INT_MAX, UINT_MAX);
	/* 191 */ test_print_long_ten("%-#1.10X, %-#1.10X, %-#1.10X, %-#1.10X, %-#1.10X, %-#1.10X, %-#1.10X, %-#1.10X, %-#1.10X, %-#1.10X", 0, 5, -1, -10, 0x1234, -1862, 0xABCDE, INT_MIN, INT_MAX, UINT_MAX);
	/* 192 */ test_print_long_ten("%-#1.100X, %-#1.100X, %-#1.100X, %-#1.100X, %-#1.100X, %-#1.100X, %-#1.100X, %-#1.100X, %-#1.100X, %-#1.100X", 0, 5, -1, -10, 0x1234, -1862, 0xABCDE, INT_MIN, INT_MAX, UINT_MAX);
	/* 193 */ test_print_long_ten("%-#5.X, %-#5.X, %-#5.X, %-#5.X, %-#5.X, %-#5.X, %-#5.X, %-#5.X, %-#5.X, %-#5.X", 0, 5, -1, -10, 0x1234, -1862, 0xABCDE, INT_MIN, INT_MAX, UINT_MAX);
	/* 194 */ test_print_long_ten("%-#5.0X, %-#5.0X, %-#5.0X, %-#5.0X, %-#5.0X, %-#5.0X, %-#5.0X, %-#5.0X, %-#5.0X, %-#5.0X", 0, 5, -1, -10, 0x1234, -1862, 0xABCDE, INT_MIN, INT_MAX, UINT_MAX);
	/* 195 */ test_print_long_ten("%-#5.1X, %-#5.1X, %-#5.1X, %-#5.1X, %-#5.1X, %-#5.1X, %-#5.1X, %-#5.1X, %-#5.1X, %-#5.1X", 0, 5, -1, -10, 0x1234, -1862, 0xABCDE, INT_MIN, INT_MAX, UINT_MAX);
	/* 196 */ test_print_long_ten("%-#5.5X, %-#5.5X, %-#5.5X, %-#5.5X, %-#5.5X, %-#5.5X, %-#5.5X, %-#5.5X, %-#5.5X, %-#5.5X", 0, 5, -1, -10, 0x1234, -1862, 0xABCDE, INT_MIN, INT_MAX, UINT_MAX);
	/* 197 */ test_print_long_ten("%-#5.10X, %-#5.10X, %-#5.10X, %-#5.10X, %-#5.10X, %-#5.10X, %-#5.10X, %-#5.10X, %-#5.10X, %-#5.10X", 0, 5, -1, -10, 0x1234, -1862, 0xABCDE, INT_MIN, INT_MAX, UINT_MAX);
	/* 198 */ test_print_long_ten("%-#5.100X, %-#5.100X, %-#5.100X, %-#5.100X, %-#5.100X, %-#5.100X, %-#5.100X, %-#5.100X, %-#5.100X, %-#5.100X", 0, 5, -1, -10, 0x1234, -1862, 0xABCDE, INT_MIN, INT_MAX, UINT_MAX);
	/* 199 */ test_print_long_ten("%-#10.X, %-#10.X, %-#10.X, %-#10.X, %-#10.X, %-#10.X, %-#10.X, %-#10.X, %-#10.X, %-#10.X", 0, 5, -1, -10, 0x1234, -1862, 0xABCDE, INT_MIN, INT_MAX, UINT_MAX);
	/* 200 */ test_print_long_ten("%-#10.0X, %-#10.0X, %-#10.0X, %-#10.0X, %-#10.0X, %-#10.0X, %-#10.0X, %-#10.0X, %-#10.0X, %-#10.0X", 0, 5, -1, -10, 0x1234, -1862, 0xABCDE, INT_MIN, INT_MAX, UINT_MAX);
	/* 201 */ test_print_long_ten("%-#10.1X, %-#10.1X, %-#10.1X, %-#10.1X, %-#10.1X, %-#10.1X, %-#10.1X, %-#10.1X, %-#10.1X, %-#10.1X", 0, 5, -1, -10, 0x1234, -1862, 0xABCDE, INT_MIN, INT_MAX, UINT_MAX);
	/* 202 */ test_print_long_ten("%-#10.5X, %-#10.5X, %-#10.5X, %-#10.5X, %-#10.5X, %-#10.5X, %-#10.5X, %-#10.5X, %-#10.5X, %-#10.5X", 0, 5, -1, -10, 0x1234, -1862, 0xABCDE, INT_MIN, INT_MAX, UINT_MAX);
	/* 203 */ test_print_long_ten("%-#10.10X, %-#10.10X, %-#10.10X, %-#10.10X, %-#10.10X, %-#10.10X, %-#10.10X, %-#10.10X, %-#10.10X, %-#10.10X", 0, 5, -1, -10, 0x1234, -1862, 0xABCDE, INT_MIN, INT_MAX, UINT_MAX);
	/* 204 */ test_print_long_ten("%-#10.100X, %-#10.100X, %-#10.100X, %-#10.100X, %-#10.100X, %-#10.100X, %-#10.100X, %-#10.100X, %-#10.100X, %-#10.100X", 0, 5, -1, -10, 0x1234, -1862, 0xABCDE, INT_MIN, INT_MAX, UINT_MAX);
	/* 205 */ test_print_long_ten("%-#100.X, %-#100.X, %-#100.X, %-#100.X, %-#100.X, %-#100.X, %-#100.X, %-#100.X, %-#100.X, %-#100.X", 0, 5, -1, -10, 0x1234, -1862, 0xABCDE, INT_MIN, INT_MAX, UINT_MAX);
	/* 206 */ test_print_long_ten("%-#100.0X, %-#100.0X, %-#100.0X, %-#100.0X, %-#100.0X, %-#100.0X, %-#100.0X, %-#100.0X, %-#100.0X, %-#100.0X", 0, 5, -1, -10, 0x1234, -1862, 0xABCDE, INT_MIN, INT_MAX, UINT_MAX);
	/* 207 */ test_print_long_ten("%-#100.1X, %-#100.1X, %-#100.1X, %-#100.1X, %-#100.1X, %-#100.1X, %-#100.1X, %-#100.1X, %-#100.1X, %-#100.1X", 0, 5, -1, -10, 0x1234, -1862, 0xABCDE, INT_MIN, INT_MAX, UINT_MAX);
	/* 208 */ test_print_long_ten("%-#100.5X, %-#100.5X, %-#100.5X, %-#100.5X, %-#100.5X, %-#100.5X, %-#100.5X, %-#100.5X, %-#100.5X, %-#100.5X", 0, 5, -1, -10, 0x1234, -1862, 0xABCDE, INT_MIN, INT_MAX, UINT_MAX);
	/* 209 */ test_print_long_ten("%-#100.10X, %-#100.10X, %-#100.10X, %-#100.10X, %-#100.10X, %-#100.10X, %-#100.10X, %-#100.10X, %-#100.10X, %-#100.10X", 0, 5, -1, -10, 0x1234, -1862, 0xABCDE, INT_MIN, INT_MAX, UINT_MAX);
	/* 210 */ test_print_long_ten("%-#100.100X, %-#100.100X, %-#100.100X, %-#100.100X, %-#100.100X, %-#100.100X, %-#100.100X, %-#100.100X, %-#100.100X, %-#100.100X", 0, 5, -1, -10, 0x1234, -1862, 0xABCDE, INT_MIN, INT_MAX, UINT_MAX);
}

void test_percent() {
	g_current_test_id = '%';
	/* 1 */ test_printf_noarg("%%");
}

int main()
{
	remove(ERRLOG_FILE);
	test_c();
	test_s();
	test_p();
	test_i();
	test_d();
	test_u();
	test_x();
	test_X();
}
/*
   int main(int argn, char **argv)
   {
   printf(YEL "\nBonus:" NC "\n");
   pf_setup_framework(argn, argv);

   test_c();
   test_s();
   test_p();
   test_d();
   test_i();
   test_u();
   test_x();
   test_X();
   test_percent();
   }
   */
