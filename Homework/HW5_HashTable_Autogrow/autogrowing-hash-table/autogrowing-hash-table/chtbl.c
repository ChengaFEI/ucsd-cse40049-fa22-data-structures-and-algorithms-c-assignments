//
//  chtbl.c
//  autogrowing-hash-table
//
//  Created by Cheng FEI on 2022/10/26.
//

#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "list.h"
#include "chtbl.h"

#define A (sqrt(5)-1)/2

int chtbl_init(CHTbl *htbl, int buckets, int(*h)(const void *key), int(*match)(
        const void *key1, const void *key2), void(*destroy)(void*data), double maxLoadFactor, double resizeMultiplier) {

    int i;

    /* Allocate space for the hash table. */
    if ((htbl->table = (List *) malloc(buckets * sizeof(List))) == NULL)
        return -1;

    /* Initialize the buckets. */
    htbl->buckets = buckets;

    for (i = 0; i < htbl->buckets; i++)
        list_init(&htbl->table[i], destroy);

    /* Encapsulate the functions. */
    htbl->h = h;
    htbl->match = match;
    htbl->destroy = destroy;

    /* Initialize the number of elements in the table. */
    htbl->size = 0;
    
    /* Initialize the resize flags. */
    htbl->maxLoadFactor = maxLoadFactor;
    htbl->resizeMultiplier = resizeMultiplier;

    return 0;
}

void chtbl_destroy(CHTbl *htbl) {

    int i;

    /* Destroy each bucket. */
    for (i = 0; i < htbl->buckets; i++) {
        list_destroy(&htbl->table[i]);
    }

    /* Free the storage allocated for the hash table. */
    free(htbl->table);

    /* No operations are allowed now, but clear the structure as a
     * precaution. */
    memset(htbl, 0, sizeof(CHTbl));
}

int chtbl_insert(CHTbl *htbl, const void *data) {

    void *temp;
    int bucket, retval;

    /* Do nothing if the data is already in the table. */
    temp = (void *) data;

    if (chtbl_lookup(htbl, &temp) == 0)
        return 1;
    
    /* Auto-grow the buckets when the load factor exceeds the maximum load factor. */
    if (1.0*(htbl->size + 1) / htbl->buckets >= htbl->maxLoadFactor) {
        chtbl_resize(htbl);
    }

    /* Hash the key. */
    bucket = floor(htbl->buckets * fmod(htbl->h(data)*A, 1.0));

    /* Insert the data into the bucket. */
    if ((retval = list_ins_next(&htbl->table[bucket], NULL, data)) == 0)
        htbl->size++;

    return retval;
}

int chtbl_remove(CHTbl *htbl, void **data) {

    ListElmt *element, *prev;
    int bucket;

    /* Hash the key. */
    bucket = floor(htbl->buckets * fmod(htbl->h(data)*A, 1.0));

    /* Search for the data in the bucket. */
    prev = NULL;

    for (element = list_head(&htbl->table[bucket]); element != NULL; element
            = list_next(element)) {

        if (htbl->match(*data, list_data(element))) {

            /* Remove the data from the bucket. */
            if (list_rem_next(&htbl->table[bucket], prev, data) == 0) {
                htbl->size--;
                return 0;
            }
            else {
                return -1;
            }
        }

        prev = element;
    }

    /* Return that the data was not found. */

    return -1;
}

int chtbl_lookup(const CHTbl *htbl, void **data) {

    ListElmt *element;
    int bucket;

    /* Hash the key. */
    bucket = floor(htbl->buckets * fmod(htbl->h(*data)*A, 1.0));

    /* Search for the data in the bucket. */
    for (element = list_head(&htbl->table[bucket]); element != NULL; element
            = list_next(element)) {

        if (htbl->match(*data, list_data(element))) {

            /* Pass back the data from the table. */
            *data = list_data(element);
            return 0;
        }
    }

    /* Return that the data was not found. */

    return -1;
}

int chtbl_resize(CHTbl *htbl) {
    List *table;
    ListElmt *listElmt;
    void * data;
    int newBucket;
    int newBuckets = htbl->buckets * htbl->resizeMultiplier;
    
    /* Allocate space for the hash table. */
    if ((table = (List *) malloc(sizeof(List) * newBuckets)) == NULL) {
        return -1;
    }
    
    for (int i = 0; i < newBuckets; i++) {
        list_init(&table[i], htbl->destroy);
    }

    /* Pass all elements stored in the old htbl into the new htbl. */
    for (int i = 0; i < htbl->buckets; i++) {
        for (listElmt = list_head(&htbl->table[i]); listElmt != NULL; listElmt = list_next(listElmt)) {
            data = listElmt->data;
            newBucket = floor(newBuckets * fmod(htbl->h(data) * A, 1.0));
            if (list_ins_next(&table[newBucket], NULL, data) != 0) {
                return -1;
            }
        }
    }
    
    list_destroy(htbl->table);
    htbl->table = table;

    htbl->buckets = newBuckets;
    
    return 0;
}
