/* ************************************************************************** */
/*                                                                            */
/*                                                         ::::::::           */
/*   pipex.h                                             :+:    :+:           */
/*                                                      +:+                   */
/*   By: makurek <marvin@42.fr>                        +#+                    */
/*                                                    +#+                     */
/*   Created: 2025/02/26 15:29:35 by makurek        #+#    #+#                */
/*   Updated: 2025/02/26 15:34:49 by makurek        ########   odam.nl        */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <unistd.h>
# include <stdio.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <errno.h>
# include <string.h>
# include <fcntl.h>
# include <stdlib.h>
# include "libft.h"

typedef struct s_process_info {
	int			fd_in;
	int			fd_out;
	const char	*output_file;
	char		**cmd_args;
	char		**env;
}	t_process_info;

//support.c
void	error_exit(const char *msg);
void	execute_command(char *cmd, char **args, char **env);
void	execute_process(t_process_info info);
//heredoc.c
void	handle_heredoc(const char *limiter, int temp_fd);
void	setup_heredoc(char **argv, int is_heredoc,
			const char **input_file, char **limiter);
//pipes.c
int		create_pipes(int num_pipes, int pipes[num_pipes][2]);
void	initialize_pipes(int num_pipes, int (**pipes)[2]);
void	execute_pipeline(char **env, int (*pipes)[2],
			int num_pipes, char **argv, int argc);
//fork.c
int		fork_first_child(t_process_info *info,
			int pipefd[2], const char *input_file, char **argv);
int		fork_middle_children(t_process_info *info,
			int pipes[][2], int num_pipes, char **argv);
int		fork_last_child(t_process_info *info,
			int pipefd[2], char **argv, int argc);
#endif
