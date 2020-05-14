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
	if (ac != 2)
	{
		dprintf(STDERR_FILENO, "USAGE: monty file\n");
		exit(EXIT_FAILURE);
	}

	file = fopen(av[1], "r");

	if (file == NULL)
	{
		dprintf(STDERR_FILENO, "Error: Can't open file %s\n", av[1]);
		exit(EXIT_FAILURE);
	}

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
	unsigned int line = 1, i;
	int stack = 1;
	size_t bufsize = 0;
	char *tmp, *buf = NULL;
	stack_t *head = NULL;

	for (; 1; line++)
	{
		if (getline(&buf, &bufsize, file) == -1)
		{
			free(buf);
			fclose(file);
			free_list(head);
			exit(EXIT_SUCCESS);
		}

		tmp = strtok(buf, " ");

		if (strcmp(tmp, "push") != 0)
		{
			get_op(tmp, line, &head, &stack, &buf);
			continue;
		}

		for (i = 0, tmp = strtok(NULL, " "); tmp[i]; i++)
			if ((tmp[i] < '0' && tmp[i] != '\n') || tmp[i] > '9')
			{
				free(buf);
				exitor(&head, line, "usage: push integer");
			}

		if (stack)
			add_top(&head, atoi(tmp));
		else
			add_bottom(&head, atoi(tmp));
	}
}

/**
 * get_op - matches a string with an op function and executes
 * @s: string to match with an op func
 * @l: line number of string
 * @h: head pointer to list
 * @stack: if true, treat stack as stack. if false, treat as queue
 * @buf: buffer holding rest of line. imported for deletion
 * Return: void
 **/
void get_op(char *s, unsigned int l, stack_t **h, int *stack, char **buf)
{
	instruction_t ops[] = {
		{"pall", pall},
		{"pint", pint},
		{"pop", pop},
		{"swap", swap},
		{"nop", nop},
		{"add", add_op},
		{"sub", sub},
		{"div", div_op},
		{"mul", mul},
		{"mod", mod},
		{"pchar", pchar},
		{"rotl", rotl},
		{"rotr", rotr},
		{"pstr", pstr},
	};
	size_t size = sizeof(ops) / sizeof(instruction_t), i;

	for (i = 0; i < size; i++)
		if (its_a_match(ops[i].opcode, s))
		{
			free(*buf);
			ops[i].f(h, l);
			*buf = NULL;
			return;
		}

	if (its_a_match("stack", s))
		*stack = 1;
	else if (its_a_match("queue", s))
		*stack = 0;
	else if (*s != '#')
	{
		dprintf(STDERR_FILENO, "L%u: Unknown instruction %s", l, s);
		free(*buf);
		exitor(h, 0, NULL);
	}
}

/**
 * its_a_match - matches a command to an op_code
 * @s1: opcode
 * @s2: command
 * Return: 1 if match, 0 if not
 **/
int its_a_match(char *s1, char *s2)
{
	int i;

	for (i = 0; s1[i]; i++)
		if (s1[i] != s2[i])
			return (0);

	if (s2[i] != '\n' && s2[i] != ' ' && s2[i] != '\0')
		return (0);

	return (1);
}
