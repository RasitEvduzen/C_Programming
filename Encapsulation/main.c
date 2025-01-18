#include <stdio.h>
#include <stdlib.h>
#include "opaque.h"


int main(void)
{
    POpaquePointer pOpaquePointer = CreateOpaquePointer();
    if(!pOpaquePointer)
        fprintf(stderr, "Failed to create opaque pointer\n");
    else
    {
        DoSomethingWithOpaquePointer(pOpaquePointer);
        DestroyOpaquePointer(pOpaquePointer);
    }

    return 0;
}
