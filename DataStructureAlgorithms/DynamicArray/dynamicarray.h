#ifndef DYNAMICARRAY_H
#define DYNAMICARRAY_H

/* Symbolic Constants */

#define DARRAY_DEF_CAPACITY 8
#define DARRAY_FAILED  ((size_t)-1)

/* Type Declarations*/
typedef int DATATYPE;

typedef struct tagDARRAY{
    DATATYPE *darray;  // Dynamic Array Initial Address
    size_t capacity;
    size_t count;
}DARRAY, *HDARRAY;


/* Function Prototypes */

HDARRAY create_darray(void);
void destroy_darray(HDARRAY hdarray);
size_t add_darray(HDARRAY hdarray,DATATYPE val);
size_t addp_darray(HDARRAY hdarray,const DATATYPE *val);
size_t multi_add_darray(HDARRAY hdarray, const DATATYPE *vals, size_t size);
size_t insert_darray(HDARRAY hdarray, size_t index, DATATYPE val);
size_t insertp_darray(HDARRAY hdarray, size_t index, const DATATYPE *val);
size_t remove_darray(HDARRAY hdarray, size_t index);
void print_darray(HDARRAY hdarray);
size_t reserve_darray(HDARRAY hdarray, size_t newcap);


/* Inline Function Definitions */

static inline size_t capacity_darray(HDARRAY hdarray)
{ 
    return hdarray->capacity;
}

static inline size_t count_darray(HDARRAY hdarray)
{
    return hdarray->count;
}

static inline DATATYPE get_darray(HDARRAY hdarray, size_t index)
{
    return hdarray->darray[index];
}

static inline void set_darray(HDARRAY hdarray, size_t index, DATATYPE val)
{
    hdarray->darray[index] = val;
}

static inline void setp_darray(HDARRAY hdarray, size_t index, DATATYPE *val)
{
    hdarray->darray[index] = *val;
}

static inline void clear_darray(HDARRAY hdarray)
{
    hdarray->count = 0;
}


#endif //DYNAMICARRAY_H