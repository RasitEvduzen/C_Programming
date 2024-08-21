#ifndef SINGLELINKLIST_H_
#define SINGLELINKLIST_H_

#include <stddef.h>
#include <stdbool.h>

/* Type Declerations */

typedef struct tagPERSON{
    char name[32];
    int no;
}PERSON;

typedef PERSON DATATYPE;

typedef struct tagNODE
{
    DATATYPE val;
    struct  tagNODE *next;
}NODE;


typedef struct tagLINKLIST
{
    NODE *head;
    NODE *tail;
    size_t count;
}LINKLIST, *HLINKLIST;

/* Function Prototypes */

HLINKLIST create_link_list(void);
NODE *addp_tail(HLINKLIST hlinklist,const PERSON *val);
NODE *addp_head(HLINKLIST hlinklist,const DATATYPE *val);
NODE *insertp_next(HLINKLIST hlinklist,NODE *node, const DATATYPE *val);
DATATYPE *getp_item(HLINKLIST hlinklist,size_t idx);
void remove_next(HLINKLIST hlinklist,NODE *node);
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
