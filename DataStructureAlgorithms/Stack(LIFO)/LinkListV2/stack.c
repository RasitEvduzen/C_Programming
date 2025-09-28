#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#include <stdbool.h>
#include "stack.h"


HSTACK create_stack(void)
{
    HSTACK hstack;

    if((hstack = (HSTACK)malloc(sizeof(STACK))) == NULL)
        return NULL;
    hstack->head = NULL;
    hstack->count = 0;
    return hstack;
}

bool push_stack(HSTACK hstack,DATATYPE val)
{
    NODE *new_node;
    if((new_node = (NODE *)malloc(sizeof(NODE))) == NULL)
        return false;
    new_node->val = val;
    new_node->next = hstack->head;
    hstack->head = new_node;
    ++hstack->count;
    return true;
}

bool pushp_stack(HSTACK hstack,DATATYPE *val)
{
    NODE *new_node;
    if((new_node = (NODE *)malloc(sizeof(NODE))) == NULL)
        return false;
    new_node->val = *val;
    new_node->next = hstack->head;
    hstack->head = new_node;
    ++hstack->count;
    return true;
}

bool pop_stack(HSTACK hstack,DATATYPE *val)
{
    NODE *node;
    if(!hstack->head)
        return false;
    node = hstack->head;
    hstack->head = node->next;
    *val = node->val;
    free(node);
    --hstack->count;
    return true;
}

void clear_stack(HSTACK hstack)
{
    NODE *node, *temp_node;
    node = hstack->head;
    while (node){
        temp_node = node->next;
        free(node);
        node = temp_node;
    }
    hstack->head = NULL;
    hstack->count = 0;
}

void destroy_stack(HSTACK hstack)
{
    clear_stack(hstack);
    free(hstack);
}

bool disp_stack(HSTACK hstack)
{
    NODE *node, *temp_node;
    node = hstack->head;
    if(!hstack->count)
        return false;
    while (node){
        temp_node = node->next;
        printf("%d ",node->val);
        node = temp_node;
    }
    putchar('\n');
    return true;
}

void clear_buffer(void)
{
    int ch;
    while ((ch = getchar()) != '\n' && ch != EOF)
        ;    
}