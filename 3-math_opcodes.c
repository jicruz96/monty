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
		GTFO("can't add, stack too short", l);
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
		GTFO("can't div, stack too short", l);
	if ((*h)->n == 0)
		GTFO("division by zero", l);
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
		GTFO("can't mul, stack too short", l);
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
		GTFO("can't sub, stack too short", l);
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
		GTFO("can't mod, stack too short", l);
	if ((*h)->n == 0)
		GTFO("division by zero", l);
	(*h)->next->n %= (*h)->n;
	pop(h, l);
}
