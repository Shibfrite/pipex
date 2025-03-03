/* ************************************************************************** */
/*																			*/
/*														 ::::::::		   */
/*   exec.c                                              :+:    :+:           */
/*													  +:+				   */
/*   By: makurek <marvin@42.fr>						+#+					*/
/*													+#+					 */
/*   Created: 2025/03/03 14:20:50 by makurek		#+#	#+#				*/
/*   Updated: 2025/03/03 20:24:35 by makurek        ########   odam.nl        */
/*																			*/
/* ************************************************************************** */

#include "pipex.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

char	*find_path_in_env(char **env)
{
	int	i;

	i = -1;
	while (env[++i])
		if (!strncmp(env[i], "PATH=", 5))
			return (env[i] + 5);
	return (NULL);
}

char	**split_paths(const char *path_env)
{
	char	**paths;

	paths = ft_split(path_env, ':');
	if (!paths)
		error_exit("malloc", NULL);
	return (paths);
}

void	free_array(char **paths)
{
	int	i;

	i = 0;
	while (paths[i])
		free(paths[i++]);
	free(paths);
}

int	find_and_execute_command(const char *cmd,
		char **args, char **env, char **paths)

{
	char	*full_path;
	int		i;
	int		found;

	full_path = NULL;
	i = 0;
	found = 0;
	while (paths[i])
	{
		full_path = malloc(strlen(paths[i]) + strlen(cmd) + 2);
		if (!full_path)
		{
			free_array(paths);
			error_exit("malloc", NULL);
		}
		ft_strcpy(full_path, paths[i]);
		ft_strcat(full_path, "/");
		ft_strcat(full_path, cmd);
		if (!access(full_path, X_OK))
			execve(full_path, args, env);
		free(full_path);
		i++;
	}
	return (found);
}

void	execute_command(char *cmd, char **args, char **env)
{
	char	*path_env;
	char	**paths;
	int		found;

	path_env = NULL;
	paths = NULL;
	found = 0;
	path_env = find_path_in_env(env);
	if (!path_env)
		error_exit("PATH not found in environment variables", NULL);
	paths = split_paths(path_env);
	if (!paths)
		error_exit("Failed to split PATH", NULL);
	found = find_and_execute_command(cmd, args, env, paths);
	free_array(paths);
	if (!found)
		error_exit("Command not found in path", NULL);
	exit(EXIT_FAILURE);
}
