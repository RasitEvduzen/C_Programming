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
    hlinklist->head.next = &hlinklist->head;
    hlinklist->tail = &hlinklist->head;
    hlinklist->count = 0;
    return hlinklist;
}

NODE *insert_next(HLINKLIST hlinklist,NODE *node, DATATYPE val)
{
    NODE *new_node;
    if((new_node = (NODE *)malloc(sizeof(NODE))) == NULL)
       return NULL;
    new_node->val = val;
    if(node == hlinklist->tail)
        hlinklist->tail = new_node;
    new_node->next = node->next;
    node->next = new_node;
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

NODE *add_tail(HLINKLIST hlinklist,DATATYPE val)
{
    return insert_next(hlinklist,hlinklist->tail,val);

}

NODE *addp_tail(HLINKLIST hlinklist,const DATATYPE *val)
{
    return insertp_next(hlinklist,hlinklist->tail,val);
}

NODE *add_head(HLINKLIST hlinklist,DATATYPE val)
{
    return insert_next(hlinklist,&hlinklist->head,val);
}


NODE *addp_head(HLINKLIST hlinklist,const DATATYPE *val)
{
    return insertp_next(hlinklist,&hlinklist->head,val);
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

void remove_head(HLINKLIST hlinklist)
{
    remove_next(hlinklist,&hlinklist->head);
}

DATATYPE *getp_item(HLINKLIST hlinklist,size_t idx)
{
    NODE *node;
    if(idx >= hlinklist->count)
        return NULL;
    node = hlinklist->head.next;
    for(size_t i = 0; i < idx ; ++i)
        node = node->next;
    return &node->val;
}


void clear_link_list(HLINKLIST hlinklist)
{
    NODE *node,*temp_node;
    node = hlinklist->head.next;
    while (node != &hlinklist->head){
        temp_node = node->next;
        free(node);
        node = temp_node;
    }
    hlinklist->head.next = &hlinklist->head;
    hlinklist->tail = &hlinklist->head;
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
    for (NODE *node = hlinklist->head.next; node != &hlinklist->head; node = node->next)
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
    printf("%d ", *val);
    clear_buffer();
    return true;
}
