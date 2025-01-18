#ifndef OPAQUE_H_
#define OPAQUE_H_

#include <stdio.h>
#include <stdlib.h>

// This is a pointer to an opaque structure. This is a (forward declaration-Cpp) ~ (Incompleta decleration-C). 
// This means that the structure is defined in the implementation file, 
// and the client code does not have access to the structure's members.
typedef struct tagOpaquePointer OpaquePointer, *POpaquePointer;


// These functions are the only way to interact with the opaque structure.
POpaquePointer CreateOpaquePointer(void);
void DestroyOpaquePointer(POpaquePointer pOpaquePointer);
void DoSomethingWithOpaquePointer(POpaquePointer pOpaquePointer);

#endif // OPAQUE_H_