/* ************************************************************************** */
/*                                                                            */
/*                                                         ::::::::           */
/*   fork.c                                              :+:    :+:           */
/*                                                      +:+                   */
/*   By: makurek <marvin@42.fr>                        +#+                    */
/*                                                    +#+                     */
/*   Created: 2025/02/17 16:57:47 by makurek        #+#    #+#                */
/*   Updated: 2025/02/26 15:26:04 by makurek        ########   odam.nl        */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	fork_first_child(t_process_info *info,
	int pipefd[2], const char *input_file, char **argv)
{
	pid_t	pid;
	int		here_doc;

	info->fd_in = open(input_file, O_RDONLY);
	if (info->fd_in == -1)
	{
		ft_putstr_fd((char *)input_file, 2);
		error_exit("open");
	}
	pid = fork();
	if (pid == -1)
	{
		close(info->fd_in);
		error_exit("fork");
	}
	if (!pid)
	{
		info->fd_out = pipefd[1];
		info->output_file = NULL;
		if (!strcmp(info->cmd_args, "here_doc"))
			here_doc++;
		info->cmd_args = &argv[2];
		execute_process(*info);
	}
	close(pipefd[1]);
	close(info->fd_in);
	return (EXIT_SUCCESS);
}

int	fork_middle_children(t_process_info *info,
	int pipes[][2], int num_pipes, char **argv)
{
	int		i;
	pid_t	pid;

	i = 0;
	while (++i < num_pipes - 2)
	{
		pid = fork();
		if (pid == -1)
			error_exit("fork");
		if (!pid)
		{
			info->fd_in = pipes[i - 1][0];
			info->fd_out = pipes[i][1];
			info->output_file = NULL;
			info->cmd_args = &argv[i + 2];
			execute_process(*info);
		}
		close(pipes[i - 1][0]);
		close(pipes[i][1]);
	}
	return (EXIT_SUCCESS);
}

int	fork_last_child(t_process_info *info,
	int pipefd[2], char **argv, int argc)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
		error_exit("fork");
	if (!pid)
	{
		info->fd_in = pipefd[0];
		info->fd_out = -1;
		info->output_file = argv[argc - 1];
		info->cmd_args = &argv[argc - 2];
		execute_process(*info);
	}
	close(pipefd[0]);
	return (EXIT_SUCCESS);
}
