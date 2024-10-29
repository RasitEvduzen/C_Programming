#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "hashtable.h"

static size_t hash_function(const char *str, size_t tsize);


HHASHTABLE create_lf_htable(size_t tsize, double load_factor)
{
    HHASHTABLE hhtable;

    if(!(hhtable = (HHASHTABLE)malloc(sizeof(HASHTABLE))))
        return NULL;

    if(!(hhtable->ht = (BUCKET *)malloc(tsize * sizeof(BUCKET)))){
        free(hhtable);
        return NULL;
    }
	for (size_t i = 0; i < tsize; ++i)
		hhtable->ht[i].status = HT_STATUS_EMPTY;
    hhtable->tsize = tsize;
    hhtable->load_factor = load_factor;
    hhtable->count = 0;
    return hhtable;
}

bool insert_htable(HHASHTABLE hhtable, const char *key,const PERSON *val)
{
    size_t index;
    index = hash_function(key,hhtable->tsize);
    if (hhtable->count >= hhtable->tsize)
		return false;
    if (((double)hhtable->count / hhtable->tsize) >= hhtable->load_factor)
		if (!resize_htable(hhtable, hhtable->tsize * 2))
			return false;
	index = hash_function(key, hhtable->tsize);
	while (hhtable->ht[index].status != HT_STATUS_EMPTY) {
		if (!strcmp(hhtable->ht[index].key, key))
			return false;
		index = (index + 1) % hhtable->tsize;
	}
	strcpy(hhtable->ht[index].key, key);
	hhtable->ht[index].value = *val;
	hhtable->ht[index].status = HT_STATUS_INUSE;
	++hhtable->count;
	return true;
}
bool update_htable(HHASHTABLE hhtable, const char *key,const PERSON *val)
{
	size_t index;
	if (hhtable->count >= hhtable->tsize)
		return false;
	if (((double)hhtable->count / hhtable->tsize) >= hhtable->load_factor)
		if (!resize_htable(hhtable, hhtable->tsize * 2))
			return false;
	index = hash_function(key, hhtable->tsize);
	while (hhtable->ht[index].status != HT_STATUS_EMPTY) {
		if (!strcmp(hhtable->ht[index].key, key)) {
			hhtable->ht[index].value = *val;
			return true;
		}
		index = (index + 1) % hhtable->tsize;
	}
	strcpy(hhtable->ht[index].key, key);
	hhtable->ht[index].value = *val;
	hhtable->ht[index].status = HT_STATUS_INUSE;
	++hhtable->count;
	return true;
}

bool remove_htable(HHASHTABLE hhtable, const char *key)
{
	size_t index, hash;
	hash = index = hash_function(key, hhtable->tsize);
	do {
		if (hhtable->ht[index].status == HT_STATUS_EMPTY)
			break;
		if (hhtable->ht[index].status == HT_STATUS_INUSE && !strcmp(hhtable->ht[index].key, key)) {
			hhtable->ht[index].status = HT_STATUS_DELETED;
			--hhtable->count;
			return true;
		}
		index = (index + 1) % hhtable->tsize;
	} while (index != hash);
	return false;
}

PERSON *find_htable(HHASHTABLE hhtable, const char *key)
{
	size_t index, hash;
	hash = index = hash_function(key, hhtable->tsize);
	do {
		if (hhtable->ht[index].status == HT_STATUS_EMPTY)
			break;
		if (hhtable->ht[index].status == HT_STATUS_INUSE && !strcmp(hhtable->ht[index].key, key))
			return &hhtable->ht[index].value;
		index = (index + 1) % hhtable->tsize; 
	} while (index != hash);
	return NULL;
}

bool resize_htable(HHASHTABLE hhtable, size_t new_size)
{
	BUCKET *new_ht;
	size_t index;
	if (new_size <= hhtable->tsize)
		return false;
	if ((new_ht = (BUCKET *)malloc(new_size * sizeof(BUCKET))) == NULL)
		return false;
	for (size_t i = 0; i < new_size; ++i)
		new_ht[i].status = HT_STATUS_EMPTY;
	for (size_t i = 0; i < hhtable->tsize; ++i) {
		if (hhtable->ht[i].status == HT_STATUS_INUSE) {
			index = hash_function(hhtable->ht[i].key, new_size);
			while (new_ht[index].status != HT_STATUS_EMPTY)
				index = (index + 1) % new_size;
			new_ht[index] = hhtable->ht[i];
		}
	}
	free(hhtable->ht);
	hhtable->ht = new_ht;
	hhtable->tsize = new_size;
	return true;
}

void clear_htable(HHASHTABLE hhtable)
{
	for (size_t i = 0; i < hhtable->tsize; ++i)
		hhtable->ht[i].status = HT_STATUS_EMPTY;

	hhtable->count = 0;
}

void destroy_htable(HHASHTABLE hhtable)
{
	free(hhtable->ht);
	free(hhtable);
}

static size_t hash_function(const char *str, size_t tsize)
{
    size_t hash = 0;
    while (*str){
        hash = (13 * hash + *str) % tsize;
        ++str;
    }
    return hash;
}
