#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <errno.h>
#include <string.h>


int main(int ac, char **av)
{
	int	i;

	if (ac == 5)
	{
		i = 4;
		while (i)
			printf("%s\n", av[i--]);
	}
	else
		printf("wrong arg number\n");
	return (0);
}
