//
//  main.c
//  larger-number-adder
//
//  Created by Cheng FEI on 2022/10/19.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "Stack.h"
#include "List.h"

/* ********************************* */
/* Function Prototype                */
/* ********************************* */

// Add two large integers (larger than long type number)
// and output the result on the console.
void addLargeNumbers(const char *, const char *);

// Test Function.
// Test addLargerNumbers function
// with two numbers that are larger than can be stored in a long.
void testAddLargeNumbersWithLongerType(void);

/* ********************************* */
/* Main Function                     */
/* ********************************* */
int main(int argc, const char * argv[]) {
    // Test addLargeNumbers function and accept the test report.
    testAddLargeNumbersWithLongerType();
}
    
/* ********************************* */
/* Function Implementation           */
/* ********************************* */

// Add two large integers (larger than long type number)
// and output the result on the console.
// @Params: pNum1 -- constant char pointer with first number's digits.
// @Params: pNum2 -- constant char pointer with second number's digits.
// @Returns: void
// @Requires: ordering of characters in both pNum1 and pNum2 should be from MSB to LSB.
void addLargeNumbers(const char *pNum1, const char *pNum2) {
    // Step 0: Helper variables settings.
    Stack stackIn1, stackIn2, stackOut;
    stack_init(&stackIn1, free); // Initialize the stack stackIn1.
    stack_init(&stackIn2, free); // Initialize the stack stackIn2.
    stack_init(&stackOut, free); // Initialize the stack stackOut.
    int *pIntDigitIn1; // Dynamically allocate a new memory to store a pNum1 digit.
    int *pIntDigitIn2; // Dynamically allocate a new memory to store a pNum2 digit.
    int *pIntDigitOut; // Dynamically allocate a new memory to store a output digit.
    void *pVoidDigitIn1; // Helper pointer to accept the dynamic memory from stack_pop function.
    void *pVoidDigitIn2; // Helper pointer to accept the dynamic memory from stack_pop function.
    void *pVoidDigitOut; // Helper pointer to accept the dynamic memory from stack_pop function.
    int result; // Value in each output's digit after addition.
    int carry = 0; // Carry-out of each digit-wise addition.
    
    // Step 1: Pre-load numerals from pNum1 to the stack stackIn1 and from pNum2 to stackIn2.
    //         (Ordering: from MSB to LSM)
    for (int i = 0; i < strlen(pNum1); i++) {
        // Store the current digit into a dynamically allocated memory.
        if ((pIntDigitIn1 = (int *)malloc(sizeof(int))) == NULL) {
            // If out of memory.
            fprintf(stderr, "Out of memory!");
            stack_destroy(&stackIn1); // Free any previously allocated dynamic memory.
            exit(EXIT_FAILURE); // Exit the program completely.
        }
        // If successfully allocated, pDigitIn1 accepts the current digit (int).
        *pIntDigitIn1 = pNum1[i] - '0'; // Change the character to the corresponding digit.
        
        // Push the current digit onto the stack stackIn1.
        if (stack_push(&stackIn1, pIntDigitIn1) != 0) {
            // If out of memory.
            fprintf(stderr, "Out of memory!"); // Alert message to the user.
            free(pIntDigitIn1); // Free the newly allocated dynamic memory.
            stack_destroy(&stackIn1); // Free any previously allocated dynamic memory.
            exit(EXIT_FAILURE); // Exit the program completely.
        }
    }
    for (int i = 0; i < strlen(pNum2); i++) {
        // Store the current digit into a dynamically allocated memory.
        if ((pIntDigitIn2 = (int *)malloc(sizeof(int))) == NULL) {
            // If out of memory.
            fprintf(stderr, "Out of memory!");
            stack_destroy(&stackIn1); // Free any previously allocated dynamic memory.
            stack_destroy(&stackIn2); // Free any previously allocated dynamic memory.
            exit(EXIT_FAILURE); // Exit the program completely.
        }
        // If successfully allocated, pDigitIn1 accepts the current digit (int).
        *pIntDigitIn2 = pNum2[i] - '0'; // Change the character to the corresponding digit.
        
        // Push the current digit onto the stack stackIn1.
        if (stack_push(&stackIn2, pIntDigitIn2) != 0) {
            // If out of memory.
            fprintf(stderr, "Out of memory!");
            free(pIntDigitIn2); // Free the newly allocated dynamic memory.
            stack_destroy(&stackIn1); // Free any previously allocated dynamic memory.
            stack_destroy(&stackIn2); // Free any previously allocated dynamic memory.
            exit(EXIT_FAILURE); // Exit the program completely.
        }
    }
    
    
    // Step 2: Add up numerals digit by digit and store results in the stack stackOut.
    //         (Ordering: from LSB to MSB)
    // Case 1: Both stacks (stackIn1, stackIn2) are non-empty.
    while (0!=stack_size(&stackIn1) && 0!=stack_size(&stackIn2)) {
        if ((pIntDigitOut = (int *)malloc(sizeof(int))) == NULL) {
            // If out of memory.
            fprintf(stderr, "Out of memory!");
            stack_destroy(&stackIn1); // Free any previously allocated dynamic memory.
            stack_destroy(&stackIn2); // Free any previously allocated dynamic memory.
            stack_destroy(&stackOut); // Free any previously allocated dynamic memory.
            exit(EXIT_FAILURE); // Exit the program completely.
        }
        // If successfully allocated, calculate the addition result and update the carry-out.
        stack_pop(&stackIn1, &pVoidDigitIn1); // Accept pointer to stackIn1's current digit.
        stack_pop(&stackIn2, &pVoidDigitIn2); // Accept pointer to stackIn1's current digit.
        pIntDigitIn1 = (int *) pVoidDigitIn1; // Unbox the integer pointed at.
        pIntDigitIn2 = (int *) pVoidDigitIn2; // Unbox the integer pointed at.
        result = carry + *pIntDigitIn1 + *pIntDigitIn2;
        carry = result / 10;
        result %= 10;
        free(pIntDigitIn1); // Free the retrieved dynamic memory.
        free(pIntDigitIn2); // Free the retrieved dynamic memory.
        // Store the result into a dynamically allocated memory.
        *pIntDigitOut = result;
        // Push the current digit onto the stack stackIn1.
        if (stack_push(&stackOut, pIntDigitOut) != 0) {
            // If out of memory.
            fprintf(stderr, "Out of memory!");
            free(pIntDigitOut); // Free the newly allocated dynamic memory.
            stack_destroy(&stackIn1); // Free any previously allocated dynamic memory.
            stack_destroy(&stackIn2); // Free any previously allocated dynamic memory.
            stack_destroy(&stackOut); // Free any previously allocated dynamic memory.
            exit(EXIT_FAILURE); // Exit the program completely.
        }
    }
    
    // Case 2: Either stackIn1 or stackIn2 is non-empty.
    //    2.1: stackIn1 is non-empty.
    while (0!=stack_size(&stackIn1)) {
        if ((pIntDigitOut = (int *)malloc(sizeof(int))) == NULL) {
            // If out of memory.
            fprintf(stderr, "Out of memory!");
            stack_destroy(&stackIn1); // Free any previously allocated dynamic memory.
            stack_destroy(&stackIn2); // Free any previously allocated dynamic memory.
            stack_destroy(&stackOut); // Free any previously allocated dynamic memory.
            exit(EXIT_FAILURE); // Exit the program completely.
        }
        // If successfully allocated, calculate the addition result and update the carry-out.
        stack_pop(&stackIn1, &pVoidDigitIn1); // Accept pointer to stackIn1's current digit.
        pIntDigitIn1 = (int *) pVoidDigitIn1; // Unbox the integer pointed at.
        result = carry + *pIntDigitIn1;
        carry = result / 10;
        result %= 10;
        free(pIntDigitIn1); // Free the retrieved dynamic memory.
        // Store the result into a dynamically allocated memory.
        *pIntDigitOut = result;
        // Push the current digit onto the stack stackIn1.
        if (stack_push(&stackOut, pIntDigitOut) != 0) {
            // If out of memory.
            fprintf(stderr, "Out of memory!");
            free(pIntDigitOut); // Free the newly allocated dynamic memory.
            stack_destroy(&stackIn1); // Free any previously allocated dynamic memory.
            stack_destroy(&stackIn2); // Free any previously allocated dynamic memory.
            stack_destroy(&stackOut); // Free any previously allocated dynamic memory.
            exit(EXIT_FAILURE); // Exit the program completely.
        }
    }
    
    //    2.2: stackIn2 is non-empty.
    while (0!=stack_size(&stackIn2)) {
        if ((pIntDigitOut = (int *)malloc(sizeof(int))) == NULL) {
            // If out of memory.
            fprintf(stderr, "Out of memory!");
            stack_destroy(&stackIn1); // Free any previously allocated dynamic memory.
            stack_destroy(&stackIn2); // Free any previously allocated dynamic memory.
            stack_destroy(&stackOut); // Free any previously allocated dynamic memory.
            exit(EXIT_FAILURE); // Exit the program completely.
        }
        // If successfully allocated, calculate the addition result and update the carry-out.
        stack_pop(&stackIn2, &pVoidDigitIn2); // Accept pointer to stackIn2's current digit.
        pIntDigitIn2 = (int *) pVoidDigitIn2; // Unbox the integer pointed at.
        result = carry + *pIntDigitIn2;
        carry = result / 10;
        result %= 10;
        free(pIntDigitIn2); // Free the retrieved dynamic memory.
        // Store the result into a dynamically allocated memory.
        *pIntDigitOut = result;
        // Push the current digit onto the stack stackIn1.
        if (stack_push(&stackOut, pIntDigitOut) != 0) {
            // If out of memory.
            fprintf(stderr, "Out of memory!");
            free(pIntDigitOut); // Free the newly allocated dynamic memory.
            stack_destroy(&stackIn1); // Free any previously allocated dynamic memory.
            stack_destroy(&stackIn2); // Free any previously allocated dynamic memory.
            stack_destroy(&stackOut); // Free any previously allocated dynamic memory.
            exit(EXIT_FAILURE); // Exit the program completely.
        }
    }
    
    // Case 3: Both stacks (stackIn1, stackIn2) are empty,
    //         but the carry is not zero.
    if (0 != carry) {
        if ((pIntDigitOut = (int *)malloc(sizeof(int))) == NULL) {
            // If out of memory.
            fprintf(stderr, "Out of memory!");
            stack_destroy(&stackIn1); // Free any previously allocated dynamic memory.
            stack_destroy(&stackIn2); // Free any previously allocated dynamic memory.
            stack_destroy(&stackOut); // Free any previously allocated dynamic memory.
            exit(EXIT_FAILURE); // Exit the program completely.
        }
        // Store the result into a dynamically allocated memory.
        *pIntDigitOut = carry;
        // Push the current digit onto the stack stackIn1.
        if (stack_push(&stackOut, pIntDigitOut) != 0) {
            // If out of memory.
            fprintf(stderr, "Out of memory!");
            free(pIntDigitOut); // Free the newly allocated dynamic memory.
            stack_destroy(&stackIn1); // Free any previously allocated dynamic memory.
            stack_destroy(&stackIn2); // Free any previously allocated dynamic memory.
            stack_destroy(&stackOut); // Free any previously allocated dynamic memory.
            exit(EXIT_FAILURE); // Exit the program completely.
        }
    }
    
    // Step 3: Pop digits from the stack stackOut and display on the console.
    //         (Ordering: from MSB to LSB)
    while (0 != stack_size(&stackOut)) {
        stack_pop(&stackOut, &pVoidDigitOut); // Accept pointer to stackOut's current digit.
        pIntDigitOut = (int *)pVoidDigitOut; // Unbox the integer pointed at.
        printf("%d", *pIntDigitOut);
        free(pIntDigitOut); // Free the retrieved dynamic memory.
    }
    
    // Step final: Free all the memories occupied by stacks stackIn1, stackIn2, stackOut.
    stack_destroy(&stackIn1);
    stack_destroy(&stackIn2);
    stack_destroy(&stackOut);
}

// Test Function.
// Test addLargerNumbers function
// with two numbers that are larger than can be stored in a long (+9,223,372,036,854,775,807).
// Output all tests' results on the console.
void testAddLargeNumbersWithLongerType() {
    // Test case 1:
    char *pNum11 = "9223372036854775810";
    char *pNum12 = "29223372036854775810";
    printf("Adding %s and %s...done!\n", pNum11, pNum12);
    printf("----------------------------------------------------------------------------\n");
    printf("Expected result: 38446744073709551620\n");
    printf("Computed result: ");
    // Print the calculation result by the adding function.
    addLargeNumbers(pNum11, pNum12);
    printf("\n\n");
    
    // Test case 2:
    char *pNum21 = "1009223235543645754775810";
    char *pNum22 = "42364826782642634742354235";
    printf("Adding %s and %s...done!\n", pNum21, pNum22);
    printf("----------------------------------------------------------------------------\n");
    printf("Expected result: 43374050018186280497130045\n");
    printf("Computed result: ");
    // Print the calculation result by the adding function.
    addLargeNumbers(pNum21, pNum22);
    printf("\n\n");

    // Test case 3:
    char *pNum31 = "14961647923472357543754635";
    char *pNum32 = "31963747324735673472364741";
    printf("Adding %s and %s...done!\n", pNum31, pNum32);
    printf("----------------------------------------------------------------------------\n");
    printf("Expected result: 46925395248208031016119376\n");
    printf("Computed result: ");
    // Print the calculation result by the adding function.
    addLargeNumbers(pNum31, pNum32);
    printf("\n\n");
    
    // Test case 4:
    char *pNum41 = "14961647973981836161674537154365424535395432542554567523472357543754635";
    char *pNum42 = "31963747324708086165746375435685479676757381230943635754335673472364741";
    printf("Adding %s and %s...done!\n", pNum41, pNum42);
    printf("----------------------------------------------------------------------------\n");
    printf("Expected result: 46925395298689922327420912590050904212152813773498203277808031016119376\n");
    printf("Computed result: ");
    // Print the calculation result by the adding function.
    addLargeNumbers(pNum41, pNum42);
    printf("\n\n");
}
