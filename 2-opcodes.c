#include "monty.h"

/**
 * pall - prints all elements on the stack
 * @h: head pointer
 * @l: line number of file being interpreted
 * Return: void
 **/
void pall(stack_t **h, unsigned int l)
{
	stack_t *tmp;

	(void)l;

	for (tmp = *h; tmp; tmp = tmp->next)
		printf("%d\n", tmp->n);
}

/**
 * pint - prints next element as an int
 * @h: pointer to stack
 * @l: line number
 * Return: void
 **/
void pint(stack_t **h, unsigned int l)
{
	if (*h == NULL)
		GTFO(h, l, "can't pint, stack empty", NULL);

	printf("%d\n", (*h)->n);
}

/**
 * pop - remove next element of list
 * @h: pointer to stack
 * @l: line number
 * Return: void
 **/
void pop(stack_t **h, unsigned int l)
{
	if (*h == NULL)
		GTFO(h, l, "can't pop an empty stack", NULL);

	if ((*h)->next)
	{
		*h = (*h)->next;
		free((*h)->prev);
		(*h)->prev = NULL;
	}
	else
	{
		free(*h);
		*h = NULL;
	}
}
/**
 * swap - swap the first and second elements
 * @h: pointer to stack
 * @l: line number
 * Return: void
 **/
void swap(stack_t **h, unsigned int l)
{
	int tmp;

	if (*h == NULL || (*h)->next == NULL)
		GTFO(h, l, "can't swap, stack too short", NULL);

	tmp = (*h)->n;
	(*h)->n = (*h)->next->n;
	(*h)->next->n = tmp;
}

/**
 * nop - do nothing
 * @h: pointer to stack
 * @l: line number
 * Return: void
 **/
void nop(stack_t **h, unsigned int l)
{
	(void)h;
	(void)l;
}
