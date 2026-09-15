#include <stddef.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#include <stdio.h>

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
  entry_t buckets[17];
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
  return calloc(1, sizeof(ioopm_hash_table_t));
}

/*
// recursive version
static void free_bucket_rec(entry_t *e){
  if(e->next != NULL){
    entry_t *tmp = e->next;
    free(e);
    free_bucket_rec(tmp);
    
  } 
  else{
    free(e);
  }
}
void ioopm_hash_table_destroy_rec(ioopm_hash_table_t *ht)
{
  for (int index = 0; index < 17; index++) // traverse each allocated bucket in memory.
  {
    entry_t *entry = ht->buckets[index]; // copying bucket's pointer.
    free_bucket_rec(entry);
  }

  free(ht); // when all buckets points to NULL, free ht
}
*/

//iterative version
void entry_destroy(entry_t *current) {
  
  free(current);
}

void entry_remove(entry_t *current){
  entry_t *tmp = current->next;
  entry_destroy(current->next);
  current->next = tmp;
}

static void free_bucket_iter(entry_t *e){
  entry_t *current = e->next;

  while (current != NULL) //loopar igenom till sista entryn och freear allt
      {
        entry_t *next = current->next;
        free(current); // free buckets pointer
        current = next; // update buckets pointer next entry_t
      }
  }

void ioopm_hash_table_destroy_iter(ioopm_hash_table_t *ht)
{
  for (int index = 0; index < 17; index++) // traverse each allocated bucket in memory.
  {
    entry_t *entry = &ht->buckets[index]; // create pointer to bucket
    free_bucket_iter(entry);
    free(entry);
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


entry_t *find_previous_entry(ioopm_hash_table_t *ht, char *key){

  size_t bucket = string_knr_hash(key) % 17;
  entry_t *previous = &ht->buckets[bucket];

  while(previous->next != NULL && strcmp(previous->next->key, key) != 0){
    previous = previous->next;
  }
  return previous;
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


/*
bool ioopm_hash_table_has_key(ioopm_hash_table_t *ht, char *key){
  //stub
  return false;
}

int ioopm_hash_table_size(ioopm_hash_table_t *ht){
  //stub
  return 0;
}


bool ioopm_hash_table_is_empty(ioopm_hash_table_t *ht){
  return ioopm_hash_table_size(ht) == 0;
}
*/



 //gcc -Wall -Wextra -g hash_table.c hash_table_tests.c -o hash_table_tests -lcunit

 /*
 int main(void) {
 
   printf("%ld", sizeof(entry_t));
 
   return 0;
 }
 */


