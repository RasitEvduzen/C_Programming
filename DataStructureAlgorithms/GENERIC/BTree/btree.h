#ifndef BTREE_H_
#define BTREE_H_

#include <stddef.h>
#include <stdbool.h>

/* Type Declararions */

typedef struct tagNODE {
	struct tagNODE *left;
	struct tagNODE *right;
	char key_value[];
} NODE;

typedef struct tagQNODE {
	struct tagQNODE *next;
	NODE *node;
} QNODE;

typedef struct tagBTREE {
	NODE *root;
	size_t count;
	QNODE *head;
	QNODE *tail;
	size_t key_size;
	size_t value_size;
	int (*compare)(const void *, const void *);
} BTREE, *HBTREE;

/* Function Prototypes */

HBTREE create_bt(size_t key_size, size_t value_size, int (*compare)(const void *, const void *));
bool insert_item_bt(HBTREE hbtree, const void *key, const void *value);
bool walk_inorder_lr_bt(HBTREE hbtree, bool (*proc)(const void *, const void *));
bool walk_inorder_rl_bt(HBTREE hbtree, bool (*proc)(const void *, const void *));
bool walk_postorder_lr_bt(HBTREE hbtree, bool (*proc)(const void *, const void *));
bool walk_preorder_lr_bt(HBTREE hbtree, bool (*proc)(const void *, const void *));
bool walk_breadth_first_bt(HBTREE hbtree, bool (*proc)(const void *, const void *));
bool delete_bt(HBTREE hbtree, const void *key);
void clear_bt(HBTREE hbtree);
void destroy_bt(HBTREE hbtree);

/* inline Function Fefinitions */

static inline size_t count_bt(HBTREE hbtree)
{
	return hbtree->count;
}

#endif /* BTREE_H_ */