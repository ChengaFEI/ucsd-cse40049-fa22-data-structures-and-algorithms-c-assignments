//
//  main.c
//  autogrowing-hash-table
//
//  Created by Cheng FEI on 2022/10/26.
//

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "list.h"
#include "chtbl.h"

int hash(const void *key);
int match(const void *key1, const void *key2);

int main(int argc, const char * argv[]) {
    /* Initialize the htbl. */
    CHTbl htbl;
    chtbl_init(&htbl, 5, &hash, &match, NULL, 0.5, 2.0);
    int nums[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    int *exist = nums+9;
    int *notExist = (int *) malloc(sizeof(int));
    *notExist = 100;
    int found = 0;

    /* Insert elements and output the statistics of the htbl. */
    for (int i = 0; i < 10; i++) {
        chtbl_insert(&htbl, &nums[i]);
        printf("buckets %d, elements %d, lf %.2f, max lf %.1f, resize multiplier %.1f\n", htbl.buckets, htbl.size, 1.0*htbl.size / htbl.buckets, htbl.maxLoadFactor, htbl.resizeMultiplier);
    }
    
    /* Look up values. */
    found = chtbl_lookup(&htbl, (void *) &exist);
    if (0 == found) {
        printf("The value %d has been successfully inserted!\n", *exist);
    }
    else printf("The value %d has not been inserted at all!\n", *exist);
    found = chtbl_lookup(&htbl, (void *) &notExist);
    if (0 == found) {
        printf("The value %d has been successfully inserted!\n", *notExist);
    }
    else printf("The value %d has not been inserted at all!\n", *notExist);
    

    /* Destroy the htbl. */
    chtbl_destroy(&htbl);
    free(notExist);

    return 0;
}

// Hash an integer.
int hash(const void *key) {
    return *(int *)key;
}

// Verify whether two elements are identical.
int match(const void *key1, const void *key2) {
    return *(int *)key1 == *(int *)key2;
}
