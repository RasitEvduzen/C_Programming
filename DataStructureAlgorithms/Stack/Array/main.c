#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#include <stdbool.h>
#include "stack.h"


int main(void)
{
    // ------------------ TEST-1 ------------------//
    HSTACK hstack;
    DATATYPE val;
    if((hstack = create_stack(10)) == NULL){
        fprintf(stderr,"Cannot Create Stack!\n");
        exit(EXIT_FAILURE);
    }

    for(size_t i = 0; i < 10; ++i)
        if(!push_stack(hstack,i)){
            fprintf(stderr,"Cannot Push Stack!\n");
            exit(EXIT_FAILURE);
        }
    disp_stack(hstack);

    while(!isempty_stack(hstack)){
        pop_stack(hstack,&val);
        printf("%d ",val);
    }
    //-----------------------------------------------
    //-----------------------------------------------

    return 0;
}