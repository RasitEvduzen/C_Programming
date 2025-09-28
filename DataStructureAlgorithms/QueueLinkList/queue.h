#ifndef QUEUE_H_
#define QUEUE_H_

#include <stddef.h>
#include <stdbool.h>

typedef int DATATYPE;

typedef struct tagNODE{
    DATATYPE val;
    struct tagNODE *next;    
    
}NODE;

typedef struct tagQUEUE{
    DATATYPE *queue;
    NODE *head;
    NODE *tail;
    size_t count;
}QUEUE, *HQUEUE;


/* Function Prototypes(Decleration) */
HQUEUE create_queue(void);
bool put_queue(HQUEUE hqueue, DATATYPE val);
bool putp_queue(HQUEUE hqueue, const DATATYPE *val);
bool get_queue(HQUEUE hqueue, DATATYPE *val);
void clear_queue(HQUEUE hqueue);
void destroy_queue(HQUEUE hqueue);
void disp_queue(HQUEUE hqueue);
void clear_buffer(void);

/* Inline Function Definition */
static inline bool isempty_queue(HQUEUE hqueue)
{
    return hqueue->count == 0;
}

static inline bool count_queue(HQUEUE hqueue)
{
    return hqueue->count;
}

#endif //QUEUE_H_
