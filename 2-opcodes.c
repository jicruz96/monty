#include "monty.h"

/**
 * pall - prints all elements on the stack
 * @h: head pointer
 * @l: line number of file being interpreted
 * Return: void
 **/
void pall(stack_t **h, unsigned int l)
{
	if (*h)
	{
		pint(h, l);
		pall(&((*h)->next), l);
	}
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
		GTFO("can't pint, stack empty", l);

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
		GTFO("can't pop an empty stack", l);

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
		GTFO("can't swap, stack too short", l);

	tmp = (*h)->n;
	(*h)->n = (*h)->next->n;
	(*h)->next->n = tmp;
}

/**
 * pchar - prints next element as a char
 * @h: pointer to stack
 * @l: line number
 * Return: void
 **/
void pchar(stack_t **h, unsigned int l)
{
	if (*h == NULL)
		GTFO("can't pchar, stack empty", l);

	if ((*h)->n > 127 || (*h)->n < 0)
		GTFO("can't pchar, value out of range", l);

	printf("%c\n", (*h)->n);
}
