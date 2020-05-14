#include "monty.h"

/**
 * rotl - rotates the list left (puts top stack at bottom)
 * @h: pointer to stackk
 * @l: line number
 * Return: void
 **/
void rotl(stack_t **h, unsigned int l)
{
	if (*h)
	{
		add_bottom(h, (*h)->n);
		pop(h, l);
	}
}

/**
 * rotr - rotates the list right (puts bottom stack on top)
 * @h: pointer to stackk
 * @l: line number
 * Return: void
 **/
void rotr(stack_t **h, unsigned int l)
{
	stack_t *tmp = *h;

	(void)l;

	while (tmp && tmp->next)
		tmp = tmp->next;

	if (tmp && tmp->prev)
	{
		add_top(h, tmp->n);
		tmp->prev = NULL;
		free(tmp);
	}
}

/**
 * pstr - treats stack as a string
 * @h: pointer to stack
 * @l: line number
 * Return: void
 **/
void pstr(stack_t **h, unsigned int l)
{
	if (*h && (*h)->n > 0 && (*h)->n < 256)
	{
		printf("%c\n", (*h)->n);
		pstr(&((*h)->next), l);
	}
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
		exitor(h, l, "can't pchar, stack empty");

	if ((*h)->n > 255 || (*h)->n < 0)
		exitor(h, l, "can't pchar, value out of range");

	printf("%c\n", (*h)->n);
}
