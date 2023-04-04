//
//  main.c
//  CmpFunc
//
//  Created by Cheng FEI on 2022/10/8.
//

#include <stdio.h>
#include "cmpfunc.h"

int main(int argc, const char * argv[]) {
    // Initialize two Employee objects.
    Employee emp1 = {1, "Ray"};
    Employee emp2 = {2, "Joe"};
    // Declare a pointer to function variable to point at different comparison functions in different tasks.
    int (* compare) (const void *, const void *);
    
    // Task 1: compare employees by id.
    compare = compareById;
    printf("Compare by Id = %d\n", compare(&emp1, &emp2));
    printf("Compare by Id = %d\n", compare(&emp1, &emp1));
    
    // Task 2: compare employees by name.
    compare = compareByName;
    printf("Compare by Name = %d\n", compare(&emp1, &emp2));
    printf("Compare by Name = %d\n", compare(&emp1, &emp1));
    
    return EXIT_SUCCESS;
}
