#include "main.h"

/**
 * arr_free - free an array
 * @arr: the array u wanna free
 * Return: nothing
 */
void arr_free(char **arr)
{
	int i = 0;

	while (arr[i] != NULL)
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}

/**
 * subequal - split the env using '='
 * @temp: the env line u wanna split
 * Return: a peer of key and value
 */
char **subequal(char *temp)
{
	int k = 0, len;
	char **array;

	array = malloc(sizeof(char *) * 3);
	array[0] = _strdup(strtok(temp, "="));
	len = _strlen(temp + _strlen(array[0]) + 1);
	if (len > 0)
	{
		array[1] = malloc(sizeof(char) * len + 1);
		while (k < len)
		{
			array[1][k] = temp[_strlen(array[0]) + k + 1];
			k++;
		}
		array[1][k] = 0;
	}
	else
		array[1] = _strdup("");
	array[2] = NULL;

	return (array);
}

/**
 * _getenv - get the env value py key
 * @key: the key
 * @env: env
 * Return: value of the env
 */
char *_getenv(char *key, char **env)
{
	char *res, *line;
	char **array;
	int i = 0;

	while (env[i])
	{
		line = _strdup(env[i]);
		array = subequal(line);
		free(line);
		if (_strcmp(array[0], key) == 0 && array[1])
		{
			res = _strdup(array[1]);
			arr_free(array);
			return (res);
		}
		arr_free(array);
		i++;
	}
	return (NULL);
}

/**
 * cmd_not_found - print command not found
 * @exec: name of the program
 * @counter: the count of cmd
 * @cmd: command we get
 * @status: status code
 * Return: nothing
 */
void cmd_not_found(char *exec, int counter, char *cmd, int *status)
{
	write(2, exec, _strlen(exec));
	write(2, ": ", _strlen(": "));
	print_number(counter);
	write(2, ": ", _strlen(": "));
	write(2, cmd, _strlen(cmd));
	write(2, ": not found\n", _strlen(": not found\n"));
	*status = 127;
}

/**
 * lexer_parser - read the command form stdin and split it
 * @status: status code
 * @args: command holder
 * Return: -1 or 0
 */
int lexer_parser(int status, char ***args)
{
	char *buf;
	int i;
	size_t size_buf;

	size_buf = 0;
	buf = NULL;

	if (isatty(STDIN_FILENO))
		write(1, "$ ", 2);
	i = getline(&buf, &size_buf, stdin);
	if (i == -1)
	{
		free(buf);
		exit(status);
	}
	buf[i - 1] = '\0';

	*args = tokenn(buf);
	free(buf);
	if (*args == NULL || *args[0] == NULL)
	{
		free(*args);
		return (-1);
	}
	return (0);
}
