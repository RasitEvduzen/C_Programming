#include <stdio.h>
#include <stdlib.h>
#include "SingleLinkList.h"


int main(void)
{
    // ------------------ TEST-1 ------------------//
    // Test Case: 100 nodes append to tail of linked list and display
    // HLINKLIST hlinklist;
    // if((hlinklist = create_link_list()) == NULL){
    //     fprintf(stderr,"Cannot Create link list...!\n");
    //     exit(EXIT_FAILURE);
    // }

    // for(int i=0; i<100; ++i)
    //     if(add_tail(hlinklist,i)== NULL){
    //         fprintf(stderr,"Cannot Add Item to List..!\n");
    //         exit(EXIT_FAILURE);
    //     }
    // walk_link_list(hlinklist,NULL);
    //-----------------------------------------------
    //-----------------------------------------------

    // ------------------ TEST-2 ------------------//
    // Test Case: 100 nodes append to head of linked list and display
    // HLINKLIST hlinklist;
    // if((hlinklist = create_link_list()) == NULL){
    //     fprintf(stderr,"Cannot Create link list...!\n");
    //     exit(EXIT_FAILURE);
    // }

    // for(int i=0; i<100; ++i)
    //     if(add_head(hlinklist,i)== NULL){
    //         fprintf(stderr,"Cannot Add Item to List..!\n");
    //         exit(EXIT_FAILURE);
    //     }
    // walk_link_list(hlinklist,NULL);
    //-----------------------------------------------
    //-----------------------------------------------

    // ------------------ TEST-3 ------------------//
    // Test Case: Insert linked list next node and display
    // HLINKLIST hlinklist;
    // NODE *node,*pos_node;
    // if((hlinklist = create_link_list()) == NULL){
    //     fprintf(stderr,"Cannot Create link list...!\n");
    //     exit(EXIT_FAILURE);
    // }

    // for(int i=0; i<10; ++i){
    //     if((node = add_tail(hlinklist,i))== NULL){
    //         fprintf(stderr,"Cannot Add Item to List..!\n");
    //         exit(EXIT_FAILURE);
    //     }
    //     if(i == 5)
    //         pos_node = node;
    // }
    // walk_link_list(hlinklist,NULL);
    // if(insert_next(hlinklist,pos_node,100) == NULL){
    //     fprintf(stderr,"Cannot Instert Next Node..!\n");
    //     exit(EXIT_FAILURE);
    // }
    // walk_link_list(hlinklist,NULL);
    //-----------------------------------------------
    //-----------------------------------------------

    // ------------------ TEST-4 ------------------//
    // Test Case: remove linked list next node and display
    // HLINKLIST hlinklist;
    // NODE *node,*pos_node;
    // if((hlinklist = create_link_list()) == NULL){
    //     fprintf(stderr,"Cannot Create link list...!\n");
    //     exit(EXIT_FAILURE);
    // }

    // for(int i=0; i<10; ++i){
    //     if((node = add_tail(hlinklist,i))== NULL){
    //         fprintf(stderr,"Cannot Add Item to List..!\n");
    //         exit(EXIT_FAILURE);
    //     }
    //     if(i == 3)
    //         pos_node = node;
    // }
    // walk_link_list(hlinklist,NULL);
    // remove_next(hlinklist,pos_node);
    // walk_link_list(hlinklist,NULL);
    //-----------------------------------------------
    //-----------------------------------------------

    // ------------------ TEST-5 ------------------//
    // Test Case: get specific node and display
    // HLINKLIST hlinklist;
    // int *val;
    // int idx = 3;
    // if((hlinklist = create_link_list()) == NULL){
    //     fprintf(stderr,"Cannot Create link list...!\n");
    //     exit(EXIT_FAILURE);
    // }

    // for(int i=0; i<10; ++i)
    //     if(add_tail(hlinklist,i)== NULL){
    //         fprintf(stderr,"Cannot Add Item to List..!\n");
    //         exit(EXIT_FAILURE);
    //     }

    // walk_link_list(hlinklist,NULL);
    // if((val = getp_item(hlinklist,idx)) == NULL){
    //     fprintf(stderr,"Invalid Index..!\n");
    //     exit(EXIT_FAILURE);
    // }
    // printf("%d\n",*val);
    //-----------------------------------------------
    //-----------------------------------------------

    // ------------------ TEST-6 ------------------//
    // Test Case: clear and destroy link list and display
    HLINKLIST hlinklist;
    int *val;
    int idx = 3;
    if((hlinklist = create_link_list()) == NULL){
        fprintf(stderr,"Cannot Create link list...!\n");
        exit(EXIT_FAILURE);
    }

    for(int i=0; i<10; ++i)
        if(add_tail(hlinklist,i)== NULL){
            fprintf(stderr,"Cannot Add Item to List..!\n");
            exit(EXIT_FAILURE);
        }

    walk_link_list(hlinklist,NULL);
    clear_link_list(hlinklist);

    for(int i=0; i<10; ++i)
        if(add_head(hlinklist,i)== NULL){
            fprintf(stderr,"Cannot Add Item to List..!\n");
            exit(EXIT_FAILURE);
        }
    walk_link_list(hlinklist,NULL);
    if(destroy_link_list(hlinklist))
        printf("List Destroyed!\n");
    //-----------------------------------------------
    //-----------------------------------------------

    return 0;
}
