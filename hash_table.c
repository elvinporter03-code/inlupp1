#include <stddef.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <stdio.h>

#define No_Buckets 17

typedef struct entry entry_t;
typedef struct hash_table ioopm_hash_table_t;

struct entry
{
  char *key;    // holds the key
  int value;    // holds the value
  entry_t *next; // points to the next entry (possibly NULL)
};

struct hash_table
{
  entry_t buckets[No_Buckets];
  int ht_size;
};

// HASH FUNCTION
static size_t string_knr_hash(const char *str)
{
  size_t result = 0;
  while (*str != '\0')
  {
    result = result * 31 + ((unsigned char) *str);
    str++;
  }
  return result;
}

ioopm_hash_table_t *ioopm_hash_table_create(void)
{
  /// Allocate zeroed-out space for a ioopm_hash_table_t = 17 pointers to entry_t's
  ioopm_hash_table_t *tmp = calloc(1, sizeof(ioopm_hash_table_t));
  tmp->ht_size = 0;
  return tmp;
}


//iterative version
static void entry_destroy(entry_t *current) {
  free(current);
}

static entry_t *find_previous_entry(ioopm_hash_table_t *ht, char *key){

  size_t bucket = string_knr_hash(key) % No_Buckets;
  entry_t *previous = &ht->buckets[bucket];

  while(previous->next != NULL && strcmp(previous->next->key, key) != 0){
    previous = previous->next;
  }
  return previous;
}

bool ioopm_hash_table_remove(ioopm_hash_table_t *ht, char *key, int *result) {
  entry_t *previous = find_previous_entry(ht, key);
  entry_t *current = previous->next; 
  if (current == NULL) {
    return false;
  } else {
    previous->next = current->next;
    *result = current->value;
    entry_destroy(current);

    (ht->ht_size)--; // decrement ht_size by one after removal.
    return true;
  }
}

static void free_bucket_iter(entry_t *e){
  entry_t *current = e->next;

  while (current != NULL) //loopar igenom till sista entryn och freear allt
      {
        entry_t *next = current->next;
        entry_destroy(current); // free buckets pointer
        current = next; // update buckets pointer next entry_t
      }
  }

void ioopm_hash_table_destroy_iter(ioopm_hash_table_t *ht)
{
  for (int index = 0; index < No_Buckets; index++) // traverse each allocated bucket in memory.
  {
    entry_t *entry = &ht->buckets[index]; // create pointer to bucket
    free_bucket_iter(entry);
    
  }

  free(ht); // when all buckets only contains sentinel nodes, free ht
}

static entry_t *entry_create(char *key, int value, entry_t *next)
{
  next = calloc(1, sizeof(entry_t)); 
  next->key = key;
  next->value = value;
  next->next = NULL;
  return next;
}


void ioopm_hash_table_insert(ioopm_hash_table_t *ht, char *key, int value)
{
  // find previous entry, or the last entry if the key does not exist
  entry_t *previous = find_previous_entry(ht, key);

  // if the key exists, update the value, otherwise create a new entry
  if (previous->next != NULL)
  {
    previous->next->value = value;
  }
  else
  {
    previous->next = entry_create(key, value, NULL);

    (ht->ht_size)++; // increment ht_size when entry added.
  }
}

bool ioopm_hash_table_lookup(ioopm_hash_table_t *ht, char *key, int *result)
{

  entry_t *previous = find_previous_entry(ht, key);
  
  // if the key exists, return the value, otherwise, indicate that the lookup failed
  if (previous->next != NULL)
  {
    *result = previous->next->value;
    return true;
  }
  else
  {
    return false;
  }
}



bool ioopm_hash_table_has_key(ioopm_hash_table_t *ht, char *key){
  // function uses same logic as lookup, therefore conveniant to reuse it.
  
  int tmp; // this is a filler, not important for this has_key but needed for lookup.

  return ioopm_hash_table_lookup(ht, key, &tmp);
}

int ioopm_hash_table_size(ioopm_hash_table_t *ht){  
  return ht->ht_size;
}


bool ioopm_hash_table_is_empty(ioopm_hash_table_t *ht){
  return ioopm_hash_table_size(ht) == 0;
}




 //gcc -Wall -Wextra -g hash_table.c hash_table_tests.c -o hash_table_tests -lcunit



