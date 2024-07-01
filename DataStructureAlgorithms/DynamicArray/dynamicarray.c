#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "dynamicarray.h"

static int reallocate(HDARRAY hdarray, size_t newcapacity);

HDARRAY create_darray(void)
{
    HDARRAY hdarray;

    if((hdarray = (HDARRAY)malloc(sizeof(DARRAY))) == NULL)
        return NULL;

    if((hdarray->darray = (DATATYPE *)malloc(sizeof(DATATYPE) * DARRAY_DEF_CAPACITY)) == NULL)
    {
        free(hdarray);
        return NULL;
    }

    hdarray->capacity = DARRAY_DEF_CAPACITY;
    hdarray->count = 0;
    return hdarray;
}


void destroy_darray(HDARRAY hdarray)
{
    free(hdarray->darray);
    free(hdarray);
}

size_t add_darray(HDARRAY hdarray,DATATYPE val)
{
    if(hdarray->count == hdarray->capacity && reallocate(hdarray,hdarray->capacity * 2) == -1)
            return DARRAY_FAILED;
    
    hdarray->darray[hdarray->count++] = val;

    return hdarray->count - 1;
}

size_t addp_darray(HDARRAY hdarray,const DATATYPE *val)
{
    if(hdarray->count == hdarray->capacity && reallocate(hdarray,hdarray->capacity * 2) == -1)
            return DARRAY_FAILED;
    
    hdarray->darray[hdarray->count++] = *val;

    return hdarray->count - 1;    
}

size_t multi_add_darray(HDARRAY hdarray, const DATATYPE *vals, size_t size)
{
    if (hdarray->count + size > hdarray->capacity && reallocate(hdarray, hdarray->capacity * 2 + size) == -1)
        return DARRAY_FAILED;

	memmove(hdarray->darray + hdarray->count, vals, sizeof(DATATYPE) * size);
	hdarray->count += size;

	return hdarray->count - 1;
}

size_t insert_darray(HDARRAY hdarray, size_t index, DATATYPE val)
{
    if(index > hdarray->count)
        return DARRAY_FAILED;
        
    if(hdarray->count == hdarray->capacity && reallocate(hdarray,hdarray->capacity * 2) == -1)
        return DARRAY_FAILED;
    
    memmove(hdarray->darray + index + 1, hdarray->darray + index, sizeof(DATATYPE) * (hdarray->count - index));
    hdarray->darray[index] = val;
    ++hdarray->count;
    return index;
}

size_t insertp_darray(HDARRAY hdarray, size_t index, const DATATYPE *val)
{
    if(index > hdarray->count)
        return DARRAY_FAILED;
        
    if(hdarray->count == hdarray->capacity && reallocate(hdarray,hdarray->capacity * 2) == -1)
            return DARRAY_FAILED;
    
    memmove(hdarray->darray + index + 1, hdarray->darray + index, sizeof(DATATYPE) * (hdarray->count - index));
    hdarray->darray[index] = *val;
    ++hdarray->count;
    return index;
}

size_t remove_darray(HDARRAY hdarray, size_t index)
{
    if(index >= hdarray->count)
        return DARRAY_FAILED;
    
    memmove(hdarray->darray + index, hdarray->darray + index + 1, sizeof(DATATYPE) * (hdarray->count - index - 1));
    --hdarray->count;
    return index;
}

size_t reserve_darray(HDARRAY hdarray, size_t newcap)
{
    if(newcap < hdarray->capacity)
        return 0;

    if(reallocate(hdarray,newcap) == -1)
        return 0;
    return newcap;
}

static int reallocate(HDARRAY hdarray, size_t newcapacity)
{
    DATATYPE *new_darray;
    if((new_darray = (DATATYPE *)realloc(hdarray->darray,sizeof(DATATYPE) * newcapacity)) == NULL)
        return -1;

    hdarray->darray = new_darray;
    hdarray->capacity = newcapacity;
    return 0;
}

void print_darray(HDARRAY hdarray)
{
    for(int i = 0; i < count_darray(hdarray); ++i)
        printf("Idx: %d Value: %d \n",i,get_darray(hdarray,i));
}