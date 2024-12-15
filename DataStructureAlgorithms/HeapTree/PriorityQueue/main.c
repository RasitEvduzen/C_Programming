#include <stdio.h>
#include <stdlib.h>
#include "hpqueue.h"



int main(void)
{
    HPQUEUE hpqueue;
    DATATYPE data[] = {{"Temp-1"},{"Temp-2"},{"Temp-3"},{"Temp-4"},{"Temp-5"},{"Temp-6"},{"Temp-7"}};
    int prios[] = {70,34,17,41,60,84};
    int prio;
	DATATYPE value;

    if((hpqueue = create_pqueue()) == NULL){
        fprintf(stderr,"Cannot Create Priority Queue!..\n");
        exit(EXIT_FAILURE);
    }
    // Add Item
    for(int i = 0; i < asize(prios);++i){
        if(!put_pqueue(hpqueue,prios[i],&data[i])){
            fprintf(stderr,"Cannot Add Item!...\n");
            exit(EXIT_FAILURE);
        }
    }

    // Disp Heap Priority Queue
    disp_pqueue(hpqueue);

    // Get Item
	while (!isempty_pqueue(hpqueue)) {
		if (!get_pqueue(hpqueue, &prio, &value)) {
			fprintf(stderr, "cannot get value!..\n");
			exit(EXIT_FAILURE);
		}
		printf("prio: %d, value: %s\n", prio, value.name);
		disp_pqueue(hpqueue);
		printf("----------------------\n");
	}

	destroy_pqueue(hpqueue);

    return 0;
}


