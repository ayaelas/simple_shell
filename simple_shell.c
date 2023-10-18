#include "main.h"

/**
 * child - function
 * @cmd_path : command path
 * @args : arguments
 */
void child(char *cmd_path, char **args)
{
	if (execve(cmd_path, args, NULL) == -1)
	{
		perror("execve");
		exit(1);
	}
	arr_free(args);
	free(cmd_path);
	exit(0);
}

/**
 * parent - function
 * @id : id
 * @status : state
 * @cmd_path : command path
 * @args : arguments
 */
void parent(int id, int *status, char *cmd_path, char **args)
{
	if (waitpid(id, status, 0) == -1)
	{
		perror("waitpid");
		exit(1);
	}
	if (WIFEXITED(*status))
		*status = WEXITSTATUS(*status);
	free(cmd_path);
	arr_free(args);
}

/**
 * main - shell
 * @ac: arg counter
 * @av: args we pass to the main
 * @env: the env
 * Return: int
 */
int main(int ac __attribute__((unused)), char **av, char **env)
{
	int id, status = 0, counter = 0;
	char *cmd_path;
	char **args;

	while (1)
	{
		if (lexer_parser(status, &args) == -1)
			continue;

		counter++;
		cmd_path = check_path(args[0], env);
		if (_strcmp(args[0], "exit") == 0 && cmd_path)
		{
			arr_free(args);
			free(cmd_path);
			exit(status);
		}
		else if (_strcmp(args[0], "env") == 0 && cmd_path)
		{
			_env(env);
			arr_free(args);
			free(cmd_path);
			continue;
		}
		if (cmd_path == 0)
		{
			cmd_not_found(av[0], counter, args[0], &status);
			arr_free(args);
			continue;
		}

		id = fork();
		if (id == -1)
			exit(1);
		if (id == 0)
			child(cmd_path, args);
		else
			parent(id, &status, cmd_path, args);
	}
	return (0);
}
