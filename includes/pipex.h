#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <errno.h>
#include <string.h>
#include <fcntl.h>
#include <stdlib.h>
#include "libft.h"

typedef struct s_process_info {
	int			fd_in;
	int			fd_out;
	const char	*output_file;
	char		**cmd_args;
	char		**env;
}	t_process_info;

void	error_exit(const char *msg);
void	execute_command(char *cmd, char **args, char **env);
void	execute_process(t_process_info info);
