/* ************************************************************************** */
/*																			*/
/*														 ::::::::		   */
/*   support.c                                           :+:    :+:           */
/*													  +:+				   */
/*   By: makurek <marvin@42.fr>						+#+					*/
/*													+#+					 */
/*   Created: 2025/02/14 19:40:59 by makurek		#+#	#+#				*/
/*   Updated: 2025/03/03 15:18:23 by makurek        ########   odam.nl        */
/*																			*/
/* ************************************************************************** */

#include "pipex.h"

char	*ft_strcat(char *dest, const char *src)
{
	char	*ptr;

	ptr = dest;
	while (*ptr)
		ptr++;
	while (*src)
		*ptr++ = *src++;
	*ptr = '\0';
	return (dest);
}

char	*ft_strcpy(char *dest, const char *src)
{
	char	*ptr;

	ptr = dest;
	while (*src)
	{
		*ptr = *src;
		ptr++;
		src++;
	}
	*ptr = '\0';
	return (ptr);
}

void error_exit(const char *msg, char *data_to_free)
{
    if (data_to_free)
        free(data_to_free);
    perror(msg);
    exit(EXIT_FAILURE);
}

void execute_process(t_process_info info)
{
    char **parsed_args;
    char *command;

    command = info.cmd_args[0];
    if (info.fd_in != -1)
    {
        dup2(info.fd_in, STDIN_FILENO);
        close(info.fd_in);
    }
    if (info.output_file)
    {
        info.fd_out = open(info.output_file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
        if (info.fd_out == -1)
            error_exit("open", NULL);
    }
    if (info.fd_out != -1)
    {
        dup2(info.fd_out, STDOUT_FILENO);
        close(info.fd_out);
    }
    parsed_args = parse_command(command);
    if (!parsed_args)
        error_exit("malloc", NULL);
    execute_command(parsed_args[0], parsed_args, info.env);
    free_array(parsed_args);
    exit(EXIT_FAILURE);
}
