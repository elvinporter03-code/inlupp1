#include <stddef.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <stdio.h>
#include "../common.h"

//Typedef ska vara efter struct
typedef struct list      ioopm_list_t;
typedef struct list_node ioopm_list_node_t;

struct list {
    ioopm_list_node_t *first;
    ioopm_list_node_t *last;
    size_t size;
};


struct list_node {
    elem_t head;
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

void ioopm_list_append(ioopm_list_t *list, elem_t value){
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

elem_t ioopm_list_head(ioopm_list_t *list){
    return list->first->head;
}

elem_t ioopm_list_last(ioopm_list_t *list) {
    return list->last->head;
}

void ioopm_list_prepend(ioopm_list_t *list, elem_t value){
    ioopm_list_node_t *new_node = calloc(1, sizeof(ioopm_list_node_t));
    new_node -> head = value;
    new_node -> tail = list->first; 
    list->first = new_node;
    (list->size)++;
    if(list->last == NULL){
        list->last = list->first;
    }
}

static ioopm_list_node_t *find_previous(ioopm_list_node_t *tmp, size_t index){ 
    ioopm_list_node_t *current = tmp; 
    while(index != 0){
        tmp = current;
        current = current->tail;
        index--;
    }
    return tmp;
}

void ioopm_list_insert(ioopm_list_t *list, size_t index, elem_t value){ //inte testad men ser fin ut
    if(index == 0){
        ioopm_list_prepend(list, value);
        return;
    } else if(index == list->size){ // ÄNDRAT förut stod det size - 1 men det borde väll bara vara size. om index == size så vill vi lägga till på slutet, alltså append'a.
        ioopm_list_append(list, value);
        return;
    }
    ioopm_list_node_t *previous = find_previous(list->first, index);
    ioopm_list_node_t *current = previous->tail;
    
    ioopm_list_node_t *new_node = calloc(1, sizeof(ioopm_list_node_t));
    new_node -> head = value;
    new_node -> tail = current;
    previous -> tail = new_node;
    (list->size)++;
}

elem_t ioopm_list_remove(ioopm_list_t *list, size_t index){
    ioopm_list_node_t *previous = find_previous(list->first, index);
    ioopm_list_node_t *current = previous->tail;
    elem_t removed = current->head;

    previous->tail = current->tail;
    if (index == 0){
        list->first = list->first->tail;
    } else if(index == list->size -1){
        list->last = previous;
    }
    free(current);
    (list->size)--;
    return removed;
}

elem_t ioopm_list_get(ioopm_list_t *list, size_t index){
    if(index == 0 ){
        return list->first->head;
    }
    ioopm_list_node_t *previous = find_previous(list->first, index);
    previous = previous->tail;
    return previous->head;
}

size_t ioopm_list_size(ioopm_list_t *list){
    return list->size;
}


bool ioopm_list_is_empty(ioopm_list_t *list){
    return ioopm_list_size(list) == 0;
}


