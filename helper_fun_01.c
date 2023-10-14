#include "main.h"

/**
 * is_slash - check if there is slash
 * @cmd: command
 * Return: 1 or 0
 */
int is_slash(char *cmd)
{
	int i = 0;

	while (cmd[i])
	{
		if (cmd[i] == '/')
			return (1);
		i++;
	}
	return (0);
}

/**
 * check_path - check if it's a valid path
 * @prog: command we get
 * @env: env
 * Return: full command path
 */
char *check_path(char *prog, char **env)
{
	char *res, *holder;
	struct stat st;
	int found_slash = is_slash(prog);
	char *path = _getenv("PATH", env);

	if (found_slash && !stat(prog, &st))
	{
		free(path);
		return (_strdup(prog));
	}
	if (!path || !*path)
	{
		free(path);
		return (NULL);
	}

	res = strtok(path, ":");
	while (res)
	{
		holder = malloc(_strlen(res) + _strlen(prog) + 2);
		_strcpy(holder, res);
		_strcat(holder, "/");
		_strcat(holder, prog);

		if (!stat(holder, &st))
		{
			free(path);
			return (holder);
		}
		free(holder);
		res = strtok(NULL, ":");
	}
	free(path);
	return (NULL);
}


/**
 * tokenn - split all the command
 * @str: the command we get
 * Return: an array of the splited command
 */
char **tokenn(char *str)
{
	char *token, **tokens;
	int i = 0;

	tokens = malloc(1025 * sizeof(char *));
	if (tokens == NULL)
	{
		perror("hhhh");
		exit(EXIT_FAILURE);
	}
	token = strtok(str, " \t\n");
	while (token != NULL)
	{
		tokens[i] = strdup(token);
		token = strtok(NULL, " \t\n");
		i++;
	}
	tokens[i] = NULL;
	return (tokens);
}
