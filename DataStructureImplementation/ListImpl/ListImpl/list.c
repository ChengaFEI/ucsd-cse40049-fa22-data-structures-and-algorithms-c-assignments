//
//  list.c
//  ListImpl
//
//  Created by Cheng FEI on 2022/10/2.
//

#include <stdlib.h>
#include <string.h>

#include "list.h"

/*
 Constructor of list structure.
 */
void list_init(List *list, void (*destroy)(void *data)) {
    list->size = 0;
    list->head = NULL;
    list->tail = NULL;
    list->destroy = destroy;
}

/*
 Destructor of list structure.
 */
void list_destroy(List *list) {
    // Declare a pointer to void object to accept data property of removed element.
    void *data;
    
    while (list_size(list) > 0) {
        if (list_rem_next(list, NULL, (void **)&data) == 0 && list->destroy != NULL) list->destroy(data);
    }
}

/*
 Insert value as an element in list structure.
 Params: list -- list structure in which new data is inserted.
 Params: element -- list element after which new data is inserted.
 Params: data -- new data to be inserted.
 Returns: status code indicating operation succeeds or fails.
 */
int list_ins_next(List *list, ListElmt *element, const void *data) {
    // Declare new list element.
    ListElmt *new_element;
    // Allocate dynamic memory to new list element.
    // If out of memory, return error code -1.
    if ((new_element = (ListElmt *) malloc(sizeof(ListElmt))) == NULL) return -1;
    // If allocate memory successfully, assigne new value to new list element.
    new_element->data = (void *) data;
    
    // If insert new element at head of list.
    if (element == NULL) {
        new_element->next = list->head;
        list->head = new_element;
        if (list_size(list) == 0) list->tail = new_element;
    }
    // If insert new element at other positions.
    else {
        new_element->next = element->next;
        element->next = new_element;
        if (element->next == NULL) list->tail = new_element;
    }
    
    // Increase size of list by 1.
    list->size++;
    // Return success code 0;
    return 0;
}

/*
 Delete an element from list structure.
 Params: list -- list structure from which data is removed.
 Params: element -- list element structure after which data is removed.
 Params: data -- pointer which keeps the void *data property of removed list element.
 Returns: status code indicating operation succeeds or fails.
 */
int list_rem_next(List *list, ListElmt *element, void **data) {
    // Declare a ListElmt object to store removed element.
    ListElmt *old_element;
    // If list is empty, return error code -1;
    if (list_size(list) == 0) return -1;
    // If remove element from head of list.
    if (element == NULL) {
        old_element = list->head;
        *data = list->head->data;
        list->head = list->head->next;
        if (list_size(list) == 1) list->tail = NULL;
    }
    // If removed element from other positions of list.
    else {
        if (element->next == NULL) return -1;
        old_element = element->next;
        *data = element->next->data;
        element->next = element->next->next;
        if (element->next == NULL) list->tail = element;
    }
    // Clean up memory for old_element.
    free(old_element);
    // Decrease size of list by 1.
    list->size--;
    // Return success code 0;
    return 0;
}
