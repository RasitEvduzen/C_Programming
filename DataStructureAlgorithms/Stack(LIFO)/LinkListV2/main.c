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
    if((hstack = create_stack()) == NULL){
        fprintf(stderr,"Cannot Create Stack!\n");
        exit(EXIT_FAILURE);
    }

    for(size_t i = 0; i < 10; ++i)
        if(!push_stack(hstack,i)){
            fprintf(stderr,"Cannot Push Stack!\n");
            exit(EXIT_FAILURE);
        }
    if(!disp_stack(hstack)){
        fprintf(stderr,"Stack Empty!\n");
        exit(EXIT_FAILURE);
    }

    for(size_t i = 0; i < 10; ++i){
        pop_stack(hstack,&val);
        printf("%d ",val);
    }
    printf("\n----------------\n");
    
    if(!disp_stack(hstack)){
        fprintf(stderr,"Stack Empty!\n");
        exit(EXIT_FAILURE);
    }
    //-----------------------------------------------
    //-----------------------------------------------

    return 0;
}