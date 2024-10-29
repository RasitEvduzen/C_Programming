#ifndef HASHTABLE_H_
#define HASHTABLE_H_

#include <stddef.h>
#include <stdbool.h>

/* Symbolic Constants */

#define HASH_TABLE_SIZE 101
#define LOAD_FACTOR 0.75

/* Type Decleration */


typedef struct tagPERSON{
    char name[32];
    int city;
    int no;
}PERSON;

typedef struct tagNODE{
    char key[32];
    PERSON value;
    struct tagNODE *next;
    struct tagNODE *prev;    
}NODE;

typedef struct tagHASHTABLE{
    NODE **table;
    size_t tsize;
    size_t count;
    double load_factor;
}HASHTABLE,*HHASTABLE;

/* Function Prototypes */
HHASTABLE create_lf_htable(size_t tsize, double load_factor);
NODE *insert_htable(HHASTABLE hhtable, const char *key,const PERSON *val);
NODE *update_htable(HHASTABLE hhtable, const char *key,const PERSON *val);
PERSON *find_htable(HHASTABLE hhtable, const char *key);
bool remove_htable(HHASTABLE hhtable, const char *key);
bool resize_htable(HHASTABLE hhtable, size_t new_size);
void clear_htable(HHASTABLE hhtable);
void destroy_htable(HHASTABLE hhtable);

/* Inline Function Definitions */
static inline size_t count_htable(HHASTABLE hhtable)
{
    return hhtable->count;
}

static inline size_t htable_size(HHASTABLE hhtable)
{
    return hhtable->tsize;
}

static inline HHASTABLE create_htable(size_t tsize)
{
    return create_lf_htable(tsize,LOAD_FACTOR);
}

#endif