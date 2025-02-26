/* ************************************************************************** */
/*                                                                            */
/*                                                         ::::::::           */
/*   heredoc.c                                           :+:    :+:           */
/*                                                      +:+                   */
/*   By: makurek <marvin@42.fr>                        +#+                    */
/*                                                    +#+                     */
/*   Created: 2025/02/17 16:54:30 by makurek        #+#    #+#                */
/*   Updated: 2025/02/26 14:57:22 by makurek        ########   odam.nl        */
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
		if (newline)
			*newline = '\0';
		if (!strcmp(buffer, limiter))
			break ;
		len = strlen(buffer);
		if (write(temp_fd, buffer, len) != len
			|| (newline && write(temp_fd, "\n", 1) != 1))
			error_exit("write");
	}
}

void	setup_heredoc(char **argv,
		int is_heredoc, const char **input_file, char **limiter)
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
