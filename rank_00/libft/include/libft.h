/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maprunty <maprunty@student.42heilbronn.de  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/05 18:06:17 by maprunty          #+#    #+#             */
/*   Updated: 2025/09/05 19:01:41 by maprunty         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


/*
ft_toupper.c ft_isalpha.c ft_isdigit.c ft_tolower.c ft_isalnum.c ft_isascii.c ft_strchr.c ft_isprint.c ft_strrchr.c ft_strlen.c ft_strncmp.c ft_memset.c ft_bzero.c ft_memchr.c ft_memcpy.c ft_memcmp.c ft_memmove.c ft_strnstr.c ft_strlcpy.c ft_strlcat.c ft_atoi.c ft_calloc.c ft_strdup.c ft_substr.c ft_strjoin.c ft_strtrim.c ft_split.c ft_itoa.c ft_strmapi.c ft_striteri.c ft_putchar_fd.c ft_putstr_fd.c ft_putendl_fd.c ft_putnbr_fd.c 


ft_toupper.c
ft_isalpha.c
ft_isdigit.c
ft_tolower.c
ft_isalnum.c
ft_isascii.c
ft_strchr.c
ft_isprint.c
ft_strrchr.c
ft_strlen.c
ft_strncmp.c
ft_memset.c
ft_bzero.c
ft_memchr.c
ft_memcpy.c
ft_memcmp.c
ft_memmove.c
ft_strnstr.c
ft_strlcpy.c
ft_strlcat.c
ft_atoi.c
ft_calloc.c
ft_strdup.c

ft_substr.c
ft_strjoin.c
ft_strtrim.c
ft_split.c
ft_itoa.c
ft_strmapi.c
ft_striteri.c
ft_putchar_fd.c
ft_putstr_fd.c
ft_putendl_fd.c
ft_putnbr_fd.c

*/

/*

char *ft_substr(char const *s, unsigned int start, size_t len);
char *ft_strjoin(char const *s1, char const *s2);
char *ft_strtrim(char const *s1, char const *set);
char **ft_split(char const *s, char c);
char *ft_itoa(int n);
void ft_striteri(char *s, void (*f)(unsigned int, char*));
void ft_putchar_fd(char c, int fd);
void ft_putstr_fd(char *s, int fd);
void ft_putendl_fd(char *s, int fd);
void ft_putnbr_fd(int n, int fd);

*/

int ft_isalpha(int c);
int ft_isdigit(int c);
int ft_isalnum(int c);
int ft_isascii(int c);
int ft_isprint(int c);

int ft_isupper(int c);
int ft_islower(int c);
