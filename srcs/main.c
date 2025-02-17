/* ************************************************************************** */
/*																			*/
/*														 ::::::::		   */
/*   main.c                                              :+:    :+:           */
/*													  +:+				   */
/*   By: makurek <marvin@42.fr>						+#+					*/
/*													+#+					 */
/*   Created: 2025/02/14 17:30:41 by makurek		#+#	#+#				*/
/*   Updated: 2025/02/17 17:26:59 by makurek        ########   odam.nl        */
/*																			*/
/* ************************************************************************** */

#include "pipex.h"

int	fork_first_child(t_process_info *info,
	int pipefd[2], const char *input_file, char **argv)
{
	pid_t	pid;

	info->fd_in = open(input_file, O_RDONLY);
	if (info->fd_in == -1)
		error_exit("open");
	pid = fork();
	if (pid == -1)
	{
		close(info->fd_in);
		error_exit("fork");
	}
	if (!pid)
	{
		dup2(info->fd_in, STDIN_FILENO);
		dup2(pipefd[1], STDOUT_FILENO);
		close(pipefd[0]);
		close(pipefd[1]);
		close(info->fd_in);
		info->cmd_args = &argv[2];
		execute_process(*info);
		exit(EXIT_FAILURE);
	}
	close(pipefd[1]);
	close(info->fd_in);
	return (pid);
}

int	fork_last_child(t_process_info *info,
	int pipefd[2], char **argv, int argc)
{
	pid_t	pid;

	info->fd_out = open(argv[argc - 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (info->fd_out == -1)
		error_exit("open");
	pid = fork();
	if (pid == -1)
	{
		close(info->fd_out);
		error_exit("fork");
	}
	if (!pid)
	{
		dup2(pipefd[0], STDIN_FILENO);
		dup2(info->fd_out, STDOUT_FILENO);
		close(pipefd[0]);
		close(info->fd_out);
		info->cmd_args = &argv[argc - 2];
		execute_process(*info);
		exit(EXIT_FAILURE);
	}
	close(pipefd[0]);
	close(info->fd_out);
	return (pid);
}

void	init_process_info(t_process_info *info, char **env)
{
	info->fd_in = -1;
	info->fd_out = -1;
	info->output_file = NULL;
	info->cmd_args = NULL;
	info->env = env;
}

int	main(int argc, char **argv, char **env)
{
	t_process_info	process_info;
	int				pipefd[2];

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
	init_process_info(&process_info, env);
	if (fork_first_child(&process_info, pipefd, argv[1], argv))
		fork_last_child(&process_info, pipefd, argv, argc);
	close(pipefd[0]);
	close(pipefd[1]);
	wait(NULL);
	wait(NULL);
	return (0);
}
