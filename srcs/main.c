#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <errno.h>
#include <string.h>
#include <fcntl.h>
#include <stdlib.h>
#include "libft.h"

void execute_command(char *cmd, char **args, char **env)
{
	const char	*paths[3];
	char		*full_path;
	int			i;

	paths[0] = "/bin";
	paths[1] = "/usr/bin";
	paths[2] = NULL;
	i = 0;
	printf("JESUISRACISTE\n");
	while (paths[i])
	{
		full_path = ft_strdup(paths[i]); 
		if (!full_path)
		{
			perror("malloc");
			exit(EXIT_FAILURE);
		}
		full_path = strcat(full_path, "/");
		full_path = strcat(full_path, cmd);
		if (!access(full_path, X_OK))
		{
			if (execve(full_path, args, env) == -1)
			{
				perror("execve");
				free(full_path);
				exit(EXIT_FAILURE);
			}
			free(full_path);
			return ;
		}
		free(full_path);
		i++;
	}
	exit(EXIT_FAILURE);
}

int main(int argc, char **argv, char **env)
{
	int		pipefd[2];
	pid_t	pid1;
	pid_t	pid2;
	char	**cmd;

	if (argc != 5)
	{
		errno = EINVAL;
		perror("Usage: ./pipex file1 \"cmd1\" \"cmd2\" file2\n");
		return (0);
	}
	if (pipe(pipefd) == -1)
	{
		perror("pipe");
		return (EXIT_FAILURE);
	}
	pid1 = fork();
	if (pid1 == -1)
	{
		perror("fork");
		close(pipefd[0]);
		close(pipefd[1]);
		return (EXIT_FAILURE);
	}
	if (!pid1)
	{
		write(1, "I am the first child process\n", 29);
		argv[2] = strcat(argv[2], " ");
		argv[2] = strcat(argv[2], argv[1]);
		cmd = ft_split(argv[2], ' ');
		execute_command(cmd[0], cmd, env);
		close(pipefd[0]);
		exit(EXIT_FAILURE);
	}
	else
	{
		pid2 = fork();
		if (pid2 == -1)
		{
			perror("fork");
			close(pipefd[0]);
			close(pipefd[1]);
			return (EXIT_FAILURE);
		}
		if (!pid2)
		{
			write(1, "I am the second process\n", 25);
			close(pipefd[1]);
			waitpid(pid1, NULL, 0);
			cmd = ft_split(argv[3], ' ');
			execute_command(cmd[0], cmd , env);
		}
		else
		{
			close(pipefd[0]);
			waitpid(pid1, NULL, 0);
			waitpid(pid2, NULL, 0);
			write(1, "I am a not a child process\n", 27);
		}
	}
	return (0);
}
