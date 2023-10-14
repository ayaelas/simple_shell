#include "main.h"

/**
 * _env - print the env
 * @env: the env
 * Return: nothing
 */
void _env(char **env)
{
	int i;

	for (i = 0; env[i]; i++)
	{
		write(1, env[i], _strlen(env[i]));
		write(1, "\n", 1);
	}
}
