#ifndef HPQUEUE_H_
#define HPQUEUE_H_

#include <stddef.h>
#include <stdbool.h>

#define PQUEUE_DEF_CAPACITY		1000
#define asize(a)   sizeof(a)/sizeof(*a)

/* Type Decleration */

typedef struct tagPERSON{
    char name[32];
}PERSON;

typedef PERSON DATATYPE;

typedef struct tagHEAPITEM{
    int prio;
    DATATYPE val;
}HEAPITEM;

typedef struct tagPQUEUE{
    HEAPITEM *hitems;
    size_t capacity;
    size_t count;
}PQUEUE,*HPQUEUE;

/* Function Prototype */

HPQUEUE create_pqueue(void);
bool put_pqueue(HPQUEUE hpqueue, int prio, DATATYPE *val);
void disp_pqueue(HPQUEUE hpqueue);
bool get_pqueue(HPQUEUE hpqueue, int *prio, DATATYPE *val);
bool resize_pqueue(HPQUEUE hpqueue, size_t new_capacity);
void destroy_pqueue(HPQUEUE hqueue);


/* inline Function Definitions */

static inline bool isempty_pqueue(HPQUEUE hpqueue)
{
	return hpqueue->count == 0;
}

static inline void clear_pqueue(HPQUEUE hpqueue)
{
	hpqueue->count = 0;
}

#endif // HPQUEUE_H_