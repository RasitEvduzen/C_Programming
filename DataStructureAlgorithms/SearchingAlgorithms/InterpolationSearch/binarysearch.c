#include <stdio.h>
#include <stdlib.h>

typedef int DATATYPE;
#define size_array(x)    (sizeof(x)/sizeof(*x))



const DATATYPE *interpolation_search(const DATATYPE *array, size_t size, DATATYPE val)
{
    size_t left = 0, right = size, mid;
    while (left <= right){
        mid = left + ((right - left) / (array[right] - array[left])) * (val - array[left]);
        if(val > array[mid]) left = mid + 1;
        else if (val < array[mid]) right = mid - 1;
        else return &array[mid];
    }
    return NULL;
}

void print_array(const DATATYPE *array, size_t size){
    for(size_t i = 0; i < size; ++i)
        printf("%d ",array[i]);
    putchar('\n');
}

int main(void)
{
    const DATATYPE array[] = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15};
    DATATYPE val;
    const DATATYPE *ret_val;
    print_array(array,size_array(array));

    printf("Give a Value:\n");
    scanf("%d",&val);

    if(!(ret_val = interpolation_search(array,size_array(array),val))){
        fprintf(stderr,"Cannot Find %d Element in Array!\n",val);
        exit(EXIT_FAILURE);
    }
    else
        printf("idx: %d\nvalue: %d\n",ret_val-array,*ret_val);

    return 0;
}
