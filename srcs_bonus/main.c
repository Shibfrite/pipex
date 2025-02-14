/* ************************************************************************** */
/*                                                                            */
/*                                                         ::::::::           */
/*   main.c                                              :+:    :+:           */
/*                                                      +:+                   */
/*   By: makurek <marvin@42.fr>                        +#+                    */
/*                                                    +#+                     */
/*   Created: 2025/02/14 20:11:52 by makurek        #+#    #+#                */
/*   Updated: 2025/02/14 20:19:33 by makurek        ########   odam.nl        */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	handle_heredoc(const char *limiter, int temp_fd)
{
	char	buffer[BUFSIZ];
	ssize_t	bytes_read;
	char	*newline;
	ssize_t	len;

	while (1)
	{
		write(STDOUT_FILENO, "> ", 2);
		bytes_read = read(STDIN_FILENO, buffer, sizeof(buffer) - 1);
		if (bytes_read <= 0)
		{
			if (bytes_read < 0)
				error_exit("read");
			break ;
		}
		buffer[bytes_read] = '\0';
		newline = strchr(buffer, '\n');
		if (newline != NULL)
			*newline = '\0';
		if (strcmp(buffer, limiter) == 0)
			break ;
		len = strlen(buffer);
		if (write(temp_fd, buffer, len) != len
			|| (newline && write(temp_fd, "\n", 1) != 1))
			error_exit("write");
	}
}

void	init_process_info(t_process_info *info, char **env)
{
	info->fd_in = -1;
	info->fd_out = -1;
	info->output_file = NULL;
	info->cmd_args = NULL;
	info->env = env;
}

int	create_pipes(int num_pipes, int pipes[num_pipes][2])
{
	int	i;

	i = -1;
	while (++i < num_pipes)
		if (pipe(pipes[i]) == -1)
			error_exit("pipe");
	return (EXIT_SUCCESS);
}

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
		info->fd_out = pipefd[1];
		info->output_file = NULL;
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

	i = -1;
	while (++i < num_pipes - 1)
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

int	parse_arguments(int argc, char **argv,
	const char **input_file, int *is_heredoc, int *num_pipes)
{
	int	result;

	result = 0;
	if (argc < 5)
	{
		errno = EINVAL;
		error_exit("Usage: ./pipex [here_doc LIMITER file1 \"cmd1\" ... \"cmdN\" file2\n");
	}
	*input_file = argv[1];
	*is_heredoc = 0;
	if (strcmp(argv[1], "here_doc") == 0)
	{
		if (argc < 6)
		{
			errno = EINVAL;
			error_exit("Usage: ./pipex here_doc LIMITER \"cmd1\" ... \"cmdN\" file2\n");
		}
		*num_pipes = argc - 4;
		*is_heredoc = 1;
		result = 1;
	}
	else
		*num_pipes = argc - 3;
	return (result);
}

void	setup_heredoc(char **argv, int is_heredoc, const char **input_file, char **limiter)
{
	int	temp_fd;

	if (is_heredoc)
	{
		*limiter = argv[2];
		temp_fd = open("pipex.tmp", O_CREAT | O_RDWR | O_TRUNC, 0644);
		if (temp_fd == -1)
			error_exit("open");
		handle_heredoc(*limiter, temp_fd);
		close(temp_fd);
		*input_file = "pipex.tmp";
		argv += 2;
	}
}

void initialize_pipes(int num_pipes, int (**pipes)[2])
{
	int i;

	*pipes = malloc(num_pipes * sizeof(**pipes));
	if (!*pipes)
		error_exit("malloc");
	i = -1;
	while (++i < num_pipes)
		if (pipe((*pipes)[i]) == -1)
			error_exit("pipe");
}

void execute_pipeline(t_process_info *process_info, int (*pipes)[2], int num_pipes, char **argv, int argc)
{
	int	i;

	if (fork_first_child(process_info, pipes[0], process_info->env, argv) == EXIT_FAILURE)
		error_exit("first child failed");
	if (fork_middle_children(process_info, pipes, num_pipes, argv) == EXIT_FAILURE)
		error_exit("middle children failed");
	if (fork_last_child(process_info, pipes[num_pipes - 2], argv, argc) == EXIT_FAILURE)
		error_exit("last child failed");
	i = 0;
	while (i++ < num_pipes)
		wait(NULL);
}

void cleanup_resources(int is_heredoc, int (*pipes)[2])
{
	free(pipes);
	if (is_heredoc)
		unlink("pipex.tmp");
}

int main(int argc, char **argv, char **env)
{
	const char	*input_file;
	int			num_pipes;
	int			is_heredoc;
	int			(*pipes)[2];
	char		*limiter;
	int			heredoc_mode;

	input_file = NULL;
	num_pipes = 0;
	is_heredoc = 0;
	pipes = NULL;
	limiter = NULL;
	heredoc_mode = parse_arguments(argc, argv, &input_file, &is_heredoc, &num_pipes);
	setup_heredoc(argv, is_heredoc, &input_file, &limiter);
	initialize_pipes(num_pipes, &pipes);
	t_process_info process_info;
	init_process_info(&process_info, env);
	execute_pipeline(&process_info, pipes, num_pipes, argv, argc);
	cleanup_resources(is_heredoc, pipes);
	return (EXIT_SUCCESS);
}
