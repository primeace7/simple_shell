#include "shell.h"


/**
 * fork_child - fork a child process to execute input command
 * Return: the pid of the forked child, or -1 on error
 */

pid_t fork_child(void)
{
	pid_t child_fork;

	child_fork = fork();
	return (child_fork);
}

/**
 * display_prompt - display a shell prompt ($) and wait for input
 *
 * Return: nothing
 *
 */

void display_prompt(void)
{

	printf("$ ");
}
