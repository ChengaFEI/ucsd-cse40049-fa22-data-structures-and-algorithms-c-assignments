//
//  list.h
//  ListImpl
//
//  Created by Cheng FEI on 2022/10/2.
//

#ifndef LIST_H
#define LIST_H

#include <stdlib.h>

/*
 List element structure in list.
 */
typedef struct ListElmt_ {
    // Data included in element.
    void *data;
    // Next ListElmt it points at.
    struct ListElmt_ *next;
} ListElmt;

/*
 Singly linked list structure.
 */
typedef struct List_ {
    // Number of elements in list.
    int size;
    // Pointer points at the first element of list.
    ListElmt *head;
    // Pointer points at the last element of list.
    ListElmt *tail;
    // Pointer points at the match function.
    int (*match)(const void *key1, const void *key2);
    // Pointer points at the destroy function.
    // The function cleans up dynamical memory of data variable.
    void (*destroy)(void *data);
} List;

/*
 Public interfaces of list structure.
 */

/*
 Constructor of list structure.
 */
void list_init(List *list, void (*destroy)(void *data));

/*
 Destructor of list structure.
 */
void list_destroy(List *list);

/*
 Insert value as an element in list structure.
 Params: list -- list structure in which new data is inserted.
 Params: element -- list element after which new data is inserted.
 Params: data -- new data to be inserted.
 Returns: status code indicating operation succeeds or fails.
 */
int list_ins_next(List *list, ListElmt *element, const void *data);

/*
 Delete an element from list structure.
 Params: list -- list structure from which data is removed.
 Params: element -- list element structure after which data is removed.
 Params: data -- pointer which keeps the void *data property of removed list element.
 Returns: status code indicating operation succeeds or fails.
 */
int list_rem_next(List *list, ListElmt *element, void **data);

#define list_size(list) ((list)->size)
#define list_head(list) ((list)->head)
#define list_tail(list) ((list)->tail)
#define list_is_head(list, element) ((element) == (list)->head ? 1 : 0)
#define list_is_tail(element) ((element)->next == NULL ? 1 : 0)
#define list_data(element) ((element)->data)
#define list_next(element) ((element)->next)

#endif /* list_h */
