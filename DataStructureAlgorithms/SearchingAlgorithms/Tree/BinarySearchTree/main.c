#include <stdio.h>
#include <stdlib.h>
#include "binarytree.h"

#define asize(a)  (sizeof(a)/sizeof(*a))

bool disp_node(int key, PERSON *val);


int main(void)
{
    HBTREE hbtree;
    PERSON person = {"Rasit Evduzen",0};
    int keys[] = {70, 50, 34, 56, 19, 80, 67, 43, 27, 76, 79, 105, 82, 65, 0};

    if((hbtree = create_btree()) == NULL)
    {
        fprintf(stderr,"Cannot Create Binary Tree!..\n");
        exit(EXIT_FAILURE);
    }
    for(int i = 0; keys[i]; ++i){
        if(!insert_item_btree_alternative(hbtree,keys[i],&person)){
            fprintf(stderr,"Cannot Insert %d Item!..\n",keys[i]);
            exit(EXIT_FAILURE);
        }
    }
    printf("\n\n ----------- Inorder Left Search ----------- \n");
    walk_inorder_left_btree(hbtree,disp_node);
    printf("\n\n ----------- Inorder Right Search ----------- \n");
    walk_inorder_right_btree(hbtree,disp_node);
    printf("\n\n ----------- Postorder Left Search ----------- \n");
    walk_postorder_left_btree(hbtree,disp_node);
    printf("\n\n ----------- Postorder Right Search ----------- \n");
    walk_postorder_right_btree(hbtree,disp_node);
    printf("\n\n ----------- Preorder Left Search ----------- \n");
    walk_preorder_left_btree(hbtree,disp_node);
    printf("\n\n ----------- Preorder Right Search ----------- \n");
    walk_preorder_right_btree(hbtree,disp_node);
    printf("\n\n ----------- Breadth First Search ----------- \n");
    walk_breadth_first(hbtree,disp_node);
    printf("\n\n ----------- Delete Node ----------- \n");
    if(!delete_bt(hbtree,80)){
        fprintf(stderr,"Cannot Delete Item!..\n");
        exit(EXIT_FAILURE);
    }




    // printf("\n\n ----------- Clear Binary Tree ----------- \n");
    // clear_btree(hbtree);
    // printf("\n\n ----------- Postorder Left Search ----------- \n");
    // walk_postorder_left_btree(hbtree,disp_node);

    destroy_btree(hbtree);
    exit(EXIT_SUCCESS);
}

bool disp_node(int key, PERSON *val)
{
    printf("%d ",key);
    fflush(stdout);
    return true;
}