/* ************************************************************************** */
/*                                                                            */
/*                                                         ::::::::           */
/*   token.c                                             :+:    :+:           */
/*                                                      +:+                   */
/*   By: makurek <marvin@42.fr>                        +#+                    */
/*                                                    +#+                     */
/*   Created: 2025/03/03 15:06:30 by makurek        #+#    #+#                */
/*   Updated: 2025/03/03 20:25:01 by makurek        ########   odam.nl        */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	end_token(const char *command, int i, int in_quote)
{
    while (command[i])
	{
		if (in_quote)
		{
			if (command[i] == in_quote)
				return (i + 1);
		}
		else if (is_space(command[i]))
			return (i);
		i++;
	}
	return (i);
}

int count_tokens(const char *command)
{
    int count;
    int i;
    int in_quote;

    count = 0;
    i = 0;
    in_quote = 0;
    while (command[i])
    {
        while (is_space(command[i]) && command[i])
            i++;
        if (command[i] == '\'' || command[i] == '\"')
            in_quote = command[i++];
        else
            in_quote = 0;
		i = end_token(command, i, in_quote);
        if ((i > 0 && command[i - 1]) || !i)
            count++;
        in_quote = 0;
    }
    return (count);
}

char *extract_token(const char *command, int *i)
{
    int start;
    int len;
    int in_quote;

    start = *i;
    len = 0;
    in_quote = 0;
    while (is_space(command[*i]))
        (*i)++;
    if (command[*i] == '\'' || command[*i] == '\"')
    {
        in_quote = command[*i];
        (*i)++;
        start = *i;
    }
    else
    {
        start = *i;
        in_quote = 0;
    }
	*i = end_token(command, *i, in_quote);
	len = *i - start;
    char *token = malloc((len + 1) * sizeof(char));
    if (!token)
        return NULL;
    strncpy(token, &command[start], len);
    token[len] = '\0';
    if (in_quote && len > 1 && token[0] == in_quote && token[len - 1] == in_quote)
    {
        token[len - 1] = '\0';
        memmove(token, &token[1], len - 1);
    }
    return (token);
}

char **parse_command(const char *command)
{
    char **args;
    int i;
    int j;
    int token_count;

    token_count = count_tokens(command);
    if (!token_count)
        return (NULL);
    args = malloc((token_count + 1) * sizeof(char *));
    if (!args)
        return (NULL);
    i = 0;
    j = 0;
    while (j < token_count)
    {
        args[j] = extract_token(command, &i);
        if (!args[j])
        {
            free_array(args);
            return (NULL);
        }
        j++;
    }
    args[j] = NULL;
    return (args);
}
