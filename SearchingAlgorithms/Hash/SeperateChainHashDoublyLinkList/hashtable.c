#include <stdlib.h>
#include <string.h>
#include "hashtable.h"

static size_t hash_function(const char *str, size_t tsize);


HHASTABLE create_lf_htable(size_t tsize, double load_factor)
{
    HHASTABLE hhtable;
    if((hhtable = (HHASTABLE)malloc(sizeof(HHASTABLE))) == NULL)
        return NULL;
    if((hhtable->table = (NODE**)malloc(sizeof(NODE*) * tsize)) == NULL){
        free(hhtable);
        return NULL;
    }
    for(size_t i = 0; i < tsize; ++i)
        hhtable->table[i] = NULL;
    hhtable->count = 0;
    hhtable->tsize = tsize;
    hhtable->load_factor = load_factor;
    return hhtable;
}

NODE *insert_htable(HHASTABLE hhtable, const char *key,const PERSON *val)
{
    NODE *new_node;
    size_t hash;
    hash = hash_function(key,hhtable->tsize);
    for(NODE *node = hhtable->table[hash]; node; node = node->next)
        if(!strcmp(key,node->key))
            return NULL;
    if((hhtable->count / hhtable->tsize) >= hhtable->load_factor)
        if(!resize_htable(hhtable,hhtable->tsize * 2))
            return NULL;
    if((new_node = (NODE*)malloc(sizeof(NODE))) == NULL)
        return NULL;
    new_node->prev = NULL;
    new_node->value = *val;
    strcpy(new_node->key,key);
    new_node->next = hhtable->table[hash];
    if(hhtable->table[hash])
        hhtable->table[hash]->prev = new_node;
    hhtable->table[hash] = new_node;
    ++hhtable->count;
    return new_node;
}

NODE *update_htable(HHASTABLE hhtable, const char *key,const PERSON *val)
{
    NODE *new_node;
    size_t hash;
    hash = hash_function(key,hhtable->tsize);
    for(NODE *node = hhtable->table[hash]; node; node = node->next)
        if(!strcmp(key,node->key)){
            node->value = *val;
            return node;
        }
    if((double)(hhtable->count / hhtable->tsize) >= hhtable->load_factor)
        if(!resize_htable(hhtable,hhtable->tsize * 2))
            return NULL;
    if((new_node = (NODE*)malloc(sizeof(NODE))) == NULL)
        return NULL;
    new_node->prev = NULL;
    new_node->value = *val;
    strcpy(new_node->key,key);
    new_node->next = hhtable->table[hash];
    if(hhtable->table[hash])
        hhtable->table[hash]->prev = new_node;
    hhtable->table[hash] = new_node;
    ++hhtable->count;
    return new_node;
}

PERSON *find_htable(HHASTABLE hhtable, const char *key)
{
    size_t hash = hash_function(key,hhtable->tsize);
    for(NODE *node = hhtable->table[hash]; node; node = node->next)
        if(!strcmp(key,node->key))
            return &node->value;
    return NULL;
}

void clear_htable(HHASTABLE hhtable)
{
    NODE *node, *temp_node;
    for(size_t i = 0; i < hhtable->tsize; ++i){
        node = hhtable->table[i];
        while (node){
            temp_node = node->next;
            free(node);
            node = temp_node;
        }
        hhtable->table[i] = NULL;
    }
    hhtable->count = 0;
}

bool remove_htable(HHASTABLE hhtable, const char *key)
{
    size_t hash = hash_function(key,hhtable->tsize);
    for(NODE *node = hhtable->table[hash]; node; node = node->next)
        if(!strcmp(key,node->key)){
            if(node->next) node->next->prev = node->prev;
            if(node->prev) node->prev->next = node->next;
            else hhtable->table[hash] = node->next;
            free(node);
            --hhtable->count;
            return true;
        }

}

bool resize_htable(HHASTABLE hhtable, size_t new_size)
{
    NODE **new_table;
    NODE *node, *temp_node;
    size_t hash;
    if(new_size <= hhtable->tsize)
        return false;
    if(!(new_table = (NODE **)malloc(new_size * sizeof(NODE*))))
        return false;
    for(size_t i = 0; i < new_size; ++i)
        new_table[i] = NULL;
	for (size_t i = 0; i < hhtable->tsize; ++i) {
		node = hhtable->table[i];
		while (node != NULL) {
			temp_node = node->next;
			hash = hash_func(node->key, new_size);
			node->next = new_table[hash];
			new_table[hash] = node;
			node = temp_node;
		}
	}
	free(hhtable->table);
	hhtable->table = new_table;
	hhtable->tsize = new_size;
	return true;
}

void destroy_htable(HHASTABLE hhtable)
{
    clear_htable(hhtable);
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

