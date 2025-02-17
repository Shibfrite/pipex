/* ************************************************************************** */
/*                                                                            */
/*                                                         ::::::::           */
/*   pipes.c                                             :+:    :+:           */
/*                                                      +:+                   */
/*   By: makurek <marvin@42.fr>                        +#+                    */
/*                                                    +#+                     */
/*   Created: 2025/02/17 16:51:54 by makurek        #+#    #+#                */
/*   Updated: 2025/02/17 19:22:10 by makurek        ########   odam.nl        */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	create_pipes(int num_pipes, int pipes[num_pipes][2])
{
	int	i;

	i = -1;
	while (++i < num_pipes)
		if (pipe(pipes[i]) == -1)
			error_exit("pipe");
	return (EXIT_SUCCESS);
}

void	initialize_pipes(int num_pipes, int (**pipes)[2])
{
	int	i;

	*pipes = malloc(num_pipes * sizeof(**pipes));
	if (!*pipes)
		error_exit("malloc");
	i = -1;
	while (++i < num_pipes)
		if (pipe((*pipes)[i]) == -1)
			error_exit("pipe");
}

void	execute_pipeline(char **env,
		int (*pipes)[2], int num_pipes, char **argv, int argc)
{
	t_process_info	process_info;

	process_info.env = env;
	if (fork_first_child(&process_info,
			pipes[0], argv[1], argv) == EXIT_FAILURE)
		error_exit("first child failed");
	if (fork_middle_children(&process_info,
			pipes, num_pipes, argv) == EXIT_FAILURE)
		error_exit("middle children failed");
	if (fork_last_child(&process_info,
			pipes[num_pipes - 2], argv, argc) == EXIT_FAILURE)
		error_exit("last child failed");
	while (num_pipes--)
		wait(NULL);
}
