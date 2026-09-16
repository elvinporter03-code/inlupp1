#include <stddef.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <stdio.h>

typedef struct list      ioopm_list_t;
typedef struct list_node ioopm_list_node_t;
typedef union element    ioopm_element_t;

struct list {
    ioopm_list_node_t *first;
    ioopm_list_node_t *last;
    int size;
};

union element {
    char *string;
    int integer;
    float floating_point;
    bool boolean;
    size_t unsigned_integer;
};

struct list_node {
    ioopm_element_t head;
    ioopm_list_node_t *tail;
};

ioopm_list_t *ioopm_list_create(void)
{
   return calloc(1, sizeof(ioopm_list_t));
}

void ioopm_list_destroy(ioopm_list_t *list){
    ioopm_list_node_t *current = list->first;
    while(current != NULL){
        ioopm_list_node_t *next = current->tail;
        free(current);
        current = next;
    }
    free(list);
}

void ioopm_list_append(ioopm_list_t *list, ioopm_element_t value){
    ioopm_list_node_t *new_node = calloc(1, sizeof(ioopm_list_node_t));

    new_node -> head = value;
    new_node -> tail = NULL;

    if (list -> size == 0) {
        list -> first = new_node;
    } else {
        list -> last -> tail = new_node;
    }

    list -> last = new_node;

    (list -> size)++;
}

ioopm_element_t ioopm_list_head(ioopm_list_t *list){
    return list->first->head;
}

ioopm_element_t ioopm_list_last(ioopm_list_t *list) {
    return list->last->head;
}

void ioopm_list_prepend(ioopm_list_t *list, ioopm_element_t value){//inte testad
    ioopm_list_node_t *new_node = calloc(1, sizeof(ioopm_list_node_t));
    new_node -> head = value;
    new_node -> tail = list->first; 
    list->first = new_node;
}

static ioopm_list_node_t *find_previous(ioopm_list_node_t *tmp, int index){
    ioopm_list_node_t *current = tmp;
    while(index != 0){
        tmp = current;
        current = current->tail;
        index--;
    }
    return tmp;
}

void ioopm_list_insert(ioopm_list_t *list, int index, ioopm_element_t value){ //inte testad men ser fin ut
    if(index == 0){
        ioopm_list_prepend(list, value);
        return;
    }
    ioopm_list_node_t *previous = find_previous(list->first, index);
    ioopm_list_node_t *current = previous->tail;
    
    ioopm_list_node_t *new_node = calloc(1, sizeof(ioopm_list_node_t));
    new_node -> head = value;
    new_node -> tail = current->tail;
    previous -> tail = new_node;
}

ioopm_element_t ioopm_list_remove(ioopm_list_t *list, int index){
    ioopm_list_node_t *previous = find_previous(list->first, index);
    ioopm_list_node_t *current = previous->tail;
    ioopm_element_t removed = current->head;

    previous->tail = current->tail;
    free(current);

    return removed;
}

ioopm_element_t ioopm_list_get(ioopm_list_t *list, int index){
    ioopm_list_node_t *previous = find_previous(list->first, index);
    previous = previous->tail;
    return previous->head;
}

int ioopm_list_size(ioopm_list_t *list){
    return list->size;
}

bool ioopm_list_is_empty(ioopm_list_t *list){
    return ioopm_list_size(list) == 0;
}
