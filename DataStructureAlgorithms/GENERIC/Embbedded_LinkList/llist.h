#ifndef LLIST_H_
#define LLIST_H_

#include <stdio.h>
#include <stdlib.h>
#include <stdlib.h> 

/* Macro Definitions */

#define offset_of(type,member)                (size_t)&(((type*)0)->member)
#define container_of(ptr,type,member)         (type*)((char*)ptr - offset_of(type,member))
#define FOR_EACH(hllist, node)		for (node = (hllist)->head.next; node != &(hllist)->head; node = node->next)
#define FOR_EACH_REV(hllist, node)	for (node = (hllist)->head.prev; node != &(hllist)->head; node = node->prev)
#define FREE_LLIST(hllist, node)	for (NODE *tnode = (hllist)->head.next;  node = tnode, tnode = tnode->next, node != &(hllist)->head; )

/* Type Declarations */
typedef struct tagNODE{
    struct tagNODE *next;
    struct tagNODE *prev;
}NODE;

typedef struct tagLLIST{
    NODE head;
    size_t count;
}LLIST, *HLLIST;

/* Function Declerations | Prototypes */
HLLIST create_llist(void);
NODE* insert_next(HLLIST hllist, NODE* node, NODE* new_node);
NODE* insert_prev(HLLIST hllist, NODE* node, NODE* new_node);
NODE* remove_node(HLLIST hllist, NODE* node);
NODE* add_tail(HLLIST hllist, NODE *new_node);
NODE* add_head(HLLIST hllist, NODE *new_node);
NODE* getp_item(HLLIST hllist, size_t index);
bool walk_llist(HLLIST hllist, bool (*proc)(NODE *));
bool walk_llist_rev(HLLIST hllist, bool (*proc)(NODE *));
void clear_llist(HLLIST hllist);
void destroy_llist(HLLIST hllist);

/* Inline Functions Definitions */
static inline size_t count_llist(HLLIST hllist){
    return hllist ? hllist->count : 0;
}

static inline NODE* head_llist(HLLIST hllist){
    return hllist ? hllist->head.next : NULL;
}

static inline NODE* tail_llist(HLLIST hllist){
    return hllist ? hllist->head.prev : NULL;
}



#endif //LLIST_H_
