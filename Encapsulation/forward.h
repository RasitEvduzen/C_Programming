#ifndef FORWARD_H_
#define FORWARD_H_

#include <stdio.h>
#include <stdlib.h>

// This is a pointer to an opaque structure. This is a (forward declaration-Cpp) ~ (Incompleta decleration-C). 
// This means that the structure is defined in the implementation file, 
// and the client code does not have access to the structure's members.
typedef struct tagUserType UserType, *PUserType;


// These functions are the only way to interact with the opaque structure.
PUserType CreateUserType(void);
void DestroyUserType(PUserType pUserType);
void DoSomethingWithUserType(PUserType pUserType);

#endif // FORWARD_H_