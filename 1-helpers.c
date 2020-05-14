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

	new->n = n;
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
 * exitor - prints error message and exits
 * @h: pointer to linked list
 * @l: current line number
 * @s: error message
 * Return: void
 **/
void exitor(stack_t **h, unsigned int l, char *s)
{
	if (l)
		dprintf(STDERR_FILENO, "L%u: %s\n", l, s);
	fclose(file);
	free_list(*h);
	exit(EXIT_FAILURE);
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
