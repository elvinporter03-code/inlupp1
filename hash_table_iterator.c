#include "hash_table.h"
#include <stddef.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <stdio.h>

#define No_Buckets 17

typedef struct hash_table_iterator ioopm_hash_table_iterator_t;

struct hash_table_iterator
{
  ioopm_hash_table_t *ht;
  int current_bucket;
  entry_t *current_entry;
};

static entry_t *find_first_entry_in_ht(ioopm_hash_table_t *ht, int *index){
    int i = 0;
    for(; i < No_Buckets; i++){
        if (ht->buckets[i].next != NULL && ht->buckets[i].key != NULL){
            *index = i;
            return &ht->buckets[i];
        }
    }
    return &ht->buckets[i];
}

static entry_t *find_next_entry_in_ht(ioopm_hash_table_t *ht, int *index){
    int i = *index;
    for(; i < No_Buckets; i++){
        if (ht->buckets[i].next != NULL && ht->buckets[i].key != NULL){
            *index = i;
            return &ht->buckets[i];
        }
    }
    return &ht->buckets[i];
}


ioopm_hash_table_iterator_t *ioopm_hash_table_iterator_create(ioopm_hash_table_t *ht){
    int bucket_index;
    ioopm_hash_table_iterator_t *result = calloc(1, sizeof(ioopm_hash_table_iterator_t));
    result->current_entry = find_first_entry_in_ht(ht, &bucket_index);
    result->current_bucket = bucket_index;
    result->ht = ht;
    return result;
}

void ioopm_hash_table_iterator_destroy(ioopm_hash_table_iterator_t *it){
    free(it);
}

bool ioopm_hash_table_iterator_at_end(ioopm_hash_table_iterator_t *it){
    return it->current_bucket == No_Buckets && it->current_entry->next == NULL;
}

char *ioopm_hash_table_iterator_current_key(ioopm_hash_table_iterator_t *it){
    return it->current_entry->key;
}

int ioopm_hash_table_iterator_current_value(ioopm_hash_table_iterator_t *it){
    return it->current_entry->value;
}

void ioopm_hash_table_iterator_advance(ioopm_hash_table_iterator_t *it){
    it->current_entry = find_next_entry_in_ht(it->ht, &it->current_bucket);
}
