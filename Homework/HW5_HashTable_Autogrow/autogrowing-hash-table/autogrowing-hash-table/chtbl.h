//
//  chtbl.h
//  autogrowing-hash-table
//
//  Created by Cheng FEI on 2022/10/26.
//

#ifndef CHTBL_H
#define CHTBL_H

#include <stdlib.h>

#include "list.h"

/* Define a structure for chained hash tables. */
typedef struct CHTbl_ {

    int buckets;

    int (*h)(const void *key);
    int (*match)(const void *key1, const void *key2);
    void (*destroy)(void *data);

    int size;
    List *table;
    
    double maxLoadFactor;
    double resizeMultiplier;

} CHTbl;

/* Public Interface */
int chtbl_init(CHTbl *htbl, int buckets, int(*h)(const void *key), int(*match)(
        const void *key1, const void *key2), void(*destroy)(void *data), double maxLoadFactor, double resizeMultiplier);

void chtbl_destroy(CHTbl *htbl);

int chtbl_insert(CHTbl *htbl, const void *data);

int chtbl_remove(CHTbl *htbl, void **data);

int chtbl_lookup(const CHTbl *htbl, void **data);

int chtbl_resize(CHTbl *htbl);

#define chtbl_size(htbl) ((htbl)->size)

#endif
