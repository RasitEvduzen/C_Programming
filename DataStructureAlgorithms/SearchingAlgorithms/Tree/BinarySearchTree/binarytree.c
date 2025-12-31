#include <stdio.h>
#include <stdlib.h>
#include "binarytree.h"

static void clear_btree_recursive(NODE *node);

/* INORDER STATIC FUNCTION */
static bool walk_inorder_left_recursive(NODE *node, bool (*proc)(int,PERSON *));
static bool walk_inorder_right_recursive(NODE *node, bool (*proc)(int,PERSON *));

/* POSTORDER STATIC FUNCTION */
static bool walk_postorder_left_recursive(NODE *node, bool (*proc)(int,PERSON *));
static bool walk_postorder_right_recursive(NODE *node, bool (*proc)(int,PERSON *));

/* PREORDER STATIC FUNCTION */
static bool walk_preorder_left_recursive(NODE *node, bool (*proc)(int,PERSON *));
static bool walk_preorder_right_recursive(NODE *node, bool (*proc)(int,PERSON *));

static void create_queue(HBTREE hbtree);
static NODE *put_queue(HBTREE hbtree, NODE *node);
static NODE *get_queue(HBTREE hbtree);
static void destroy_queue(HBTREE hbtree);
static void subtree_shift(HBTREE hbtree, NODE *node1, NODE *node2, NODE *node3);

HBTREE create_btree(void)
{
    HBTREE hbtree;

    if((hbtree = (HBTREE)malloc(sizeof(BTREE))) == NULL)
        return NULL;

    hbtree->root = NULL;
    hbtree->count = 0;
    return hbtree;    
}



bool insert_item_btree(HBTREE hbtree, int key, const PERSON *val)
{
    NODE *new_node, *node, *parent_node;
    if((new_node = (NODE*)malloc(sizeof(NODE))) == NULL)
        return false;
    new_node->key = key;
    new_node->value = *val;
    new_node->left = new_node->right = NULL;
    if(hbtree->root == NULL){
        hbtree->root = new_node;
        ++hbtree->count;
        return true;
    }
    node = hbtree->root;
    while (node != NULL){
        parent_node = node;
        if(key < node->key) node = node->left;
        else if(key > node->key)  node = node->right;
        else{
            node->value = *val;
            return true;
        }
    }
    if(key < parent_node->key) parent_node->left = new_node;
    else parent_node->right = new_node;
    ++hbtree->count;
    return true; 
}

bool insert_item_btree_alternative(HBTREE hbtree, int key, const PERSON *val)
{
    NODE *new_node, *node;
    if((new_node = (NODE*)malloc(sizeof(NODE))) == NULL)
        return false;
    new_node->key = key;
    new_node->value = *val;
    new_node->left = new_node->right = NULL;
    if(hbtree->root == NULL){
        hbtree->root = new_node;
        ++hbtree->count;
        return true;
    }
    node = hbtree->root;
    while (node != NULL){
        if(key < node->key)
            if(node->left == NULL){
                node->left = new_node;
                break;
            } 
            else
                node = node->left;
        else if(key > node->key)  
            if(node->right == NULL){
                node->right = new_node;
                break;
            } 
            else
                node = node->right;
        else{
            node->value = *val;
            return true;
        }
    }
    ++hbtree->count;
    return true; 
}

void clear_btree(HBTREE hbtree)
{
    if(hbtree->root){
        clear_btree_recursive(hbtree->root);
        hbtree->root = NULL;
        hbtree->count = 0;    
    } 
    
}
void destroy_btree(HBTREE hbtree)
{
    if(hbtree->root) clear_btree(hbtree);
    free(hbtree);
}

/* INORDER  FUNCTION */
bool walk_inorder_left_btree(HBTREE hbtree, bool(*proc)(int, PERSON *))
{
    if(hbtree->root) return walk_inorder_left_recursive(hbtree->root,proc);
    return false;
}

bool walk_inorder_right_btree(HBTREE hbtree, bool(*proc)(int, PERSON *))
{
    if(hbtree->root) return walk_inorder_right_recursive(hbtree->root,proc);
    return false;
}

/* POSTORDER FUNCTION */
bool walk_postorder_left_btree(HBTREE hbtree, bool(*proc)(int, PERSON *))
{
    if(hbtree->root) return walk_postorder_left_recursive(hbtree->root,proc);
    return false;
}

bool walk_postorder_right_btree(HBTREE hbtree, bool(*proc)(int, PERSON *))
{
    if(hbtree->root) return walk_postorder_right_recursive(hbtree->root,proc);
    return false;
}

/* PREORDER FUNCTION */
bool walk_preorder_left_btree(HBTREE hbtree, bool(*proc)(int, PERSON *))
{
    if(hbtree->root) return walk_preorder_left_recursive(hbtree->root,proc);
    return false;
}

bool walk_preorder_right_btree(HBTREE hbtree, bool(*proc)(int, PERSON *))
{
    if(hbtree->root) return walk_preorder_right_recursive(hbtree->root,proc);
    return false;
}

/* INORDER STATIC FUNCTION */
static bool walk_inorder_left_recursive(NODE *node, bool (*proc)(int,PERSON *))
{
    if(node->left != NULL) if(!walk_inorder_left_recursive(node->left,proc)) return false;
    if(!proc(node->key,&node->value)) return false;        
    if(node->right != NULL) if(!walk_inorder_left_recursive(node->right,proc)) return false;
    return true;
}

static bool walk_inorder_right_recursive(NODE *node, bool (*proc)(int,PERSON *))
{
    if(node->right != NULL) if(!walk_inorder_right_recursive(node->right,proc)) return false;
    if(!proc(node->key,&node->value)) return false;        
    if(node->left != NULL) if(!walk_inorder_right_recursive(node->left,proc)) return false;
    return true;
}

/* POSTORDER STATIC FUNCTION */
static bool walk_postorder_left_recursive(NODE *node, bool (*proc)(int,PERSON *))
{
    if(node->left != NULL) if(!walk_postorder_left_recursive(node->left,proc)) return false;
    if(node->right != NULL) if(!walk_postorder_left_recursive(node->right,proc)) return false;
    if(!proc(node->key,&node->value)) return false;        
    return true;
}

static bool walk_postorder_right_recursive(NODE *node, bool (*proc)(int,PERSON *))
{
    if(node->right != NULL) if(!walk_postorder_right_recursive(node->right,proc)) return false;
    if(node->left != NULL) if(!walk_postorder_right_recursive(node->left,proc)) return false;
    if(!proc(node->key,&node->value)) return false;        
    return true;
}

/* PREORDER STATIC FUNCTION */
static bool walk_preorder_left_recursive(NODE *node, bool (*proc)(int,PERSON *))
{
    if(!proc(node->key,&node->value)) return false;    
    if(node->left != NULL) if(!walk_preorder_left_recursive(node->left,proc)) return false;
    if(node->right != NULL) if(!walk_preorder_left_recursive(node->right,proc)) return false;
    return true;
}

static bool walk_preorder_right_recursive(NODE *node, bool (*proc)(int,PERSON *))
{
    if(!proc(node->key,&node->value)) return false;
    if(node->right != NULL) if(!walk_preorder_right_recursive(node->right,proc)) return false;    
    if(node->left != NULL) if(!walk_preorder_right_recursive(node->left,proc)) return false;
    return true;
}

/* Breadth First */
bool walk_breadth_first(HBTREE hbtree, bool(*proc)(int, PERSON *))
{
	NODE *node;
	bool result = true;
	create_queue(hbtree);
	put_queue(hbtree, hbtree->root);
	while ((node = get_queue(hbtree)) != NULL) {
		if (!proc(node->key, &node->value)) {
			result = false;
			break;
		}
		if (node->left != NULL)
			if (put_queue(hbtree, node->left) == NULL) {
				fprintf(stderr, "put_queue cannot allocate memory!..\n");
				result = false;
				break;
			}
		if (node->right != NULL)
			if (put_queue(hbtree, node->right) == NULL) {
				result = false;
				fprintf(stderr, "put_queue cannot allocate memory!..\n");
				break;
			}
	}
	destroy_queue(hbtree);
	return result;
}

static void create_queue(HBTREE hbtree)
{
    hbtree->head = NULL;
    hbtree->tail = NULL;
}

static NODE * put_queue(HBTREE hbtree, NODE *node)
{
	QNODE *new_qnode;
	if ((new_qnode = (QNODE *)malloc(sizeof(QNODE))) == NULL)
		return NULL;
	new_qnode->node = node;
	new_qnode->next = NULL;
	if (hbtree->tail != NULL)
		hbtree->tail->next = new_qnode;
	else
		hbtree->head = new_qnode;
	hbtree->tail = new_qnode;
	return node;
}

static NODE *get_queue(HBTREE hbtree)
{
	QNODE *qnode;
	NODE *rnode;
	if (hbtree->head == NULL)
		return NULL;
	qnode = hbtree->head;
	hbtree->head = qnode->next;
	if (hbtree->head == NULL)
		hbtree->tail = NULL;
	rnode = qnode->node;
	free(qnode);
	return rnode;
}

bool delete_bt(HBTREE hbtree, int key)
{
	NODE *delete_node, *delete_parent_node, *replace_parent_node, *replace_node;
	delete_node= hbtree->root;
	delete_parent_node = NULL;
	while (delete_node != NULL) {
		if (delete_node->key == key)
			break;
		delete_parent_node = delete_node;
		if (key < delete_node->key)
			delete_node = delete_node->left;
		else if (key > delete_node->key )
			delete_node = delete_node->right;
	}
	if (delete_node == NULL)
		return false;
	if (delete_node->left == NULL)
		subtree_shift(hbtree, delete_parent_node, delete_node, delete_node->right);
	else if (delete_node->right == NULL)
		subtree_shift(hbtree, delete_parent_node, delete_node, delete_node->left);
	else {
		replace_parent_node = delete_node;
		replace_node = delete_node->right;
		while (replace_node->left!= NULL) {
			replace_parent_node = replace_node;
			replace_node= replace_node->left;
		}
		if (replace_parent_node != delete_node) {
			subtree_shift(hbtree, replace_parent_node, replace_node, replace_node->right);
			replace_node->right= delete_node->right;
		}
		subtree_shift(hbtree, delete_parent_node, delete_node, replace_node);
		replace_node->left = delete_node->left;
	}
	free(delete_node);
	--hbtree->count;
	return true;
}


static void clear_btree_recursive(NODE *node)
{
    if(node->left) clear_btree_recursive(node->left);
    if(node->right) clear_btree_recursive(node->right);
    free(node);
}

static void destroy_queue(HBTREE hbtree)
{
	QNODE *qnode, *temp_qnode;
	qnode = hbtree->head;
	while (qnode != NULL) {
		temp_qnode = qnode->next;
		free(qnode);
		qnode = temp_qnode;
	}
}

static void subtree_shift(HBTREE hbtree, NODE *node1, NODE *node2, NODE *node3)
{
	if (node1 == NULL)
		hbtree->root = node3;
	else if (node1->left == node2)
		node1->left = node3;
	else
		node1->right = node3;
}