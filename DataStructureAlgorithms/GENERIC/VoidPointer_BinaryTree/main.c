#include <stdio.h>
#include <stdlib.h>
#include "btree.h"

typedef struct tagPERSON {
	char name[32];
	int no;
} PERSON;

bool disp_node(const void *key, const void *value);
int comp_person(const void *key1, const void *key2);

int main(void)
{
	HBTREE hbtree;
	PERSON per = {"Noname", 0};
	int keys[] = {70, 50, 34, 56, 19, 80, 67, 43, 27, 76, 79, 105, 82, 65, 0};
	int del_key = 70;

	if ((hbtree = create_bt(sizeof(int), sizeof(PERSON), comp_person)) == NULL) {
		fprintf(stderr, "cannot create binary tree!..\n");
		exit(EXIT_FAILURE);
	}

	for (int i = 0; keys[i] != 0; ++i)
		if (!insert_item_bt(hbtree, &keys[i], &per)) {
			fprintf(stderr, "cannot insert item: %d\n", keys[i]);
			exit(EXIT_FAILURE);
		}
	
	walk_inorder_lr_bt(hbtree, disp_node);
	printf("\n------------------------------\n");
	walk_inorder_rl_bt(hbtree, disp_node);
	printf("\n------------------------------\n");
	walk_postorder_lr_bt(hbtree, disp_node);
	printf("\n------------------------------\n");
	walk_preorder_lr_bt(hbtree, disp_node);
	printf("\n------------------------------\n");
	walk_breadth_first_bt(hbtree, disp_node);
	printf("\n------------------------------\n");
	if (!delete_bt(hbtree, &del_key)) {
		fprintf(stderr, "cannot find item!...\n");
		exit(EXIT_FAILURE);
	}
	walk_breadth_first_bt(hbtree, disp_node);

	destroy_bt(hbtree);

	return 0;
}

bool disp_node(const void *key, const void *value)
{
	const int *ikey = (const int *)key;
	printf("%d ", *ikey);
	fflush(stdout);

	return true;
}

int comp_person(const void *key1, const void *key2)
{
	const int *ikey1 = (const int *)key1;
	const int *ikey2 = (const int *)key2;

	if (*ikey1 > *ikey2)
		return 1;

	if (*ikey1 < *ikey2)
		return -1;

	return 0;
}