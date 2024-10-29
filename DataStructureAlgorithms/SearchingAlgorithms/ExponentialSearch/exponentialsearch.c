#include <stdio.h>
#include <stdlib.h>

typedef int DATATYPE;
#define size_array(x)    (sizeof(x)/sizeof(*x))


const DATATYPE *binary_search(const DATATYPE *array, size_t size, DATATYPE val)
{
    size_t left, right, middle;
    left = 0, right = size - 1;
    while (left <= right){
        middle = (right + left) / 2;
        if(val > array[middle]) left = middle + 1;
        else if(val < array[middle]) right = middle - 1;
        else return &array[middle];
    }
    return NULL;
}

const DATATYPE *exponential_search(const DATATYPE *array, size_t size, DATATYPE val)
{
    size_t left, right = 1;
    if(array[0] == val)
        return &array[0];
    while (array[right] < val && right < size)
        right *= 2;
    left = right / 2;
    return binary_search(array + left, right - left + 1, val);
}


void print_array(const DATATYPE *array, size_t size){
    for(size_t i = 0; i < size; ++i)
        printf("%d ",array[i]);
    putchar('\n');
}

int main(void)
{
    const DATATYPE array[] = {1,3,6,9,11,17,23,28,36,41,48,54,61,67,72,78,82,86,90,92};
    DATATYPE val;
    const DATATYPE *ret_val;
    print_array(array,size_array(array));

    printf("Give a Value:\n");
    scanf("%d",&val);

    if(!(ret_val = exponential_search(array,size_array(array),val))){
        fprintf(stderr,"Cannot Find %d Element in Array!\n",val);
        exit(EXIT_FAILURE);
    }
    else
        printf("idx: %d\nvalue: %d\n",ret_val-array,*ret_val);

    return 0;
}
