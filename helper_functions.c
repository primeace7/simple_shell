#include "shell.h"

/**
 * get_inputline - read a line from stdin
 * @destination: a buffer to store the input from stdin
 * Return: the number of characters read, or -1 on EOF
 */

ssize_t get_inputline(char **destination)
{
	char **linebuf, *test; /* to store the characters read from stdin*/
	size_t bufsize; /*to store the number of characters stored in linebuf*/
	ssize_t bytes_read; /*number of bytes read, the return value of getline*/

	test = NULL;
	linebuf = &test;
/*getline() returns -1 on failure, or when it encounters EOF*/
	bytes_read = getline(linebuf, &bufsize, stdin);

	if (bytes_read == -1 || bytes_read == EOF)
		return (bytes_read);
	*destination = malloc(bytes_read + 1);
	if (*destination == NULL)
		perror("getline() - Couldn't allocate destination memory");

	strcpy(*destination, *linebuf);
	free(*linebuf);

	return (bytes_read);
}

/**
 * strip - strip the input (usually the output from getline()) of
 * any whitespace (including linefeeds) before tokenizing
 * @input: pointer to the string to strip
 * Return: nothing. The string is stripped in place
 */
void strip(char **input)
{
	int i, j, hold;

	if (*input != NULL)
	{
		for (i = 0; (*input)[i] != '\0'; i++)
		{
			hold = i;
			while ((*input)[i] == ' ' || (*input)[i] == '\n')
			{
				for (j = i; (*input)[j] != '\0'; j++)
					(*input)[j] = (*input)[j + 1];
				i = hold;
			}
		}
	}
}


/**
 * ops_error - handle errors in the tokenize function
 * @id: an error id that determines how to handle error
 * Return: nothing
 * Description: The error ids are:
 * 0 = empty input string
 * 1 = no token in input string
 * 2 = memory allocation error
 */

void ops_error(int id)
{
	if (id == 0)
	{
		printf("Input string is empty\n");
		exit(EXIT_FAILURE);
	}

	if (id == 1)
	{
		printf("There are no tokens in input string\n");
		exit(EXIT_FAILURE);
	}

	if (id == 2)
	{
		printf("Couldn't allocate memory for token\n");
		exit(EXIT_FAILURE);
	}
}

/**
 * tokenize - convert a string to an array of tokens
 * @string_to_split: pointer to the string to split into tokens
 * @tokenized_buf: NULL-terminated array to store pointers to generated tokens
 * Return: nothing
 */

void tokenize(char *string_to_split, char ***tokenized_buf)
{
	char **placeholder, *hold, *token;
	int count, string_len;

	string_len = 0;
	count = 0;
	if (string_to_split == NULL) /*check that input isn't empty*/
		ops_error(0);
	hold = strtok(string_to_split, " ");

	if (hold == NULL)
		ops_error(1);
	string_len = strlen(hold) + 1; /*add one to store null byte*/
	token = malloc(string_len * sizeof(char));/*allocate space for 1 token*/
	if (token == NULL)
		ops_error(2);

	placeholder = malloc(sizeof(hold));
	if (placeholder == NULL)
		ops_error(2);
	placeholder[count] = strcpy(token, hold);
	count++;

	while ((hold = strtok(NULL, " ")) != NULL)
	{
		count++;
		string_len = strlen(hold) + 1;
		token = malloc(string_len * sizeof(char));
		if (token == NULL)
			ops_error(2);
		placeholder = realloc(placeholder, count * sizeof(hold));
		if (placeholder == NULL)
			ops_error(2);
		placeholder[count - 1] = strcpy(token, hold); }
	count++;

	placeholder = realloc(placeholder, count * sizeof(hold));
	if (placeholder == NULL)
		ops_error(2);
	placeholder[count - 1] = NULL;
	*tokenized_buf = placeholder; }
