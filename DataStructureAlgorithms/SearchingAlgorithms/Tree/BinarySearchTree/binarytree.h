#ifndef BINARYTREE_H_
#define BINARYTREE_H_

#include <stddef.h>
#include <stdio.h>
#include <stdbool.h>

/* Type Declerations */

typedef int DATATYPE;
 
 typedef struct tagPERSON{
    char name[32];
    int city;
 }PERSON;

typedef struct tagNODE{
    size_t key;
    PERSON value;
    struct tagNODE *left;
    struct tagNODE *right;    
}NODE;

 typedef struct tagQNODE{
    struct tagNODE *next;
    NODE *node;
    
 }QNODE;

typedef struct tagBTREE{
    NODE *root;
    size_t count;
    QNODE *head;
    QNODE *tail;
}BTREE, *HBTREE;

/* Function Prototypes */
HBTREE create_btree(void);
bool insert_item_btree(HBTREE hbtree, int key, const PERSON *val);
bool insert_item_btree_alternative(HBTREE hbtree, int key, const PERSON *val);
/* INORDER  FUNCTION */
bool walk_inorder_left_btree(HBTREE hbtree, bool(*proc)(int, PERSON *));
bool walk_inorder_right_btree(HBTREE hbtree, bool(*proc)(int, PERSON *));
/* POSTORDER FUNCTION */
bool walk_postorder_left_btree(HBTREE hbtree, bool(*proc)(int, PERSON *));
bool walk_postorder_right_btree(HBTREE hbtree, bool(*proc)(int, PERSON *));
/* PREORDER FUNCTION */
bool walk_preorder_left_btree(HBTREE hbtree, bool(*proc)(int, PERSON *));
bool walk_preorder_right_btree(HBTREE hbtree, bool(*proc)(int, PERSON *));
/* Breadth First */
bool walk_breadth_first(HBTREE hbtree, bool(*proc)(int, PERSON *));

bool delete_bt(HBTREE hbtree, int key);
void clear_btree(HBTREE hbtree);
void destroy_btree(HBTREE hbtree);
#endif //BINARYTREE_H_