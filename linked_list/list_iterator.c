#include "linked_list.h"
#include <stddef.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <stdio.h>

typedef struct list_iterator ioopm_list_iterator_t;
typedef union element    elem_t;

struct list_iterator{
    ioopm_list_node_t *current;
    ioopm_list_t *list;
};

ioopm_list_iterator_t *ioopm_list_iterator_create(ioopm_list_t *l){
    ioopm_list_iterator_t *tmp = calloc(1,sizeof(ioopm_list_iterator_t));
    tmp->current = l->first;
    tmp->list = l;
    return tmp;
}

void ioopm_list_iterator_destroy(ioopm_list_iterator_t *iter){
    free(iter);
}

bool ioopm_list_iterator_at_end(ioopm_list_iterator_t *iter){
    return iter->current->tail == NULL;
}

void ioopm_list_iterator_advance(ioopm_list_iterator_t *iter){
    if(iter->current->tail != NULL){
        iter->current = iter->current->tail;
    } else{
        iter->current = iter->list->first;
    }
}

elem_t ioopm_list_iterator_current(ioopm_list_iterator_t *iter){
    return iter->current->head;
}

static size_t find_index(ioopm_list_node_t *node, ioopm_list_t *list){
    ioopm_list_node_t *current = list->first;
    size_t count = 0;
    while(node->tail != current->tail){
        current = current->tail;
        count++;
    }
    return count;
}

elem_t ioopm_list_iterator_remove(ioopm_list_iterator_t *iter){
    elem_t removed = ioopm_list_remove(iter->list, find_index(iter->current, iter->list));
    ioopm_list_iterator_advance(iter);
    return removed;
}

void ioopm_list_iterator_insert(ioopm_list_iterator_t *iter, elem_t element){
    if(iter->list->first == NULL){
        ioopm_list_append(iter->list, element);
        iter->current = iter->list->first;
        return;
    }
    size_t index = find_index(iter->current, iter->list);
    ioopm_list_insert(iter->list, index, element);

    size_t i = 0;
    iter->current = iter->list->first;
    while(i != index){
        iter->current = iter->current->tail;
        i++;
    }

}