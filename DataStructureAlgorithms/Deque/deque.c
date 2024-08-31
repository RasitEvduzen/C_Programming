#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "deque.h"

HDEQUE create_deque(void)
{
     HDEQUE hdeque;
    if((hdeque = (HDEQUE)malloc(sizeof(DEQUE))) == NULL)
        return NULL;
    if((hdeque->deque = (DATATYPE *)malloc(sizeof(DATATYPE) * DEFAULTCAPACITY)) == NULL){
        free(hdeque);
        return NULL;
    }
    hdeque->capacity = DEFAULTCAPACITY;
    hdeque->count = 0;
    hdeque->head = 0;
    hdeque->tail = 0;
    return hdeque;
}

size_t add_deque_back(HDEQUE hdeque, DATATYPE val)
{
    if(hdeque->count == hdeque->capacity && set_cap_deque(hdeque,hdeque->capacity * 2) == NULL)
        return DEQUEFAILED;
    hdeque->deque[hdeque->tail++] = val;    
    hdeque->tail %= hdeque->capacity;
    ++hdeque->count;
    return hdeque->count;
}

size_t addp_deque_back(HDEQUE hdeque,const DATATYPE *val)
{
    if(hdeque->count == hdeque->capacity && set_cap_deque(hdeque,hdeque->capacity * 2) == NULL)
        return DEQUEFAILED;
    hdeque->deque[hdeque->tail++] = *val;    
    hdeque->tail %= hdeque->capacity;
    ++hdeque->count;
    return hdeque->count;
}

size_t add_deque_front(HDEQUE hdeque, DATATYPE val)
{
    if(hdeque->count == hdeque->capacity && set_cap_deque(hdeque,hdeque->capacity * 2) == NULL)
        return DEQUEFAILED;
    if(hdeque->head == 0)
        hdeque->head = hdeque->capacity - 1;
    else
        --hdeque->head;
    hdeque->deque[hdeque->head] = val;
    ++hdeque->count;
    return 0;
}

size_t addp_deque_front(HDEQUE hdeque, const DATATYPE *val)
{
    if(hdeque->count == hdeque->capacity && set_cap_deque(hdeque,hdeque->capacity * 2) == NULL)
        return DEQUEFAILED;
    if(hdeque->head == 0)
        hdeque->head = hdeque->capacity - 1;
    else
        --hdeque->head;
    hdeque->deque[hdeque->head] = *val;
    ++hdeque->count;
    return 0;
}

DATATYPE get_deque_idx(HDEQUE hdeque, size_t idx)
{
    return hdeque->deque[(hdeque->head + idx) % hdeque->capacity];
}

void getp_deque_idx(HDEQUE hdeque, size_t idx, DATATYPE *val)
{
    *val = hdeque->deque[(hdeque->head + idx) % hdeque->capacity];
}

DATATYPE *set_cap_deque(HDEQUE hdeque,size_t new_capcacity)
{
    size_t size_1,size_2;
    DATATYPE *new_deque;
    if((new_deque = (DATATYPE*)malloc(sizeof(DATATYPE) * new_capcacity)) == NULL)
        return NULL;
    size_1 = MIN(hdeque->capacity - hdeque->head, hdeque->count);
    size_2 = hdeque->count - size_1;
    memcpy(new_deque,&hdeque->deque[hdeque->head],size_1*sizeof(DATATYPE));
    if(size_2) 
        memcpy(new_deque + size_1, hdeque->deque,size_2*sizeof(DATATYPE));
    free(hdeque->deque);
    hdeque->capacity = new_capcacity;
    hdeque->deque = new_deque;
    hdeque->head = 0;
    hdeque->tail = hdeque->count;
    return new_deque;
}

DATATYPE pop_deque_front(HDEQUE hdeque)
{
    size_t head;
    head = hdeque->head++;
    hdeque->head %= hdeque->capacity;
    return hdeque->deque[head];
}

void pop_deque_frontp(HDEQUE hdeque, DATATYPE *val)
{
    *val = hdeque->deque[hdeque->head++];
    hdeque->head %= hdeque->capacity;
}

size_t insert_deque(HDEQUE hdeque, size_t idx, DATATYPE val)
{
    size_t temp_idx;
    if (idx > hdeque->count) 
        return DEQUEFAILED;
    if(hdeque->count == hdeque->capacity && set_cap_deque(hdeque,hdeque->capacity * 2) == NULL) 
        return DEQUEFAILED;
    temp_idx = hdeque->tail;
    for(size_t i = 0; i < hdeque->count - idx; --i){
        if(!temp_idx){
            temp_idx = hdeque->capacity - 1;
            hdeque->deque[0] = hdeque->deque[temp_idx];
        }
        else{
            hdeque->deque[temp_idx] = hdeque->deque[temp_idx - 1];
            --temp_idx;
        }
    }
    hdeque->deque[idx] = val;
    return idx;
}

size_t remove_deque(HDEQUE hdeque,size_t idx)
{
    size_t temp_idx;
    if (idx >= hdeque->count) 
        return DEQUEFAILED;
    
    temp_idx = (hdeque->head + idx) % hdeque->capacity;   
    for(size_t i = 0; i < hdeque->count - idx - 1; ++i){
        if(temp_idx == hdeque->capacity - 1){
            hdeque->deque[temp_idx] = hdeque->deque[0];
            temp_idx = 0;
        }
        else{
            hdeque->deque[temp_idx] = hdeque->deque[temp_idx + 1];
            ++temp_idx;
        }
    }
    hdeque->tail = (hdeque->tail + hdeque->capacity - 1) % hdeque->capacity;
    --hdeque->count;
    return idx;
}

void clear_deque(HDEQUE hdeque)
{
    hdeque->head = hdeque->tail = 0;
    hdeque->count = 0;
}

void destroy_deque(HDEQUE hdeque)
{
    clear_deque(hdeque);
    free(hdeque->deque);
    free(hdeque);
}

void print_deque(HDEQUE hdeque)
{
    for(int i = 0; i < count_deque(hdeque); ++i) printf("%d ",get_deque_idx(hdeque,i));
    printf("\n");
}

void clear_buffer(void)
{
	int ch;
	while ((ch = getchar()) != '\n' && ch != EOF)
	;	
}