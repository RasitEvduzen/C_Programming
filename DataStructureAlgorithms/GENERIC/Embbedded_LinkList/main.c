#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "llist.h"

typedef struct tagPERSON {
	char name[32];
	int no;
	NODE link;
} PERSON;

bool disp_person(NODE *node);    // Function prototype for displaying person information

int main(void)
{
	HLLIST hllist;
	PERSON *per;
	NODE *node;
    
	if ((hllist = create_llist()) == NULL) {
		fprintf(stderr, "cannot create linked list...\n");
		exit(EXIT_FAILURE);
	}

	for (int i = 0; i < 100; ++i) {
		if ((per = (PERSON *)malloc(sizeof(PERSON))) == NULL) {
			fprintf(stderr, "ccano tallocate memory!..\n");
			exit(EXIT_FAILURE);
		}
		per->no = i;
		per->name[0] = '\0';
		add_tail(hllist, &per->link);
	}
	walk_llist(hllist, disp_person);
	
	printf("\n--------------------\n");
	FOR_EACH (hllist, node) {
		per = container_of(node, PERSON, link);
		printf("%d ", per->no);
		fflush(stdout);
	}

	printf("\n--------------------\n");
	FOR_EACH_REV (hllist, node) {
		per = container_of(node, PERSON, link);
		printf("%d ", per->no);
		fflush(stdout);
	}

	FREE_LLIST(hllist, node) {
		per = container_of(node, PERSON, link);
		free(per);
	}
	return 0;
}


bool disp_person(NODE *node) // Function to display person information
{
	PERSON *per;
	per = container_of(node, PERSON, link);
	printf("%d ", per->no);
	fflush(stdout);
	return true;
}