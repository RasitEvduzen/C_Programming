#include <stdio.h>
#include <stdlib.h>
#include "queue.h"


HQUEUE create_queue(void)
{
	HQUEUE hqueue;
	if ((hqueue = (HQUEUE)malloc(sizeof(QUEUE))) == NULL)
		return NULL;

	hqueue->head = hqueue->tail = NULL;
	hqueue->count = 0;
	return hqueue;
}

bool put_queue(HQUEUE hqueue, DATATYPE val)
{
	NODE *new_node;
	if((new_node = (NODE *)malloc(sizeof(NODE))) == NULL)
		return false;
	new_node->val = val;
	new_node->next = NULL;
	if(hqueue->tail != NULL)
		hqueue->tail->next = new_node;
	else
		hqueue->head = new_node;
	hqueue->tail = new_node;
	++hqueue->count;
	return true;
}

bool putp_queue(HQUEUE hqueue, const DATATYPE *val)
{
	NODE *new_node;
	if((new_node = (NODE *)malloc(sizeof(NODE))) == NULL)
		return false;
	new_node->val = *val;
	new_node->next = NULL;
	if(hqueue->tail != NULL)
		hqueue->tail->next = new_node;
	else
		hqueue->head = new_node;
	hqueue->tail = new_node;
	++hqueue->count;
	return true;
}

bool get_queue(HQUEUE hqueue, DATATYPE *val)
{
	NODE *node;
    if(!hqueue->head)
        return false;
	node = hqueue->head;
    *val = node->val;
	if(!node->next)
		hqueue->tail = NULL;
	hqueue->head = hqueue->head->next;
    --hqueue->count;
	free(node);
    return true;
}



void clear_queue(HQUEUE hqueue)
{
	NODE *temp_node, *node = hqueue->head;
	while (node){
		temp_node = node->next;
		free(node);
		node = temp_node;
	}
	hqueue->head = hqueue->tail = NULL;
	hqueue->count = 0;
}

void clear_buffer(void)
{
	int ch;
	while ((ch = getchar()) != '\n' && ch != EOF)
	;	
}

void destroy_queue(HQUEUE hqueue)
{
	clear_queue(hqueue);
	free(hqueue);
}


void disp_queue(HQUEUE hqueue)
{
    for(size_t i=0; i<hqueue->count;++i){
		printf("%d ", hqueue->head->val);
		hqueue->head = hqueue->head->next;
	}
    putchar('\n');
}
