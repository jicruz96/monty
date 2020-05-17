#include "monty.h"

global_t g = {NULL, NULL, NULL, 1};

/**
 * main - interprets monty bytecode
 * @ac: argument count
 * @av: argument vector
 * Return: Always 0
 **/
int main(int ac, char *av[])
{
	unsigned int line_no = 1, n;
	size_t size = 0;
	op f = NULL;

	if (ac != 2)
		GTFO("USAGE: monty file", 0);

	if (access(av[1], R_OK) == -1)
	{
		dprintf(2, "Error: Can't open file %s\n", av[1]);
		exit(EXIT_FAILURE);
	}

	g.file = fopen(av[1], "r");
	/*if (g.file == NULL)
		GTFO("Error: malloc failed", 0);*/

	for (; 1; line_no++)
	{
		if (getline(&g.buf, &size, g.file) == -1)
			break;

		f = get_op(strtok(g.buf, " \t\n"));
		if (f != NULL)
		{
			n = get_num(f, line_no, strtok(NULL, " \t\n"));
			f(&g.head, n);
		}
	}
	cleanup();
	return (0);
}

/**
 * get_op - matches a string with an op function
 * @opcode: string to match with an op func
 * Return: matched op function | NULL if no match
 **/
op get_op(char *opcode)
{
	instruction_t *p, ops[] = {{"push", add_top}, {"pall", pall}, {"pint", pint}, {"pop", pop}, {"swap", swap}, {"add", add_op}, {"sub", sub}, {"div", div_op}, {"mul", mul}, {"mod", mod}, {"pchar", pchar}, {"pstr", pstr}, {"rotl", rotl}, {"rotr", rotr}, {"stack", stack}, {"queue", queue}, {"nop", NULL}, {NULL, NULL}};

	if (opcode == NULL || *opcode == '#')
		return (NULL);

	if (g.mode == 0)
		ops[0].f = add_bottom;

	for (p = ops; p->opcode; p++)
		if (strcmp(p->opcode, (const char *)opcode) == 0)
			return (p->f);

	dprintf(2, "unknown instruction %s\n", opcode);
	cleanup();
	exit(EXIT_FAILURE);
}

/**
 * get_num - converts a string to an integer or exits if error found
 * @f: opcode function
 * @line_no: line_no of command. used for exit error message
 * @a: string to convert to integer if f is a push function
 * Return: found integer, as integer data type | exits if error found
 */
unsigned int get_num(op f, unsigned int line_no, char *a)
{
	int i = 0, sign = 1;

	if (f != add_bottom && f != add_top)
		return (line_no);

	for (; a && *a; a++)
	{
		if (*a == '-')
		{
			sign *= -1;
			continue;
		}

		while (isdigit(*a))
			i = (i * 10) + (*a++ - '0') * sign;

		if (*a)
			break;

		return ((unsigned int)i);
	}

	GTFO("usage: push integer", line_no);
	return (0);
}
