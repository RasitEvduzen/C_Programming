#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "hashtable.h"

void get_random_record(char *key, PERSON *per);

int main(void)
{
	HHASHTABLE hhtable;
	char name[32];
	PERSON per, *pper;
	PERSON specific_per = {"Rasit Evduzen", 35, 123456};
	srand((unsigned)time(NULL));

	if ((hhtable = create_htable(HASH_TABLE_SIZE)) == NULL) {
		fprintf(stderr, "Cannot Allocate Memory!..\n");
		exit(EXIT_FAILURE);
	}

	for (int i = 0; i < 1000; ++i) {
		if (i == 500) {
			if (!insert_htable(hhtable, "Rasit Evduzen", &specific_per)) {
				fprintf(stderr, "Cannot Insert Item!..\n");
				exit(EXIT_FAILURE);
			}
		} 
		else  {
			get_random_record(name, &per);
			if (!insert_htable(hhtable, name, &per)) {
				fprintf(stderr, "Cannot Insert Item!..\n");
				exit(EXIT_FAILURE);
			}
		}
	}

	if (remove_htable(hhtable, "Rasit Evduzen"))
		printf("Item Removed...\n");
	else
		printf("Cannot Remove Item!..\n");

	if ((pper = find_htable(hhtable, "Rasit Evduzen")) != NULL) 
		printf("Found: %s %d %d\n", pper->name, pper->city, pper->no);
	else 
		printf("Cannot Find Record!..\n");
	destroy_htable(hhtable);
	return 0;
}

void get_random_record(char *key, PERSON *per)
{
	int i;

	for (i = 0; i < 31; ++i)
		key[i] = per->name[i] = rand() % 26 + 'A';
	per->name[i] = key[i] = '\0';

	per->city = rand() % 81;
	per->no = rand() % 1000000;
}

