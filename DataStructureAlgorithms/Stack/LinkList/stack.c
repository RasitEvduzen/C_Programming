#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "stack.h"


HSTACK stack_create(void)
{
	HSTACK hstack;

	if ((hstack = (HSTACK)malloc(sizeof(STACK))) == NULL)
		return NULL;

	hstack->count = 0;
	hstack->head = NULL;
	hstack->tail = NULL;

	return hstack;
}

bool stack_push(HSTACK hstack, DATATYPE val)
{
	NODE* new_node;
	if ((new_node = (NODE*)malloc(sizeof(NODE))) == NULL)
		return false;

	new_node->val = val;
	new_node->next = hstack->head;

	if (hstack->head == NULL)
		hstack->tail = new_node;

	hstack->head = new_node;
	++hstack->count;


	return true;
}

bool stack_pop(HSTACK hstack)
{
	NODE* temp_node;
	if (hstack->head == NULL)
		return false;

	temp_node = hstack->head;
	hstack->head = hstack->head->next;
	--hstack->count;
	free(temp_node);

	return true;

}
DATATYPE stack_peep(HSTACK hstack)
{
	if (hstack->head == NULL)
		exit(EXIT_FAILURE);

	return hstack->head->val;

}

size_t stack_size(HSTACK hstack)
{
	return hstack->count * sizeof(NODE);

}

size_t stack_length(HSTACK hstack)
{
	return hstack->count;

}

void stack_display(HSTACK hstack)
{
	NODE* current_node = hstack->head;
	DATATYPE order = hstack->count;
	
	while (current_node)
	{
		printf("%5d.  -  %5d\n", order--, current_node->val);
		current_node = current_node->next;
	}
}


void stack_clear(HSTACK hstack)
{
	NODE* temp_node;

	while (hstack->head)
	{
		temp_node = hstack->head;
		hstack->head = hstack->head->next;
		--hstack->count;
		free(temp_node);
	}
}

void stack_destroy(HSTACK hstack)
{
	stack_clear(hstack);
	free(hstack);
	hstack = NULL;
}