#include <stdio.h>
#include <stdlib.h>
#include "dynamicarray.h"


int main(void)
{
    HDARRAY hdarray;
    
    const DATATYPE vals[] = {9,9,9,9,9,9,9};

    if((hdarray = create_darray()) == NULL){
        fprintf(stderr,"Cannot Create Dynamic Array!\n");
        exit(EXIT_FAILURE);
    }

    for(int i = 10; i > 0; --i){
        if(add_darray(hdarray,i) == DARRAY_FAILED){
            fprintf(stderr,"Cannot Add Item!\n");
            exit(EXIT_FAILURE);
        }
        // printf("Count: %zd Capacity: %zd \n",count_darray(hdarray),capacity_darray(hdarray));
    }


    if(insert_darray(hdarray,5,1000) == DARRAY_FAILED){
        fprintf(stderr,"Insertion Failed!..\n");
        exit(EXIT_FAILURE);
    }

    printf("\n----------------------------\n\n");
    print_darray(hdarray);
    
    if(remove_darray(hdarray, 3) == DARRAY_FAILED){
        fprintf(stderr,"Remove Failed!..\n");
        exit(EXIT_FAILURE);
    }

    printf("\n----------------------------\n\n");
    print_darray(hdarray);
    
    printf("\n----------------------------\n\n");
    printf("Count: %zd Capacity: %zd \n",count_darray(hdarray),capacity_darray(hdarray));

    if(multi_add_darray( hdarray, vals, sizeof(vals)/sizeof(vals[0])) == DARRAY_FAILED){
        fprintf(stderr,"Cannot Add Multi Arrays!\n");
        exit(EXIT_FAILURE);
    }
    printf("\n----------------------------\n\n");
    print_darray(hdarray);

    printf("\n----------------------------\n\n");
    printf("Count: %zd Capacity: %zd \n",count_darray(hdarray),capacity_darray(hdarray));



    destroy_darray(hdarray);
    return 0;
}