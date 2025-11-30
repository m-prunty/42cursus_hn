#include <fcntl.h>
#include <stdio.h>
#include "get_next_line_bonus.h"

void	print_nl(int fd)
{
	char *gnl_str;

	gnl_str = malloc(1);
	while (gnl_str)
	{
		free(gnl_str);
		gnl_str = get_next_line(fd);
		printf("%s", gnl_str);
		fflush(stdout);
	}
}

void	print_line(int fd, char **gnl_str)
{
	free(*gnl_str);
	*gnl_str = get_next_line(fd);
	printf("%s", *gnl_str);
	fflush(stdout);
}

void	print_n_nl(int *fd, int n)
{
	char	*gnl_str;
	int		i;
//	int		j = 0;

	gnl_str = malloc(1);
	while (gnl_str)//&& j++ < 3)
	{
		i = 0;
		while (i < n)
			print_line(fd[i++], &gnl_str);
	}
	free(gnl_str);
}

int main(int ac, char **av)
{
	int fd[ac - 1];
	int i;
	
	i = 0;
	while(++i < ac)
		fd[i - 1] = open(av[i], O_RDONLY);
	print_n_nl(fd, (ac - 1));
	i = 0;
	while(++i < ac)
		fd[i - 1] = close(fd[i - 1]);
}


