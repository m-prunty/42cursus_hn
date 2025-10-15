#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "include/libft.h"

void	ft_print_result(char const *s)
{
	int		len;

	len = 0;
	while (s[len])
		len++;
	write(1, s, len);
	//free((char*)s);
}

int		main(int argc, const char *argv[])
{
	char	**tabstr;
	int		i;
	int		arg;

	i = 0;
	//	if ((arg = atoi(argv[1])) == 1)
	//	{
printf("1\n");
	i=0;
	if (!(tabstr = ft_split("          ", ' ')))
		ft_print_result("NULL");
	else
	{
		while (tabstr[i] != NULL)
		{
			ft_print_result(tabstr[i]);
			write(1, "\n", 1);
			i++;
		}
	}
printf("2\n");
	i=0;
	if (!(tabstr = ft_split("lorem ipsum dolor sit amet, consectetur adipiscing elit. Sed non risus. Suspendisse", ' ')))
		ft_print_result("NULL");
	else
		{
		while (tabstr[i] != NULL)
		{
			ft_print_result(tabstr[i]);
			write(1, "\n", 1);
			i++;
		}
	}
printf("3\n");
	i=0;
	if (!(tabstr = ft_split("   lorem   ipsum dolor     sit amet, consectetur   adipiscing elit. Sed non risus. Suspendisse   ", ' ')))
		ft_print_result("NULL");
	else
		{
		while (tabstr[i] != NULL)
		{
			ft_print_result(tabstr[i]);
			write(1, "\n", 1);
			i++;
		}
	}
printf("4\n");
	i=0;
	if (!(tabstr = ft_split("lorem ipsum dolor sit amet, consectetur adipiscing elit. Sed non risus. Suspendisse lectus tortor, dignissim sit amet, adipiscing nec, ultricies sed, dolor. Cras elementum ultricies diam. Maecenas ligula massa, varius a, semper congue, euismod non, mi.", 'i')))
		ft_print_result("NULL");
	else
		{
		while (tabstr[i] != NULL)
		{
			ft_print_result(tabstr[i]);
			write(1, "\n", 1);
			i++;
		}
	}
printf("5\n");
	i=0;
	if (!(tabstr = ft_split("lorem ipsum dolor sit amet, consectetur adipiscing elit. Sed non risus. Suspendisse lectus tortor, dignissim sit amet, adipiscing nec, ultricies sed, dolor. Cras elementum ultricies diam. Maecenas ligula massa, varius a, semper congue, euismod non, mi.", 'z')))
		ft_print_result("NULL");
	else
		{
		while (tabstr[i] != NULL)
		{
			ft_print_result(tabstr[i]);
			write(1, "\n", 1);
			i++;
		}
	}
printf("6\n");
	i=0;
	if (!(tabstr = ft_split("", 'z')))
		ft_print_result("NULL");
	else
		if (!tabstr[0])
		ft_print_result("ok\n");
printf("7\n");
	i=0;
	if (!(tabstr = ft_split("lorem   i", ' ')))
		ft_print_result("NULL");
	else
		{	
		while (tabstr[i] != NULL)
		{
			ft_print_result(tabstr[i]);
			write(1, "\n", 1);
			i++;
		}	
	}
printf("8\n");
	i=0;
	if (!(tabstr = ft_split("hello!", ' ')))
		ft_print_result("NULL");
	else
		{
		while (tabstr[i] != NULL)
		{
			ft_print_result(tabstr[i]);
			write(1, "\n", 1);
			i++;
		}	
	}
printf("9\n");
	i=0;
	if (!(tabstr = ft_split("xxxxxxxxhello!", 'x')))
		ft_print_result("NULL");
	else
		{
		while (tabstr[i] != NULL)
		{
			ft_print_result(tabstr[i]);
			write(1, "\n", 1);
			i++;
		}	
	}
printf("10\n");
	i=0;
	if (!(tabstr = ft_split("^^^1^^2a,^^^^3^^^^--h^^^^", '^')))
		ft_print_result("NULL");
	else
		{
		while (tabstr[i] != NULL)
		{
			ft_print_result(tabstr[i]);
			write(1, "\n", 1);
			i++;
		}	
	}
printf("11\n");
	i=0;
	if (!(tabstr = ft_split("hello!", ' ')))
		ft_print_result("NULL");
	else
		{
		while (tabstr[i] != NULL)
		{
			ft_print_result(tabstr[i]);
			write(1, "\n", 1);
			i++;
		}	
	}
//free(tabstr[i]);
return (0);
}
