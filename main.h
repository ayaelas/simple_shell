#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <errno.h>
#include <limits.h>
#include <fcntl.h>

char *_strcat(char *dest, char *src);
char *_strcpy(char *dest, char *src);
int _strlen(char *st);
int _strcmp(char *s1, char *s2);
char *_strdup(char *str);
void print_number(int n);
void _env(char **env);

void arr_free(char **arr);
char *_getenv(char *key, char **env);
void cmd_not_found(char *exec, int counter, char *cmd, int *status);
int lexer_parser(int status, char ***args);

char **tokenn(char *str);
char *check_path(char *prog, char **env);

#endif /* SHELL_H */
