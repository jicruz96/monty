#ifndef MONTY_H
#define MONTY_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdbool.h>
#include <ctype.h>

/**
 * struct stack_s - doubly linked list representation of a stack (or queue)
 * @n: integer
 * @prev: points to the previous element of the stack (or queue)
 * @next: points to the next element of the stack (or queue)
 *
 * Description: doubly linked list node structure
 * for stack, queues, LIFO, FIFO Holberton project
 */
typedef struct stack_s
{
	int n;
	struct stack_s *prev;
	struct stack_s *next;
} stack_t;

/**
 * struct global_s - struct of global variables
 * @file: pointer to file
 * @head: pointer to linked list
 * @buf: pointer to command buffer
 * @mode: 0 = stack mode | 1 = queue mode
 *
 * Description: pointer variables are global so
 *				GTFO can free them at exit. mode
 *				sets behavior of stack.
 **/
typedef struct global_s
{
	FILE *file;
	stack_t *head;
	char *buf;
	int mode;
} global_t;

/**
 * struct instruction_s - opcode and its function
 * @opcode: the opcode
 * @f: function to handle the opcode
 *
 * Description: opcode and its function
 * for stack, queues, LIFO, FIFO Holberton project
 */
typedef struct instruction_s
{
	char *opcode;
	void (*f)(stack_t **stack, unsigned int line_number);
} instruction_t;

extern global_t g;

typedef void (*op)(stack_t **, unsigned int);

op get_op(char *, unsigned int);

void pall(stack_t **, unsigned int);
void pint(stack_t **, unsigned int);
void add_op(stack_t **, unsigned int);
void div_op(stack_t **, unsigned int);
void mul(stack_t **, unsigned int);
void mod(stack_t **, unsigned int);
void queue(stack_t **, unsigned int);
void stack(stack_t **, unsigned int);
void pop(stack_t **, unsigned int);
void swap(stack_t **, unsigned int);
void sub(stack_t **, unsigned int);
void pchar(stack_t **, unsigned int);
void rotl(stack_t **, unsigned int);
void rotr(stack_t **, unsigned int);
void pstr(stack_t **, unsigned int);
void error(stack_t **, unsigned int);
void add_top(stack_t **, unsigned int);
void add_bottom(stack_t **, unsigned int);
void GTFO(char *, unsigned int);
unsigned int get_num(op, unsigned int, char *);
void cleanup(void);

#endif /* MONTY_H */
