/* ************************************************************************** */
/*                                                                            */
/*                                                         ::::::::           */
/*   support.c                                           :+:    :+:           */
/*                                                      +:+                   */
/*   By: makurek <marvin@42.fr>                        +#+                    */
/*                                                    +#+                     */
/*   Created: 2025/02/14 19:40:59 by makurek        #+#    #+#                */
/*   Updated: 2025/02/26 15:15:03 by makurek        ########   odam.nl        */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	error_exit(const char *msg)
{
	perror(msg);
	exit(EXIT_FAILURE);
}

void	execute_command(char *cmd, char **args, char **env)
{
	const char	*paths[3];
	char		*full_path;
	int			i;

	paths[0] = "/bin";
	paths[1] = "/usr/bin";
	paths[2] = NULL;
	i = -1;
	while (paths[++i])
	{
		full_path = ft_strdup(paths[i]);
		if (!full_path)
			error_exit("malloc");
		if (strcat(full_path, "/") && strcat(full_path, cmd)
			&& execve(full_path, args, env) == -1)
		{
			free(full_path);
			ft_putendl_fd(cmd, 2);
			error_exit("execve");
		}
		free(full_path);
	}
	exit(EXIT_FAILURE);
}

void	execute_process(t_process_info info)
{
	char	**parsed_args;

	if (info.fd_in != -1)
	{
		dup2(info.fd_in, STDIN_FILENO);
		close(info.fd_in);
	}
	if (info.output_file)
	{
		info.fd_out = open(info.output_file, O_WRONLY
				| O_CREAT | O_TRUNC, 0644);
		if (info.fd_out == -1)
			error_exit("open");
	}
	if (info.fd_out != -1)
	{
		dup2(info.fd_out, STDOUT_FILENO);
		close(info.fd_out);
	}
	parsed_args = ft_split(info.cmd_args[0], ' ');
	execute_command(parsed_args[0], parsed_args, info.env);
	exit(EXIT_FAILURE);
}
