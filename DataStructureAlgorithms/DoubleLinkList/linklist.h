#ifndef LINKLIST_H
#define LINKLIST_H

#include <stddef.h>
#include <stdbool.h>

/* Type Declerations */

typedef int DATATYPE;

typedef struct tagNODE
{
    DATATYPE val;
    struct  tagNODE *next;
    struct  tagNODE *prev;
}NODE;


typedef struct tagLINKLIST
{
    NODE *head;
    NODE *tail;
    size_t count;
}LINKLIST, *HLINKLIST;

/* Function Prototypes */

HLINKLIST create_link_list(void);
NODE *add_tail(HLINKLIST hlinklist,DATATYPE val);
NODE *addp_tail(HLINKLIST hlinklist,const DATATYPE *val);
NODE *add_head(HLINKLIST hlinklist,DATATYPE val);
NODE *addp_head(HLINKLIST hlinklist,const DATATYPE *val);
NODE *insert_next(HLINKLIST hlinklist,NODE *node, DATATYPE val);
NODE *insertp_next(HLINKLIST hlinklist,NODE *node, const DATATYPE *val);
NODE *insert_prev(HLINKLIST hlinklist,NODE *node, DATATYPE val);
NODE *insertp_prev(HLINKLIST hlinklist,NODE *node, const DATATYPE *val);
DATATYPE *getp_item(HLINKLIST hlinklist,size_t idx);
void remove_node(HLINKLIST hlinklist,NODE *node);
void clear_link_list(HLINKLIST hlinklist);
void destroy_link_list(HLINKLIST hlinklist);
bool walk_link_list(HLINKLIST hlinklist, bool(*proc)(NODE *));
bool walk_link_list_rev(HLINKLIST hlinklist, bool(*proc)(NODE *));

/* Inline Functions */
static inline size_t count_link_list(HLINKLIST hlinklist)
{
    return hlinklist->count;
}



#endif // LINKLIST_H
