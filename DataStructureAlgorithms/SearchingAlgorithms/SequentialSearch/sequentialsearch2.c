#include <stdio.h>
#include <stdlib.h>

typedef int DATATYPE;

#define size_array(x)    (sizeof(x)/sizeof(*x))


DATATYPE *linear_search(DATATYPE *array, size_t size, DATATYPE val)
{
    size_t i;
    array[size] = val;
    for(i = 0;; ++i)
        if(array[i] == val)
            break;
    return i != size ? &array[i] : NULL;
}

void print_array(const DATATYPE *array, size_t size){
    for(size_t i = 0; i < size; ++i)
        printf("%d ",array[i]);
    putchar('\n');
}

int main(void)
{
    DATATYPE array[] = {1,98,23,55,67,35,22,54,88,11,0};
    DATATYPE val;
    DATATYPE *ret_val;
    print_array(array,size_array(array));

    printf("Give a Number!\n");
    scanf("%d",&val);

    if(!(ret_val = linear_search(array,size_array(array),val))){
        fprintf(stderr,"Cannot Find %d Element in Array!\n",val);
        exit(EXIT_FAILURE);
    }
    else
        printf("idx: %d\nvalue: %d\n",ret_val-array,*ret_val);

    return 0;
}