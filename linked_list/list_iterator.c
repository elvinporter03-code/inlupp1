#include <stddef.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <stdio.h>
#include "../common.h"
#include "linked_list.h"

typedef struct list_iterator ioopm_list_iterator_t;

struct list_iterator {
    ioopm_list_t *list;
    ioopm_list_node_t *current_node;
};

ioopm_list_iterator_t *ioopm_list_iterator_create(ioopm_list_t *l) {
    ioopm_list_iterator_t *it = calloc(1, sizeof(ioopm_list_iterator_t));
    it -> list = l;
    it -> current_node = l -> first;

    return it;
}

void ioopm_list_iterator_destroy(ioopm_list_iterator_t *iter) {
    free(iter);
}

bool ioopm_list_iterator_at_end(ioopm_list_iterator_t *iter) {
    return iter -> current_node -> tail == NULL;
}

void ioopm_list_iterator_advance(ioopm_list_iterator_t *iter) {
    iter->current_node = ioopm_list_iterator_at_end(iter)
                            ?  iter -> list -> first
                            : iter -> current_node -> tail;

}

elem_t ioopm_list_iterator_current(ioopm_list_iterator_t *iter) {
    return iter -> current_node -> head;
}

static size_t find_index_in_list(ioopm_list_t *list, ioopm_list_node_t *node) {
    size_t index = 0;
    ioopm_list_node_t *node_to_compare = list -> first;
    while (node != node_to_compare) {
        node_to_compare = node_to_compare -> tail;
        index ++;
    }

    return index;
}

elem_t ioopm_list_iterator_remove(ioopm_list_iterator_t *iter) {
    ioopm_list_node_t *to_remove = iter -> current_node;
    size_t index_of_to_remove = find_index_in_list(iter -> list, to_remove);

    ioopm_list_iterator_advance(iter);

    return ioopm_list_remove(iter -> list, index_of_to_remove);
}

void ioopm_list_iterator_insert(ioopm_list_iterator_t *iter, elem_t element) {
    if (iter -> current_node == NULL) {
        ioopm_list_append(iter -> list, element);
        iter -> current_node = iter -> list -> first;
        return;
    }

    size_t index_for_insert = find_index_in_list(iter -> list, iter -> current_node);
    ioopm_list_insert(iter -> list, (int) index_for_insert, element);
    
}