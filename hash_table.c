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
  entry_t *buckets[17];
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
static void free_bucket_iter(entry_t *e){
  while (e != NULL) // check if bucket does not point to NULL.
      {
        entry_t *next = e->next; // copy the entry's pointer to next entry_t.
        free(e); // free buckets pointer
        e = next; // update buckets pointer next entry_t
      }
  }
void ioopm_hash_table_destroy_iter(ioopm_hash_table_t *ht)
{
  for (int index = 0; index < 17; index++) // traverse each allocaded bucket in memory.
  {
    entry_t *entry = ht->buckets[index]; // copying bucket's pointer.
    free_bucket_iter(entry);
  }

  free(ht); // when all buckets points to NULL, free ht
}


void ioopm_hash_table_insert(ioopm_hash_table_t *ht, char *key, int value)
{
  // find bucket
  size_t bucket = string_knr_hash(key) % 17;

  // look for an entry with the key we want
  entry_t *current = ht->buckets[bucket]; //sätter current till den bucket som key indexerar till
  while (current != NULL && strcmp(current->key, key) != 0)  // Leta om key finns i bucket'en genom att gå igenom linkade listan och jämföra keys.
  {
    current = current->next;
  }

  // if the key exists, update the value, otherwise, add a new entry to the end of the list
  if (current != NULL)
  {
    current->value = value;
  }
  else
  {
    // if the bucket is empty, we add a new first node
    if (ht->buckets[bucket] == NULL)
    {
      ht->buckets[bucket] = malloc(sizeof(entry_t));
      ht->buckets[bucket]->key = key;
      ht->buckets[bucket]->value = value;
      ht->buckets[bucket]->next = NULL;
    }
    else
    {
      // otherwise, we append a new node to the list
      entry_t *last = ht->buckets[bucket];
      while (last->next != NULL)
      {
        last = last->next;
      }
      last->next = malloc(sizeof(entry_t));
      last->next->key = key;
      last->next->value = value;
      last->next->next = NULL;
    }
  }
}

bool ioopm_hash_table_lookup(ioopm_hash_table_t *ht, char *key, int *result)
{

  size_t bucket = string_knr_hash(key) % 17;

  // look for an entry with the key we want
  entry_t *current = ht->buckets[bucket];
  while (current != NULL && strcmp(current->key, key) != 0)
  {
    current = current->next;
  }

  // if the key exists, return the value, otherwise, indicate that the lookup failed
  if (current != NULL)
  {
    *result = current->value;
    return true;
  }
  else
  {
    return false;
  }
}

 //gcc -Wall -Wextra -g hash_table.c hash_table_tests.c -o hash_table_tests -lcunit

 /*
 int main(void) {
 
   printf("%ld", sizeof(entry_t));
 
   return 0;
 }
 */


