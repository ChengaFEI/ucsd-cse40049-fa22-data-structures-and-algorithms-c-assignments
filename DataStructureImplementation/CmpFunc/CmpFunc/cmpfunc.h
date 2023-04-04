//
//  cmpfunc.h
//  CmpFunc
//
//  Implementation of Comparison Function.
//
//  Created by Cheng FEI on 2022/10/8.
//

#ifndef cmpfunc_h
#define cmpfunc_h


#endif /* cmpfunc_h */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NAME_LENGTH 256

// Employee structure with id (int) and name (char *).
typedef struct Employee_ {
    int id;
    char name[MAX_NAME_LENGTH];
} Employee;

// Compare two employees by id.
// Params: pKey1 -- pointer to void object with info of the first Empolyee object.
// Params: pKey2 -- pointer to void object with info of the second Employee object.
// Return: 0 -- if their id is equal.
//         1 -- if the first employee's id is larger than the second employee's id.
//         2 -- if the first employee's id is smaller than the second employee's id.
int compareById(const void *pKey1, const void *pKey2) {
    // Declare two empty Employee objects to receive value from arguments.
    Employee *pEmp1 = (Employee *) pKey1;
    Employee *pEmp2 = (Employee *) pKey2;
    if (pEmp1->id > pEmp2->id) return 1;
    if (pEmp1->id < pEmp2->id) return -1;
    return 0;
}

// Compare two employees by name.
// Params: pKey1 -- pointer to void object with info of the first Empolyee object.
// Params: pKey2 -- pointer to void object with info of the second Employee object.
// Return: 0 -- if their name is the same.
//         1 -- if the first employee's name comes after the second employee's name.
//         2 -- if the first employee's name comes before the second employee's name.
int compareByName(const void *pKey1, const void *pKey2) {
    // Declare two empty Employee objects to receive value from arguments.
    Employee *pEmp1 = (Employee *) pKey1;
    Employee *pEmp2 = (Employee *) pKey2;
    // Compare two employee's name by built-in strcmp function.
    int result = strcmp(pEmp1->name, pEmp2->name);
    if (result > 0) return 1;
    if (result < 0) return -1;
    return 0;
}
