#include <stdio.h>
#include <stdlib.h>
#include "hpqueue.h"

HPQUEUE create_pqueue(void){
    HPQUEUE hpqueue;
    if((hpqueue = (HPQUEUE)malloc(sizeof(PQUEUE))) == NULL)
        return NULL;
    
    if((hpqueue->hitems = (HEAPITEM*)malloc(sizeof(HEAPITEM)*PQUEUE_DEF_CAPACITY)) == NULL){
        free(hpqueue);
        return NULL;
    }
    hpqueue->capacity = PQUEUE_DEF_CAPACITY;
    hpqueue->count = 0;
    return hpqueue;
}

bool put_pqueue(HPQUEUE hpqueue, int prio, DATATYPE *val)
{
	size_t index;

	if (hpqueue->count + 1 == hpqueue->capacity) 
		if (!resize_pqueue(hpqueue, hpqueue->capacity * 2))
			return false;

	index = hpqueue->count + 1;

	while (index > 1 && prio > hpqueue->hitems[index / 2].prio) {
		hpqueue->hitems[index] = hpqueue->hitems[index / 2];
		index /= 2;
	}
	hpqueue->hitems[index].prio = prio;
	hpqueue->hitems[index].val = *val;
	++hpqueue->count;

	return true;
}

bool get_pqueue(HPQUEUE hpqueue, int *prio, DATATYPE *val)
{
	size_t i, ci;

	if (hpqueue->count == 0)
		return false;

	*prio = hpqueue->hitems[1].prio;
	*val = hpqueue->hitems[1].val;

	i = 1;
	ci = 2;

	while (ci <= hpqueue->count) {
		if (ci + 1 < hpqueue->count && hpqueue->hitems[ci + 1].prio > hpqueue->hitems[ci].prio)
			++ci;
		if (hpqueue->hitems[hpqueue->count].prio > hpqueue->hitems[ci].prio)
			break;
			
		hpqueue->hitems[i] = hpqueue->hitems[ci];
		i = ci;
		ci *= 2;
	}
	hpqueue->hitems[i] = hpqueue->hitems[hpqueue->count];
	--hpqueue->count;

	return true;
}

bool resize_pqueue(HPQUEUE hpqueue, size_t new_capacity)
{
	HEAPITEM *hitems;
	
	if (new_capacity <= hpqueue->capacity)
		return false;

	if ((hitems = (HEAPITEM *)realloc(hpqueue->hitems, new_capacity * sizeof(HEAPITEM))) == NULL)
		return false;

	hpqueue->hitems = hitems;
	hpqueue->capacity = new_capacity;

	return true;
}

void destroy_pqueue(HPQUEUE hpqueue)
{
	free(hpqueue->hitems);
	free(hpqueue);
}

void disp_pqueue(HPQUEUE hpqueue){
    for(int i = 1; i <= hpqueue->count; ++i)    
        printf("%d ",hpqueue->hitems[i].prio);
    printf("\n");
}