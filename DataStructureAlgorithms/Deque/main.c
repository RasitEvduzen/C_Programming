#include <stdio.h>
#include <stdlib.h>
#include "deque.h"

int main(void)
{
    // ------------------ TEST-1 ------------------//
    // HDEQUE hdeque;
    // if((hdeque = create_deque()) == NULL){
    //     fprintf(stderr,"Cannot Create Deque!\n");
    //     exit(EXIT_FAILURE);
    // }
    // for(int i = 0; i < 20; ++i)
    //     if(add_deque_back(hdeque,i) == DEQUEFAILED){
    //         fprintf(stderr,"Cannot Add Item Into Deque!\n");
    //         exit(EXIT_FAILURE);
    //     }
    // printf("Deque Count : %d\n",count_deque(hdeque));
    // print_deque(hdeque);
    // for(int i = 0; i < 20; ++i)
    //     if(add_deque_front(hdeque,i) == DEQUEFAILED){   
    //         fprintf(stderr,"Cannot Add Item Into Deque!\n");
    //         exit(EXIT_FAILURE);
    //     }
    // printf("Deque Count : %d\n",count_deque(hdeque));
    // print_deque(hdeque);
    // destroy_deque(hdeque);
    //-----------------------------------------------
    //-----------------------------------------------
    // ------------------ TEST-2 ------------------//
    HDEQUE hdeque;
    if((hdeque = create_deque()) == NULL){
        fprintf(stderr,"Cannot Create Deque!\n");
        exit(EXIT_FAILURE);
    }
    for(int i = 0; i < 10; ++i)
        if(add_deque_back(hdeque,i) == DEQUEFAILED){
            fprintf(stderr,"Cannot Add Item Into Deque!\n");
            exit(EXIT_FAILURE);
        }
    printf("Deque Count : %d\n",count_deque(hdeque));
    print_deque(hdeque);
    insert_deque(hdeque,5,100);
    print_deque(hdeque);
    remove_deque(hdeque,5);
    print_deque(hdeque);
    //-----------------------------------------------
    //-----------------------------------------------

    return 0;
}
