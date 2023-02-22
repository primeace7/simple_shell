#include "shell.h"

/**
 * main - execute a simple shell
 * @argc: argument count
 * @argv: argument vector
 * @envp: environment list
 * Return: nothing
 */

int main(int argc, char **argv, char *envp[])
{
	ssize_t input_line; /*store return value of getline to check for EOF*/
	char *input_buffer, **tokenized_buf;/*tokenize user input command line*/
	int i;
	pid_t child_fork;

	input_buffer = NULL;
	tokenized_buf = NULL;
	display_prompt();
	argc = argc;
	argv = argv;

	input_line = get_inputline(&input_buffer);

	while (input_line != -1 && input_line != EOF)
	{
		tokenize(input_buffer, &tokenized_buf);
		child_fork = fork_child();

		if (child_fork == -1)
			perror("There was a fork error");
		else if (child_fork == 0)
			execute_child(tokenized_buf, envp);
		else
			wait(NULL);
		display_prompt();
		input_line = get_inputline(&input_buffer); }

	if (input_buffer != NULL)
	{
		free(input_buffer);
/*tokenized_buf is an array of pointers, it must be freed*/
		for (i = 0; tokenized_buf[i] != NULL; i++)
			free(tokenized_buf[i]);
		free(tokenized_buf); }
	if (input_line == -1 || input_line == EOF)
		printf("Process terminated: EOF encountered\n");
	exit(EXIT_SUCCESS); }

/**
 * execute_child - execite a command with execve, in the child process
 * @tokenized_buf: buffer containing pointers to input tokens
 * @envp: the environment list for execve
 * Return: nothing
 */

void execute_child(char **tokenized_buf, char *envp[])
{
	int i, child_exec;
	for (i = 0; tokenized_buf[i] != NULL; i++)
		strip(&tokenized_buf[i]);
	child_exec = execve(tokenized_buf[0], tokenized_buf, envp);
	if (child_exec == -1)
		perror("child_exec error");
	exit(EXIT_SUCCESS);
}
