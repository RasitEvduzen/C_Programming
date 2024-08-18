#include <stdio.h>
#include <stdlib.h>
#include "linklist.h"


int main(void)
{
    HLINKLIST hlinklist;
    NODE *node, *pos_node;
    DATATYPE *val;

    if((hlinklist = create_link_list()) == NULL){
        fprintf(stderr,"Cannot Create Link List!\n");
        exit(EXIT_FAILURE);
    }

    // for(int i = 0; i < 100; ++i)
    //     if(add_tail(hlinklist,i) == NULL){
    //         fprintf(stderr,"Cannot Add Item!\n");
    //         exit(EXIT_FAILURE);
    //     }
    // walk_link_list_rev(hlinklist,NULL);

    // for(int i = 0; i < 100; ++i)
    //     if(add_head(hlinklist,i) == NULL){
    //         fprintf(stderr,"Cannot Add Item!\n");
    //         exit(EXIT_FAILURE);
    //     }
    // walk_link_list_rev(hlinklist,NULL);

    for(int i = 0; i < 10; ++i){
        if((node = add_tail(hlinklist,i)) == NULL){
            fprintf(stderr,"Cannot Add Item!\n");
            exit(EXIT_FAILURE);
        }
        if(i == 5)
            pos_node = node;
    }
    walk_link_list_rev(hlinklist,NULL);

    remove_node(hlinklist,pos_node);
    walk_link_list(hlinklist,NULL);

    // DATATYPE i_val = 100;
    // if(insertp_next(hlinklist,pos_node,&i_val) == NULL){
    // // if(insert_next(hlinklist,pos_node,100) == NULL){
    //     fprintf(stderr,"Cannot Insert!\n");
    //     exit(EXIT_FAILURE);
    // }
    // walk_link_list(hlinklist,NULL);

    // DATATYPE i_val = 100;
    // // if(insertp_prev(hlinklist,pos_node,&i_val) == NULL){
    // if(insert_prev(hlinklist,pos_node,100) == NULL){
    //     fprintf(stderr,"Cannot Insert!\n");
    //     exit(EXIT_FAILURE);
    // }
    // walk_link_list(hlinklist,NULL);

    // remove_node(hlinklist,pos_node);
    // walk_link_list(hlinklist,NULL);

    // if((val = getp_item(hlinklist,5)) == NULL){
    //     fprintf(stderr,"Invalid Index!\n");
    //     exit(EXIT_FAILURE);
    // }
    // printf("%d ",*val);


    return 0;
}
