#include "monty.h"

FILE *file = NULL;

/**
 * main - interprets monty bytecode
 * @ac: argument count
 * @av: argument vector
 * Return: Always 0
 **/
int main(int ac, char *av[])
{
	int fd;

	if (ac != 2)
		gtfo("USAGE: monty file");

	fd = open(av[1], O_RDONLY);

	if (fd == -1)
		gtfo("Error: Can't open file");

	file = fopen(av[1], "r");

	if (file == NULL)
		gtfo("Error: malloc failed");

	monty(file);
	return (0);
}

/**
 * monty - monty bytecode interpreter
 * @file: file
 * Return: void
 **/
void monty(FILE *file)
{
	unsigned int l = 1, mode = 1, i;
	size_t size = 0;
	char *token, *s = NULL;
	stack_t *h = NULL;
	op f = NULL;

	for (; 1; l++)
	{
		if (getline(&s, &size, file) == -1)
		{
			free(s);
			fclose(file);
			free_list(h);
			exit(EXIT_SUCCESS);
		}

		token = strtok(s, " \n\t");
		if (token == NULL)
			continue;

		f = get_op(token, &mode);

		if (f == NULL)
			GTFO(&h, l, "Unknown instruction ", &s);

		i = l;

		if (its_a_match("push", token))
		{
			token = strtok(NULL, " \n\t");
			if (is_a_number(token))
				i = atoi(token);
			else
			{
				free(s);
				GTFO(&h, l, "usage: push integer", NULL);
			}
		}
		f(&h, i);
	}
}

/**
 * get_op - matches a string with an op function
 * @token: string to match with an op func
 * @mode: if 1, list is stack. if 0, list is queue
 * Return: matched op function | NULL if no match found
 **/
op get_op(char *token, unsigned int *mode)
{
	int i;
	instruction_t ops[] = {
		{"push", add_top},
		{"pall", pall},
		{"pint", pint},
		{"pop", pop},
		{"swap", swap},
		{"add", add_op},
		{"sub", sub},
		{"div", div_op},
		{"mul", mul},
		{"mod", mod},
		{"pchar", pchar},
		{"rotl", rotl},
		{"rotr", rotr},
		{"pstr", pstr},
		{"nop", nop},
	};

	if (its_a_match("stack", token))
	{
		*mode = 1;
		return (nop);
	}
	if (its_a_match("queue", token))
	{
		*mode = 0;
		return (nop);
	}
	if (*mode == 0)
		ops[0].f = add_bottom;

	for (i = 0; i < 14; i++)
		if (its_a_match(ops[i].opcode, token))
			return (ops[i].f);

	if (*token == '#')
		return (nop);

	return (NULL);
}

/**
 * its_a_match - matches a command to an op_code
 * @opcode: opcode
 * @token: command
 * Return: 1 if match, 0 if not
 **/
int its_a_match(char *opcode, char *token)
{
	int i;

	for (i = 0; opcode[i]; i++)
		if (opcode[i] != token[i])
			return (0);

	if (token[i] != '\0')
		return (0);

	return (1);
}

/**
 * is_a_number - returns true if the string is a number
 * @s: string
 * Return: true if number | false if not number
 **/
bool is_a_number(char *s)
{
	if (*s == '-')
		s++;

	for (; *s; s++)
		if (*s < '0' || *s > '9')
			return (false);

	return (true);
}
