#include <stdio.h>
#include <stdlib.h>
#include "opaque.h"

typedef struct tagOpaquePointer{
    int x;
    int y;
    int z;
} OpaquePointer, *POpaquePointer;

POpaquePointer CreateOpaquePointer(void)
{
    POpaquePointer pOpaquePointer = (POpaquePointer)malloc(sizeof(OpaquePointer));
    if (pOpaquePointer)
    {
        pOpaquePointer->x = 0;
        pOpaquePointer->y = 0;
        pOpaquePointer->z = 0;
    }
    return pOpaquePointer;
}


void DestroyOpaquePointer(POpaquePointer pOpaquePointer)
{
    if(pOpaquePointer) 
        free(pOpaquePointer);
}
void DoSomethingWithOpaquePointer(POpaquePointer pOpaquePointer)
{
    if(pOpaquePointer)
        printf("x = %d\ny = %d\nz = %d\n", pOpaquePointer->x, pOpaquePointer->y, pOpaquePointer->z);
}
