#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "btree.h"

static bool walk_inorder_lr_recur(NODE *node, size_t key_size, bool (*proc)(const void *, const void *));
static bool walk_inorder_rl_recur(NODE *node, size_t key_size, bool (*proc)(const void *, const void *));
static bool walk_postorder_lr_recur(NODE *node, size_t key_size, bool (*proc)(const void *, const void *));
static bool walk_preorder_lr_recur(NODE *node, size_t key_size, bool (*proc)(const void *, const void *));
static void create_queue(HBTREE hbtree);
static NODE *put_queue(HBTREE hbtree, NODE *node);
static NODE *get_queue(HBTREE hbtree);
static void destroy_queue(HBTREE hbtree);
static void subtree_shift(HBTREE hbtree, NODE *node1, NODE *node2, NODE *node3);
static void clear_recur(NODE *node);

HBTREE create_bt(size_t key_size, size_t value_size, int (*compare)(const void *, const void *))
{
	HBTREE hbtree;

	if ((hbtree = (HBTREE)malloc(sizeof(BTREE))) == NULL)
		return NULL;

	hbtree->root = NULL;
	hbtree->count = 0;
	hbtree->key_size = key_size;
	hbtree->value_size = value_size;
	hbtree->compare = compare;

	return hbtree;
}

bool insert_item_bt(HBTREE hbtree, const void *key, const void *value)
{
	NODE *new_node, *node, *parent_node = NULL;
	int result;

	if ((new_node = (NODE *)malloc(sizeof(NODE) + hbtree->key_size + hbtree->value_size)) == NULL)
		return false;
	memcpy(new_node->key_value, key, hbtree->key_size);
	memcpy(new_node->key_value + hbtree->key_size, value, hbtree->value_size);
	
	new_node->left = NULL;
	new_node->right = NULL;

	if (hbtree->root == NULL) {
		hbtree->root = new_node;
		++hbtree->count;
		return true;
	}
	node = hbtree->root;

	while (node != NULL) {
		parent_node = node;
		result = hbtree->compare(key, node->key_value);

		if (result < 0)
			node = node->left;
		else if (result > 0)
			node = node->right;
		else {
			memcpy(node->key_value + hbtree->key_size, value, hbtree->value_size);
			return true;
		}
	}

	if (hbtree->compare(key, parent_node->key_value) <  0)
		parent_node->left = new_node;
	else
		parent_node->right = new_node;

	++hbtree->count;

	return true;
}

bool walk_inorder_lr_bt(HBTREE hbtree, bool (*proc)(const void *, const void *))
{
	if (hbtree->root != NULL)
		return walk_inorder_lr_recur(hbtree->root, hbtree->key_size, proc);

	return true;
}

bool walk_inorder_rl_bt(HBTREE hbtree, bool (*proc)(const void *, const void *))
{
	if (hbtree->root != NULL)
		return walk_inorder_rl_recur(hbtree->root, hbtree->key_size, proc);

	return true;
}

bool walk_postorder_lr_bt(HBTREE hbtree, bool (*proc)(const void *, const void *))
{
	if (hbtree->root != NULL)
		return walk_postorder_lr_recur(hbtree->root, hbtree->key_size, proc);

	return true;
}

bool walk_preorder_lr_bt(HBTREE hbtree, bool (*proc)(const void *, const void *))
{
	if (hbtree->root != NULL)
		return walk_preorder_lr_recur(hbtree->root, hbtree->key_size, proc);

	return true;
}

static bool walk_preorder_lr_recur(NODE *node, size_t key_size, bool (*proc)(const void *, const void *))
{
	if (!proc(node->key_value, node->key_value + key_size))
		return false;

	if (node->left != NULL)
		if (!walk_preorder_lr_recur(node->left, key_size, proc))
			return false;

	if (node->right != NULL)
		if (!walk_preorder_lr_recur(node->right, key_size, proc))
			return false;
	
	return true;
}

bool walk_breadth_first_bt(HBTREE hbtree, bool (*proc)(const void *, const void *))
{
	NODE *node;
	bool result = true;

	create_queue(hbtree);
	put_queue(hbtree, hbtree->root);

	while ((node = get_queue(hbtree)) != NULL) {
		if (!proc(node->key_value, node->key_value + hbtree->key_size)) {
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

static NODE *put_queue(HBTREE hbtree, NODE *node)
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

bool delete_bt(HBTREE hbtree, const void *key)
{
	NODE *delete_node, *delete_parent_node, *replace_parent_node, *replace_node;
	int result;

	delete_node = hbtree->root;
	delete_parent_node = NULL;

	while (delete_node != NULL) {
		result = hbtree->compare(key, delete_node->key_value);
		if (result == 0)
			break;
		delete_parent_node = delete_node;
		if (result < 0)
			delete_node = delete_node->left;
		else if (result > 0)
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
		while (replace_node->left != NULL) {
			replace_parent_node = replace_node;
			replace_node = replace_node->left;
		}
		if (replace_parent_node != delete_node) {
			subtree_shift(hbtree, replace_parent_node, replace_node, replace_node->right);
			replace_node->right = delete_node->right;
		}
		subtree_shift(hbtree, delete_parent_node, delete_node, replace_node);
		replace_node->left = delete_node->left;
	}

	free(delete_node);
	--hbtree->count;

	return true;
}

void clear_bt(HBTREE hbtree)
{
	if (hbtree->root != NULL) {
		clear_recur(hbtree->root);
		hbtree->root = NULL;
		hbtree->count = 0;
	}
}

void destroy_bt(HBTREE hbtree)
{
	if (hbtree->root != NULL)
		clear_recur(hbtree->root);

	free(hbtree);
}

static bool walk_inorder_lr_recur(NODE *node, size_t key_size, bool (*proc)(const void *, const void *))
{
	if (node->left != NULL)
		if (!walk_inorder_lr_recur(node->left, key_size, proc))
			return false;

	if (!proc(node->key_value, node->key_value + key_size))
		return false;

	if (node->right != NULL)
		if (!walk_inorder_lr_recur(node->right, key_size, proc))
			return false;

	return true;
}

static bool walk_inorder_rl_recur(NODE *node, size_t key_size, bool (*proc)(const void *, const void *))
{
	if (node->right != NULL)
		if (!walk_inorder_rl_recur(node->right, key_size, proc))
			return false;

	if (!proc(node->key_value, node->key_value + key_size))
		return false;

	if (node->left != NULL)
		if (!walk_inorder_rl_recur(node->left, key_size, proc))
			return false;
	return true;
}

static bool walk_postorder_lr_recur(NODE *node, size_t key_size, bool (*proc)(const void *, const void *))
{
	if (node->left != NULL)
		if (!walk_postorder_lr_recur(node->left, key_size, proc))
			return false;

	if (node->right != NULL)
		if (!walk_postorder_lr_recur(node->right, key_size, proc))
			return false;

	if (!proc(node->key_value, node->key_value + key_size))
		return false;

	return true;
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


static void clear_recur(NODE *node)
{
	if (node->left != NULL)
		clear_recur(node->left);

	if (node->right != NULL)
		clear_recur(node->right);

	free(node);
}