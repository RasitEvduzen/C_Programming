#include <stdio.h>
#include <stdlib.h>
#include "forward.h"


int main(void)
{
    PUserType pUserType = CreateUserType();
    if(!pUserType)
        fprintf(stderr, "Failed to create opaque pointer\n");
    else
    {
        DoSomethingWithUserType(pUserType);
        DestroyUserType(pUserType);
    }

    return 0;
}
