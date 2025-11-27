#include <fcntl.h>
#include <stdio.h>
#include "get_next_line.h"

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
}/*
int main(int ac, char **av)
{
    char *line;
    int fd = open(av[1], O_RDONLY);

    for (int i = 1; i <= 20; i++)
    {
        line = get_next_line(fd);
        printf("GNL returned: %s\n", line ? line : "(NULL)");
        free(line);
    }
}
*/
int main(int ac, char **av)
{
	int fd[ac];
	int i;
	
	i = 0;
	while(++i < ac)
		fd[i - 1] = open(av[i], O_RDONLY);
	print_nl(*fd);
	close(*fd);
}


