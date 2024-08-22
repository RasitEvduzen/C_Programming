#ifndef STACK_H
#define STACK_H


#include <stddef.h>
#include <stdbool.h>


typedef int DATATYPE;

typedef struct tagNODE
{
    DATATYPE val;
    struct  tagNODE* next;
}NODE;


typedef struct tagSTACK
{
    NODE* head;
    NODE* tail;
    size_t count;
}STACK, * HSTACK;


HSTACK stack_create(void);
bool stack_push(HSTACK, DATATYPE);
bool stack_pop(HSTACK);
DATATYPE stack_peep(HSTACK);
size_t stack_size(HSTACK);
size_t stack_length(HSTACK);
void stack_display(HSTACK);
void stack_clear(HSTACK);
void stack_destroy(HSTACK);




#endif //STACK_H
