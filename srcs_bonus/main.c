/* ************************************************************************** */
/*                                                                            */
/*                                                         ::::::::           */
/*   main.c                                              :+:    :+:           */
/*                                                      +:+                   */
/*   By: makurek <marvin@42.fr>                        +#+                    */
/*                                                    +#+                     */
/*   Created: 2025/02/14 20:11:52 by makurek        #+#    #+#                */
/*   Updated: 2025/02/17 19:20:23 by makurek        ########   odam.nl        */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	parse_arguments(int argc, char **argv,
	const char **input_file)
{
	int	is_heredoc;

	if (argc < 5)
	{
		errno = EINVAL;
		error_exit("Usage: ./pipex file1 \"cmd1\" ... \"cmdN\" file2\n");
	}
	*input_file = argv[1];
	is_heredoc = 0;
	if (!strcmp(argv[1], "here_doc"))
	{
		if (argc < 6)
		{
			errno = EINVAL;
			ft_putstr_fd("Usage: ./pipex here_doc LIMITER ", 2);
			error_exit("\"cmd1\" ... \"cmdN\" file2\n");
		}
		is_heredoc = 1;
	}
	return (is_heredoc);
}

void	cleanup_resources(int is_heredoc, int (*pipes)[2])
{
	free(pipes);
	if (is_heredoc)
		unlink("pipex.tmp");
}

int	main(int argc, char **argv, char **env)
{
	const char	*input_file;
	int			num_pipes;
	int			is_heredoc;
	int			(*pipes)[2];
	char		*limiter;

	input_file = NULL;
	pipes = NULL;
	limiter = NULL;
	is_heredoc = parse_arguments(argc, argv, &input_file);
	setup_heredoc(argv, is_heredoc, &input_file, &limiter);
	num_pipes = argc - 3 - is_heredoc;
	initialize_pipes(num_pipes, &pipes);
	if (is_heredoc)
		argv[1] = "pipex.tmp";
	execute_pipeline(env, pipes, num_pipes, argv, argc);
	cleanup_resources(is_heredoc, pipes);
	return (EXIT_SUCCESS);
}
