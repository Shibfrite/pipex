/* ************************************************************************** */
/*																			*/
/*														 ::::::::		   */
/*   token.c											 :+:	:+:		   */
/*													  +:+				   */
/*   By: makurek <marvin@42.fr>						+#+					*/
/*													+#+					 */
/*   Created: 2025/03/03 15:06:30 by makurek		#+#	#+#				*/
/*   Updated: 2025/03/03 20:25:01 by makurek		########   odam.nl		*/
/*																			*/
/* ************************************************************************** */

#include "pipex.h"

int	is_quote(char c)
{
    return c == '\'' || c == '"';
}

int end_token(const char *command, int i, int in_quote)
{
    while (command[i])
    {
        if (in_quote)
        {
            if (command[i] == in_quote)
                return (i + 1);
        }
        else
        {
            if (is_quote(command[i]))
                error_exit("Unexpected quote", NULL);
            if (is_space(command[i]))
                return (i);
        }
        i++;
    }
    if (in_quote)
        error_exit("No ending quote", NULL);
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
		if (is_quote(command[i]))
			in_quote = command[i++];
		else
			in_quote = 0;
		i = end_token(command, i, in_quote);
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
    
    // Skip leading spaces
    while (is_space(command[*i]))
        (*i)++;
    
    // Check for quotes
    if (command[*i] == '\'' || command[*i] == '\"')
    {
        in_quote = command[*i];
        (*i)++; // Skip the opening quote
        start = *i; // Start after the opening quote
    }
    else
    {
        start = *i;
        in_quote = 0;
    }
    
    // Find the end of the token
    *i = end_token(command, *i, in_quote);
    len = *i - start;
    
    // Allocate memory for the token
    char *token = malloc((len + 1) * sizeof(char));
    if (!token)
        return NULL;
    
    // Copy the token and null-terminate it
    strncpy(token, &command[start], len);
    token[len] = '\0';
    
    // Remove the closing quote if necessary
    if (in_quote && len > 0)
    {
        token[len - 1] = '\0'; // Remove the closing quote
    }
    
    return token;
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
