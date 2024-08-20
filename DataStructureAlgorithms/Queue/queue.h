#ifndef QUEUE_H_
#define QUEUE_H_

#include <stddef.h>
#include <stdbool.h>

typedef int DATATYPE;

typedef struct tagQUEUE{
    DATATYPE *queue;
    size_t head;
    size_t tail;
    size_t size;
    size_t count;
}QUEUE, *HQUEUE;


/* Function Prototypes(Decleration) */
HQUEUE create_queue(size_t size);
bool put_queue(HQUEUE hqueue, DATATYPE val);
bool putp_queue(HQUEUE hqueue, const DATATYPE *val);
bool get_queue(HQUEUE hqueue, DATATYPE *val);
DATATYPE *getp_queue(HQUEUE hqueue);
bool resize_queue(HQUEUE hqueue, size_t newsize);
void clear_queue(HQUEUE hqueue);
void destroy_queue(HQUEUE hqueue);
void disp_queue(HQUEUE hqueue);

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