#include <stdio.h>
#include <stdlib.h>
#include "forward.h"

typedef struct tagUserType{
    int x;
    int y;
    int z;
} UserType, *PUserType;

PUserType CreateUserType(void)
{
    PUserType Pusertype = (PUserType)malloc(sizeof(UserType));
    if (Pusertype)
    {
        Pusertype->x = 0;
        Pusertype->y = 0;
        Pusertype->z = 0;
    }
    return Pusertype;
}


void DestroyUserType(PUserType PUserType)
{
    if(PUserType) 
        free(PUserType);
}
void DoSomethingWithUserType(PUserType PUserType)
{
    if(PUserType)
        printf("x = %d\ny = %d\nz = %d\n", PUserType->x, PUserType->y, PUserType->z);
}
