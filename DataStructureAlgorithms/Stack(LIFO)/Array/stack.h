#ifndef STACK_H_
#define STACK_H_

#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#include <stdbool.h>

typedef int DATATYPE;

typedef struct tagSTACK{
    DATATYPE *stack;
    DATATYPE *sp;
    size_t count;
    size_t size;
}STACK, *HSTACK;

/* Function Decleration */
HSTACK create_stack(size_t size);
bool push_stack(HSTACK hstack,DATATYPE val);
bool pushp_stack(HSTACK hstack,DATATYPE *val);
bool pop_stack(HSTACK hstack,DATATYPE *val);
void clear_stack(HSTACK hstack);
void destroy_stack(HSTACK hstack);
bool disp_stack(HSTACK hstack);
void clear_buffer(void);
/* Inline Function Definition */

static inline bool isempty_stack(HSTACK hstack)
{
    return hstack->count == 0;
}

static inline size_t count_stack(HSTACK hstack)
{
	return hstack->count;
}

#endif // STACK_H_