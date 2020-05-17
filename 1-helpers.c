#include "monty.h"

/**
 * add_top - adds an element to top of stack
 * @h: pointer to head of stack
 * @n: element to add
 * Return: void
 **/
void add_top(stack_t **h, unsigned int n)
{
	stack_t *new = malloc(sizeof(stack_t));

	if (new == NULL)
		GTFO("Error: malloc failed", 0);

	new->n = (int)n;
	new->next = NULL;
	new->prev = NULL;

	if (*h != NULL)
		(*h)->prev = new;
	new->next = *h;
	*h = new;
}

/**
 * add_bottom - adds an element to bottom of stack
 * @h: pointer to head of stack
 * @n: element to add
 * Return: void
 **/
void add_bottom(stack_t **h, unsigned int n)
{
	stack_t *new = malloc(sizeof(stack_t)), *tmp;

	if (new == NULL)
		GTFO("Error: malloc failed", 0);

	new->n = (int)n;
	new->next = NULL;
	new->prev = NULL;

	for (tmp = *h; tmp && tmp->next; tmp = tmp->next)
		;

	if (tmp)
	{
		tmp->next = new;
		new->prev = tmp;
	}
	else
		*h = new;
}

/**
 * cleanup - free all malloc'd pointers
 * Return: void
 **/
void cleanup(void)
{
	while (g.head && g.head->next != NULL)
	{
		g.head = g.head->next;
		free(g.head->prev);
	}
	free(g.head);
	free(g.buf);
	if (g.file)
		fclose(g.file);
}

/**
 * GTFO - prints error message and exits
 * @line_no: current line number
 * @s: error message
 * Return: void
 **/
void GTFO(char *s, unsigned int line_no)
{
	if (line_no)
		dprintf(STDERR_FILENO, "L%u: ", line_no);
	dprintf(STDERR_FILENO, "%s\n", s);
	cleanup();
	exit(EXIT_FAILURE);
}

/**
 * not_number - checks if string is a number
 * @s: string
 * Return: true if number | false if not
 **/
bool not_number(const char *s)
{
	if (s == NULL)
		return (true);

	if (*s == '-')
		s++;

	if (*s == '\0')
		return (true);

	for (; *s; s++)
		if (*s < '0' || *s > '9')
			return (true);

	return (false);
}
