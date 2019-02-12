#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "generic_list.h"

void __list_initialize(list_t *list, size_t data_size, int (*data_cmp)(void *, void *), void (*data_print)(FILE *, void *)) {
    list->head = NULL;
    list->data_size = data_size;
    list->data_cmp = data_cmp;
    list->data_print = data_print;
}

// Add a node in the beginning
list_node_t *list_insert(list_t *list, void *new_data) {
    size_t data_size = list->data_size;
    /* Allocate node and initialize node */
    // NOTE(stefanos): + data_size means that the size of the variable-length
    // array 'data' of the node will be of size data_size.
    list_node_t *new_node = (list_node_t *) malloc(sizeof(list_node_t) + data_size);
    memcpy(new_node->data, new_data, data_size);
    /* since we are adding at the begining, prev is always NULL */
    new_node->prev = NULL;
    /* link the old list off the new node */
    new_node->next = list->head;
    /* change prev of head node to new node */
    if(list->head != NULL) {
        list->head->prev = new_node;
    }
    /* move the head to point to the new node */
    list->head = new_node;

    return new_node;
}

list_node_t *list_sorted_insert(list_t *list, void *new_data) {
    size_t data_size = list->data_size;
    list_node_t *current;
    /* Allocate and initialize node */
    // NOTE(stefanos): + data_size means that the size of the variable-length
    // array 'data' of the node will be of size data_size.
    list_node_t *new_node = (list_node_t *) malloc(sizeof(list_node_t) + data_size);
    memcpy(new_node->data, new_data, data_size);
    new_node->prev = new_node->next = NULL;
    /* if list is empty */
    if(list->head == NULL) {
        list->head = new_node;
    } else {
        if(list->data_cmp(new_node->data, list->head->data) < 0) {
            new_node->next = list->head;
            new_node->next->prev = new_node;
            list->head = new_node;
        } else {
            current = list->head;
            /* Find position to be inserted */
            while(current->next != NULL && list->data_cmp(new_node->data, current->next->data) > 0) {
                current = current->next;
            }
            new_node->next = current->next;
            if(current->next != NULL) {
                new_node->next->prev = new_node;
            }
            current->next = new_node;
            new_node->prev = current;
        }
    }

    return new_node;
}

void list_delete_node(list_t *list, list_node_t *del) {
    /* base case */
    if(list->head == NULL || del == NULL)
        return;
    /* If node to be deleted is head node */
    if(list->head == del)
        list->head = del->next;
    /* Change next only if node to be deleted is NOT the last node */
    if(del->next != NULL)
        del->next->prev = del->prev;
    /* Change prev only if node to be deleted is NOT the first node */
    if(del->prev != NULL)
        del->prev->next = del->next;
    /* Finally, free the memory occupied by del*/
    free(del);
}

list_node_t *list_search(list_t *list, void *searching_data) {
    list_node_t *temp = list->head;
    while(temp != NULL) {
        if(list->data_cmp(temp->data, searching_data) == 0 ) {
            return temp;
        } else {
            temp = temp->next;
        }
    }
    return NULL;
}

list_node_t *list_search_custom(list_t *list, void *searching_data, int (*eq)(void *, void *)) {
    list_node_t *temp = list->head;
    while(temp != NULL) {
        if(eq(temp->data, searching_data) == 0) {
            return temp;
        } else {
            temp = temp->next;
        }
    }
    return NULL;
}

void list_print(list_t *list, FILE *out) {
    if(list == NULL) return;

    list_node_t *temp = list->head;
    while(temp != NULL) {
        list->data_print(out, temp->data);
        temp = temp->next;
    }

}

void list_delete_list(list_t *list) {

    if(list == NULL) return;

    list_node_t *current = list->head;
    list_node_t *next;

    while(current != NULL) {
        next = current->next;
        free(current);
        current = next;
    }
    list->head = NULL;
}
