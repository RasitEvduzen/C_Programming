#include <stdio.h>
#include <stdlib.h>
#include "queue.h"


HQUEUE create_queue(size_t size)
{
	HQUEUE hqueue;
	if ((hqueue = (HQUEUE)malloc(sizeof(QUEUE))) == NULL)
		return NULL;
	if ((hqueue->queue = (DATATYPE *)malloc(sizeof(DATATYPE) * size)) == NULL) {
		free(hqueue);
		return NULL;
	}
	hqueue->head = hqueue->tail = 0;
	hqueue->size = size;
	hqueue->count = 0;
	return hqueue;
}

bool put_queue(HQUEUE hqueue, DATATYPE val)
{
    if(hqueue->count == hqueue->size)
        return false;
    hqueue->queue[hqueue->tail++] = val;
    hqueue->tail %= hqueue->size;
    ++hqueue->count;
    return true;
}

bool putp_queue(HQUEUE hqueue, const DATATYPE *val)
{
    if(hqueue->count == hqueue->size)
        return false;
    hqueue->queue[hqueue->tail++] = *val;
    hqueue->tail %= hqueue->size;
    ++hqueue->count;
    return true;
}

bool get_queue(HQUEUE hqueue, DATATYPE *val)
{
    if(!hqueue->count)
        return false;
    *val = hqueue->queue[hqueue->head++];
    hqueue->head %= hqueue->size;
    --hqueue->count;
    return true;
}

DATATYPE *getp_queue(HQUEUE hqueue)
{
    if(!hqueue->count)
        return NULL;
    hqueue->head %= hqueue->size;
    --hqueue->count;
    return &hqueue->queue[hqueue->head++];
}

bool resize_queue(HQUEUE hqueue, size_t newsize)
{
	DATATYPE *new_queue;
	if (newsize <= hqueue->size)
		return false;
	if ((new_queue = (DATATYPE *)malloc(newsize * sizeof(DATATYPE))) == NULL)
		return false;
	for (size_t i = 0, head = hqueue->head; i < hqueue->size; ++i) {
		new_queue[i] = hqueue->queue[head++];
		head %= hqueue->size;
	}

	hqueue->head = 0;
	hqueue->tail = hqueue->count;
	hqueue->size = newsize;
	free(hqueue->queue);
	hqueue->queue = new_queue;
	return true;
}


void clear_queue(HQUEUE hqueue)
{
	hqueue->count = 0;
	hqueue->head = 0;
	hqueue->tail = 0;
}
void clear_buffer(void)
{
	int ch;
	while ((ch = getchar()) != '\n' && ch != EOF)
	;	
}

void destroy_queue(HQUEUE hqueue)
{
	free(hqueue->queue);
	free(hqueue);
}

void disp_queue(HQUEUE hqueue)
{
    for(size_t i=0; i<hqueue->count;++i){
	printf("%d ", hqueue->queue[i]);
	clear_buffer();
	}
    putchar('\n');
}

