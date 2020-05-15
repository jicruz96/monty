#include "monty.h"

/**
 * add_op - adds first and second elements
 * @h: pointer to stack
 * @l: line number
 * Return: void
 **/
void add_op(stack_t **h, unsigned int l)
{
	if (*h == NULL || (*h)->next == NULL)
		GTFO(h, l, "can't add, stack too short", NULL);
	(*h)->next->n += (*h)->n;
	pop(h, l);
}

/**
 * div_op - divides second element by the first
 * @h: pointer to stack
 * @l: line number
 * Return: void
 **/
void div_op(stack_t **h, unsigned int l)
{
	if (*h == NULL || (*h)->next == NULL)
		GTFO(h, l, "can't div, stack too short", NULL);
	if ((*h)->n == 0)
		GTFO(h, l, "division by zero", NULL);
	(*h)->next->n /= (*h)->n;
	pop(h, l);
}

/**
 * mul - multiplies first and second elements
 * @h: pointer to stack
 * @l: line number
 * Return: void
 **/
void mul(stack_t **h, unsigned int l)
{
	if (*h == NULL || (*h)->next == NULL)
		GTFO(h, l, "can't mul, stack too short", NULL);
	(*h)->next->n *= (*h)->n;
	pop(h, l);
}

/**
 * sub - subtract first element from the second
 * @h: pointer to stack
 * @l: line number
 * Return: void
 **/
void sub(stack_t **h, unsigned int l)
{
	if (*h == NULL || (*h)->next == NULL)
		GTFO(h, l, "can't sub, stack too short", NULL);
	(*h)->next->n -= (*h)->n;
	pop(h, l);
}

/**
 * mod - make second element remainder of 2nd / 1st
 * @h: pointer to stack
 * @l: line number
 * Return: void
 **/
void mod(stack_t **h, unsigned int l)
{
	if (*h == NULL || (*h)->next == NULL)
		GTFO(h, l, "can't mod, stack too short", NULL);
	(*h)->next->n %= (*h)->n;
	pop(h, l);
}
