#ifndef DEQUE_H_
#define DEQUE_H_
#include <stddef.h>
#include <stdbool.h>

/* Symbolic Constant */
#define DEFAULTCAPACITY 8
#define DEQUEFAILED  ((size_t) - 1)
#define MIN(a,b)     ((a) < (b) ? (a) : (b))


/* Type Decleration */
typedef int DATATYPE;


typedef struct tagDEQUE{
    DATATYPE *deque;
    size_t capacity;
    size_t count;
    size_t head;
    size_t tail;
} DEQUE, *HDEQUE;

/* Function Prototype */
HDEQUE create_deque(void);
size_t add_deque_back(HDEQUE hdeque, DATATYPE val);
size_t addp_deque_back(HDEQUE hdeque, const DATATYPE *val);
size_t add_deque_front(HDEQUE hdeque, DATATYPE val);
size_t addp_deque_front(HDEQUE hdeque, const DATATYPE *val);
DATATYPE get_deque_idx(HDEQUE hdeque, size_t idx);
void getp_deque_idx(HDEQUE hdeque, size_t idx, DATATYPE *val);
DATATYPE *set_cap_deque(HDEQUE hdeque,size_t new_capacity);
DATATYPE pop_deque_front(HDEQUE hdeque);
size_t insert_deque(HDEQUE hdeque, size_t idx, DATATYPE val);
size_t remove_deque(HDEQUE hdeque,size_t idx);
void pop_deque_frontp(HDEQUE hdeque, DATATYPE *val);
void print_deque(HDEQUE hdeque);
void clear_deque(HDEQUE hdeque);
void destroy_deque(HDEQUE hdeque);
void clear_buffer(void);

/* Inline Functions */
static inline size_t count_deque(HDEQUE hdeque)
{
    return hdeque->count;
}

static inline size_t cap_deque(HDEQUE hdeque)
{
    return hdeque->capacity;
}

#endif  //DEQUE_H_
