/* ************************************************************************** */
/*                                                                            */
/*                                                         ::::::::           */
/*   pipex.h                                             :+:    :+:           */
/*                                                      +:+                   */
/*   By: makurek <marvin@42.fr>                        +#+                    */
/*                                                    +#+                     */
/*   Created: 2025/02/26 15:29:35 by makurek        #+#    #+#                */
/*   Updated: 2025/03/03 15:18:04 by makurek        ########   odam.nl        */
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
char    *ft_strcpy(char *dest, const char *src);
char    *ft_strcat(char *dest, const char *src);
void	error_exit(const char *msg, char *data_to_free);
void	execute_process(t_process_info info);

//exec.c
void	execute_command(char *cmd, char **args, char **env);
void    free_array(char **paths);

//token.c
int count_tokens(const char *command);
char *extract_token(const char *command, int *i);
char *extract_token(const char *command, int *i);
char **parse_command(const char *command);


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
