#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

void execute_command(char *cmd, char **args, char **env) {
	const char *paths[] = {"/bin", "/usr/bin", NULL};

	for (int i = 0; paths[i] != NULL; i++)
	{
		//size_t path_len = strlen(paths[i]) + strlen(cmd) + 2; // +2 for '/' and '\0'
		char *full_path = strdup(paths[i]); // Duplicate the directory path
		if (!full_path) {
			perror("malloc");
			exit(EXIT_FAILURE);
		}

		// Append '/' and the command name
		full_path = strcat(full_path, "/");
		full_path = strcat(full_path, cmd);
		if (!access(full_path, X_OK))
		{
			if (execve(full_path, args, 0) == -1)
			{
				perror("execve");
				free(full_path);
				exit(EXIT_FAILURE);
			}
			free(full_path);
			return ;
		}
		free(full_path);
	}
	exit(EXIT_FAILURE);
}

int main(int ac, char **av, char **env) {
	// Example: Execute "ls -l"
	char *cmd = "ls";
	char *args[] = {"ls", "-l", NULL};

	execute_command(cmd, args, env);

	return 0; // This line will never be reached if execve succeeds
}
