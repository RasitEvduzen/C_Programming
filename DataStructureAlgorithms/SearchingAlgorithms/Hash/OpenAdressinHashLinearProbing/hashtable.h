#ifndef HASHTABLE_H_
#define HASHTABLE_H_

#include <stdbool.h>
#include <stddef.h>

/* Symbolic Constant*/
#define HASH_TABLE_SIZE 10
#define LOAD_FACTOR 0.75
#define HT_STATUS_EMPTY			0
#define HT_STATUS_INUSE			1
#define HT_STATUS_DELETED		2

/* Type Declerations */

typedef struct tagPERSON
{
    char name[32];
    int city;
    int no;

}PERSON;

typedef struct tagBUCKET{
    char key[32];
    PERSON value;
	int status;
}BUCKET;

typedef struct tagHTABLE
{
    BUCKET *ht;
    size_t tsize;
    size_t count;
    size_t load_factor;
}HASHTABLE,*HHASHTABLE;

/* Function Prototypes */
HHASHTABLE create_lf_htable(size_t tsize, double load_factor);
bool insert_htable(HHASHTABLE hhtable, const char *key,const PERSON *val);
bool update_htable(HHASHTABLE hhtable, const char *key,const PERSON *val);
bool remove_htable(HHASHTABLE hhtable, const char *key);
PERSON *find_htable(HHASHTABLE hhtable, const char *key);
void clear_htable(HHASHTABLE hhtable);
void destroy_htable(HHASHTABLE hhtable);
bool resize_htable(HHASHTABLE hhtable, size_t new_size);


/* Inline Function Definitions*/

static inline HHASHTABLE create_htable(size_t tsize)
{
    return create_lf_htable(tsize,LOAD_FACTOR);
}
static inline size_t count_htable(HHASHTABLE hhtable)
{
	return hhtable->count;
}

static inline size_t tsize_htable(HHASHTABLE hhtable)
{
	return hhtable->tsize;
}

#endif //HASHTABLE_H_