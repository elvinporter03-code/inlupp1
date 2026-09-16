#include <stddef.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <stdio.h>

typedef struct list ioopm_list_t;

struct list
{
    int head; // this is a dodge to simplify, remake this later to be generic
    ioopm_list_t *tail;
};

ioopm_list_t *ioopm_list_create(void)
{
    ioopm_list_t *new_list = calloc(1, sizeof(ioopm_list_t));

    return new_list;
}



int main(void) {
    ioopm_list_t *test = ioopm_list_create();
    printf("%d\n", test->head);
    bool is_null = test->tail == NULL;
    printf("%d\n", is_null);
}