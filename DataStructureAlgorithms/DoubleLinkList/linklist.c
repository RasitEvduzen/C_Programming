#include <stdio.h>
#include <stdlib.h>
#include "linklist.h"


/* Static Functions Prototypes */
static bool disp(DATATYPE *val);

/* Function Definitions */
HLINKLIST create_link_list(void)
{
    HLINKLIST hlinklist;
    if((hlinklist = (HLINKLIST)malloc(sizeof(LINKLIST))) == NULL)
        return NULL;

    hlinklist->head = hlinklist->tail = NULL;  // Init Null Pointer
    hlinklist->count = 0;
    return hlinklist;
}


NODE *add_tail(HLINKLIST hlinklist,DATATYPE val)
{
    NODE *new_node;
    if((new_node = (NODE *)malloc(sizeof(NODE))) == NULL)
        return NULL;
    if(hlinklist->head != NULL)  // is List is empty?
        hlinklist->tail->next = new_node;
    else
        hlinklist->head = new_node;
    new_node->prev = hlinklist->tail;
    new_node->next = NULL;
    new_node->val = val;
    hlinklist->tail = new_node;

    ++hlinklist->count;
    return new_node;
}

NODE *addp_tail(HLINKLIST hlinklist,const DATATYPE *val)
{
    NODE *new_node;
    if((new_node = (NODE *)malloc(sizeof(NODE))) == NULL)
        return NULL;
    if(hlinklist->head != NULL)  // is List is empty?
        hlinklist->tail->next = new_node;
    else
        hlinklist->head = new_node;
    new_node->prev = hlinklist->tail;
    new_node->next = NULL;
    new_node->val = *val;
    hlinklist->tail = new_node;

    ++hlinklist->count;
    return new_node;
}

NODE *add_head(HLINKLIST hlinklist,DATATYPE val)
{
    NODE *new_node;
    if((new_node = (NODE *)malloc(sizeof(NODE))) == NULL)
        return NULL;
    if(hlinklist->head == NULL)  // is List is empty?
        hlinklist->tail = new_node;
    else
        hlinklist->head->prev = new_node;

    new_node->prev = NULL;
    new_node->next = hlinklist->head;
    new_node->val = val;
    hlinklist->head = new_node;

    ++hlinklist->count;
    return new_node;
}


NODE *addp_head(HLINKLIST hlinklist,const DATATYPE *val)
{
    NODE *new_node;
    if((new_node = (NODE *)malloc(sizeof(NODE))) == NULL)
        return NULL;
    if(hlinklist->head == NULL)  // is List is empty?
        hlinklist->tail = new_node;
    else
        hlinklist->head->prev = new_node;

    new_node->prev = NULL;
    new_node->next = hlinklist->head;
    new_node->val = *val;
    hlinklist->head = new_node;

    ++hlinklist->count;
    return new_node;
}

NODE *insert_next(HLINKLIST hlinklist,NODE *node, DATATYPE val)
{
    NODE *new_node;
    if((new_node = (NODE *)malloc(sizeof(NODE))) == NULL)
        return NULL;
    new_node->val = val;
    if(node != hlinklist->tail)
        node->next->prev = new_node;
    else
        hlinklist->tail = new_node;
        
    new_node->next = node->next;
    node->next = new_node;
    new_node->prev = node;

    ++hlinklist->count;    
    return new_node;
}

NODE *insertp_next(HLINKLIST hlinklist,NODE *node, const DATATYPE *val)
{
    NODE *new_node;
    if((new_node = (NODE *)malloc(sizeof(NODE))) == NULL)
        return NULL;
    new_node->val = *val;
    if(node != hlinklist->tail)
        node->next->prev = new_node;
    else
        hlinklist->tail = new_node;
        
    new_node->next = node->next;
    node->next = new_node;
    new_node->prev = node;

    ++hlinklist->count;    
    return new_node;
}

NODE *insert_prev(HLINKLIST hlinklist,NODE *node, DATATYPE val)
{
    NODE *new_node;
    if((new_node = (NODE *)malloc(sizeof(NODE))) == NULL)
        return NULL;
    new_node->val = val;
    if(node != hlinklist->head)
        node->prev->next = new_node;
    else
        hlinklist->head=new_node;
    new_node->next = node;
    new_node->prev = node->prev;
    node->prev = new_node;

    ++hlinklist->count;    
    return new_node;
}

NODE *insertp_prev(HLINKLIST hlinklist,NODE *node, const DATATYPE *val)
{
    NODE *new_node;
    if((new_node = (NODE *)malloc(sizeof(NODE))) == NULL)
        return NULL;
    new_node->val = *val;
    if(node != hlinklist->head)
        node->prev->next = new_node;
    else
        hlinklist->head=new_node;
    new_node->next = node;
    new_node->prev = node->prev;
    node->prev = new_node;

    ++hlinklist->count;    
    return new_node;
}

void remove_node(HLINKLIST hlinklist,NODE *node)
{
    if(node == hlinklist->head)
        hlinklist->head = node->next;
    else
        node->prev->next = node->next;

    if(node == hlinklist->tail)
        hlinklist->tail = node->prev;
    else
        node->next->prev = node->prev;
    
    --hlinklist->count;
    free(node);
}

DATATYPE *getp_item(HLINKLIST hlinklist,size_t idx)
{
    NODE *node = hlinklist->head;
    if(idx >= hlinklist->count)
        return NULL;    
    for (size_t i = 0; i < idx; ++i)
        node = node->next;
    return &node->val;
}

void clear_link_list(HLINKLIST hlinklist)
{
    NODE *temp_node, *node;
    node = hlinklist->head;
    
    while (node != NULL)
    {
        temp_node = node->next;
        free(node);
        node = temp_node;
    }
    hlinklist->head = hlinklist->tail = NULL;
    hlinklist->count = 0;
}

void destroy_link_list(HLINKLIST hlinklist)
{
    clear_link_list(hlinklist);
    free(hlinklist);
}

bool walk_link_list(HLINKLIST hlinklist, bool(*proc)(DATATYPE *))
{
    if(proc == NULL)
        proc = &disp;
    for (NODE *node = hlinklist->head; node != NULL; node = node->next)
        if(!proc(&node->val))
            return false;
    putchar('\n');
    return true;
}

bool walk_link_list_rev(HLINKLIST hlinklist, bool(*proc)(DATATYPE *))
{
    if(proc == NULL)
        proc = &disp;
    for (NODE *node = hlinklist->tail; node != NULL; node = node->prev)
        if(!proc(&node->val))
            return false;
    putchar('\n');
    return true;
}

static bool disp(DATATYPE *val)
{
    printf("%d ", *val);
    fflush(stdout);
    return true;
}
