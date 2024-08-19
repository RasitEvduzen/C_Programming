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

    hlinklist->head.next = &hlinklist->head;
    hlinklist->head.prev = &hlinklist->head;
    hlinklist->count = 0;
    return hlinklist;
}

NODE *insert_next(HLINKLIST hlinklist,NODE *node, DATATYPE val)
{
    NODE *new_node;
    if((new_node = (NODE *)malloc(sizeof(NODE))) == NULL)
        return NULL;
    new_node->val = val;

    node->next->prev = new_node;        
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
    node->next->prev = new_node;        
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
    node->prev->next = new_node;
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
    node->prev->next = new_node;
    new_node->next = node;
    new_node->prev = node->prev;
    node->prev = new_node;

    ++hlinklist->count;    
    return new_node;
}


NODE *add_tail(HLINKLIST hlinklist,DATATYPE val)
{
    return insert_prev(hlinklist,&hlinklist->head,val);
}

NODE *addp_tail(HLINKLIST hlinklist,const DATATYPE *val)
{
    return insertp_prev(hlinklist,&hlinklist->head,val);
}

NODE *add_head(HLINKLIST hlinklist,DATATYPE val)
{
    return insert_next(hlinklist,&hlinklist->head,val);
}

NODE *addp_head(HLINKLIST hlinklist,const DATATYPE *val)
{
    return insertp_next(hlinklist,&hlinklist->head,val);
}
void remove_node(HLINKLIST hlinklist,NODE *node)
{
    node->prev->next = node->next;
    node->next->prev = node->prev;
    --hlinklist->count;
    free(node);
}

DATATYPE *getp_item(HLINKLIST hlinklist,size_t idx)
{
    NODE *node = hlinklist->head.next;
    if(idx >= hlinklist->count)
        return NULL;    
    for (size_t i = 0; i < idx; ++i)
        node = node->next;
    return &node->val; 
}


void clear_link_list(HLINKLIST hlinklist)
{
    NODE *temp_node, *node;
    node = hlinklist->head.next;
    
    while (node != &hlinklist->head)
    {
        temp_node = node->next;
        free(node);
        node = temp_node;
    }
    hlinklist->head.next = &hlinklist->head;
    hlinklist->head.prev = &hlinklist->head;
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
    for (NODE *node = hlinklist->head.next; node != &hlinklist->head; node = node->next)
        if(!proc(&node->val))
            return false;
    putchar('\n');
    return true;
}

bool walk_link_list_rev(HLINKLIST hlinklist, bool(*proc)(DATATYPE *))
{
    if(proc == NULL)
        proc = &disp;
    for (NODE *node = hlinklist->head.prev; node != &hlinklist->head; node = node->prev)
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
