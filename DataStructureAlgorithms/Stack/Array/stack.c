#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#include <stdbool.h>
#include "stack.h"


HSTACK create_stack(size_t size)
{
    HSTACK hstack;

    if((hstack = (HSTACK)malloc(sizeof(STACK))) == NULL)
        return NULL;
    
    if((hstack->stack = (DATATYPE *)malloc(sizeof(DATATYPE)*size)) == NULL){
        free(hstack);
        return NULL;
    }

    hstack->sp = hstack->stack + size; // Set Stack Pointer 
    hstack->size = size;
    hstack->count = 0;
    return hstack;
}

bool push_stack(HSTACK hstack,DATATYPE val)
{
    if(hstack->sp == hstack->stack)
        return false;
    *--hstack->sp = val;
    ++hstack->count;
    return true;
}

bool pushp_stack(HSTACK hstack,DATATYPE *val)
{
    if(hstack->sp == hstack->stack)
        return false;
    *--hstack->sp = *val;
    ++hstack->count;
    return true;
}

bool pop_stack(HSTACK hstack,DATATYPE *val)
{
    if(!hstack->count)
        return false;
    *val = *hstack->sp++;
    --hstack->count;
    return true;
}

void clear_stack(HSTACK hstack)
{
    hstack->sp = hstack->stack + hstack->size;
    hstack->count = 0;
}

void destroy_stack(HSTACK hstack)
{
    free(hstack->stack);
    free(hstack);
}

void disp_stack(HSTACK hstack)
{
    for(size_t i = 0; i < hstack->count; ++i){
        printf("%d ",*hstack->sp++);
    }
    putchar('\n');
}

void clear_buffer(void)
{
    int ch;
    while ((ch = getchar()) != '\n' && ch != EOF)
        ;    
}