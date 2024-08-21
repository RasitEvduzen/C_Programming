#include <stdio.h>
#include <stdlib.h>
#include "SingleLinkList.h"


/* Static Functions Prototypes */
static bool disp(DATATYPE *val);

/* Function Definitions */
HLINKLIST create_link_list(void)
{
    HLINKLIST hlinklist;
    if((hlinklist = (HLINKLIST)malloc(sizeof(HLINKLIST))) == NULL)
        return NULL;
    hlinklist->head = hlinklist->tail = NULL;
    hlinklist->count = 0;
    return hlinklist;
}


NODE *addp_tail(HLINKLIST hlinklist,const DATATYPE *val)
{
       NODE *new_node;
    if((new_node = (NODE *)malloc(sizeof(NODE))) == NULL)
       return NULL;
    new_node->val = *val;
    if(hlinklist->tail != NULL)
        hlinklist->tail->next = new_node;
    else
        hlinklist->head = new_node;
    hlinklist->tail = new_node;
    new_node->next = NULL;    
    ++hlinklist->count;
    return new_node;
}


NODE *addp_head(HLINKLIST hlinklist,const DATATYPE *val)
{
    NODE *new_node;
    if((new_node = (NODE *)malloc(sizeof(NODE))) == NULL)
       return NULL;
    new_node->val = *val;
    new_node->next = hlinklist->head;
    if(hlinklist->head == NULL)
        hlinklist->tail = new_node;
    hlinklist->head = new_node;
    ++hlinklist->count;
    return new_node;
}


NODE *insertp_next(HLINKLIST hlinklist,NODE *node, const DATATYPE *val)
{
       NODE *new_node;
    if((new_node = (NODE *)malloc(sizeof(NODE))) == NULL)
       return NULL;
    new_node->val = *val;
    if(node == hlinklist->tail)
        hlinklist->tail = new_node;
    new_node->next = node->next;
    node->next = new_node;
    ++hlinklist->count;
    return new_node;
}


void remove_next(HLINKLIST hlinklist,NODE *node)
{
    NODE *next_node;
    if(node == hlinklist->tail)
        return;
    if(node->next == hlinklist->tail)
        hlinklist->tail = node;
    next_node = node->next;
    node->next = next_node->next;
    --hlinklist->count;
    free(next_node);
}

DATATYPE *getp_item(HLINKLIST hlinklist,size_t idx)
{
    NODE *node;
    if(idx >= hlinklist->count)
        return NULL;
    node = hlinklist->head;
    for(size_t i = 0; i < idx ; ++i)
        node = node->next;
    return &node->val;
}


void clear_link_list(HLINKLIST hlinklist)
{
    NODE *node,*temp_node;
    node = hlinklist->head;
    while (!node){
        temp_node = node->next;
        free(node);
        node = temp_node;
    }
    hlinklist->head = hlinklist->tail = NULL;  
    hlinklist->count = 0; 
}

bool destroy_link_list(HLINKLIST hlinklist)
{
    clear_link_list(hlinklist);
    free(hlinklist);
    return true;
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

void clear_buffer(void)
{
	int ch;
	while ((ch = getchar()) != '\n' && ch != EOF)
	;	
}

static bool disp(DATATYPE *val)
{
    printf("%s : %d \n", val->name, val->no);
    clear_buffer();
    return true;
}
