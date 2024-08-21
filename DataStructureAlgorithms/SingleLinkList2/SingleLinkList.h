#ifndef SINGLELINKLIST_H_
#define SINGLELINKLIST_H_

#include <stddef.h>
#include <stdbool.h>

/* Type Declerations */

typedef int DATATYPE;

typedef struct tagNODE
{
    DATATYPE val;
    struct  tagNODE *next;
}NODE;


typedef struct tagLINKLIST
{
    NODE head;
    NODE *tail;
    size_t count;
}LINKLIST, *HLINKLIST;

/* Function Prototypes */

HLINKLIST create_link_list(void);
NODE *insert_next(HLINKLIST hlinklist,NODE *node, DATATYPE val);
NODE *insertp_next(HLINKLIST hlinklist,NODE *node, const DATATYPE *val);
NODE *add_tail(HLINKLIST hlinklist,DATATYPE val);
NODE *addp_tail(HLINKLIST hlinklist,const DATATYPE *val);
NODE *add_head(HLINKLIST hlinklist,DATATYPE val);
NODE *addp_head(HLINKLIST hlinklist,const DATATYPE *val);
DATATYPE *getp_item(HLINKLIST hlinklist,size_t idx);
void remove_next(HLINKLIST hlinklist,NODE *node);
void remove_head(HLINKLIST hlinklist);
void clear_link_list(HLINKLIST hlinklist);
bool destroy_link_list(HLINKLIST hlinklist);
bool walk_link_list(HLINKLIST hlinklist, bool(*proc)(DATATYPE *));
void clear_buffer(void);

/* Inline Functions */
static inline size_t count_link_list(HLINKLIST hlinklist)
{
    return hlinklist->count;
}


#endif // SINGLELINKLIST_H_
