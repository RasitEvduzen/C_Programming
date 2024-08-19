#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "SingleLinkList.h"

void buffer_fflush(void);

int main(void)
{
    // ------------------ TEST-1 ------------------//
    // Test Case: 100 nodes append to tail of linked list and display
    HLINKLIST hlinklist;
	PERSON per;
	char *str;
	
	if ((hlinklist = create_link_list()) == NULL) {
		fprintf(stderr, "cannot create linked list...\n");
		exit(EXIT_FAILURE);
	}

	for (;;) {
		printf("Name Surname :");
		if (fgets(per.name, 32, stdin) == NULL)
			continue;
		if ((str = strchr(per.name, '\n')) != NULL)
			*str = '\0';
		if (!strcmp(per.name, "quit"))
			break;
		printf("No: ");
		scanf("%d", &per.no);
		buffer_fflush();
		addp_tail(hlinklist, &per);
	}
    printf("------------------------\n");
	walk_link_list(hlinklist, NULL);
	if(destroy_link_list(hlinklist))
        printf("Single Link List Destroyed!\n");

	return 0;
}

void buffer_fflush(void)
{
    int ch;
    while ((ch = getchar()) != '\n' && ch != EOF)
        ;
}