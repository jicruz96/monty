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
		GTFO(h, 0, "Error: malloc failed", NULL);

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
		GTFO(h, 0, "Error: malloc failed", NULL);

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
 * GTFO - prints error message and exits
 * @h: pointer to linked list
 * @l: current line number
 * @s: error message
 * @s2: error message supplement
 * Return: void
 **/
void GTFO(stack_t **h, unsigned int l, char *s, char **s2)
{
	if (file)
		fclose(file);
	if (h)
		free_list(*h);
	if (l)
		dprintf(STDERR_FILENO, "L%u: ", l);
	if (s)
		dprintf(STDERR_FILENO, "%s", s);
	if (s2)
	{
		dprintf(STDERR_FILENO, " %s", *s2);
		free(*s2);
	}
	dprintf(STDERR_FILENO, "\n");

	exit(EXIT_FAILURE);
}

/**
 * gtfo - wrapper for simple version of GTFO
 * @s: error message snippet
 * Return: void
 **/
void gtfo(char *s)
{
	GTFO(NULL, 0, s, NULL);
}

/**
 * free_list - frees list
 * @h: h pointer to list
 * Return: void
 */
void free_list(stack_t *h)
{
	while (h && h->next != NULL)
	{
		h = h->next;
		free(h->prev);
	}
	free(h);
}
