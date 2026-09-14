#include <stddef.h>

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

ioopm_hash_table_t *ioopm_hash_table_create(void) {
  // TODO: Stub
  return NULL
  
  ;
 }
 
 void ioopm_hash_table_destroy(ioopm_hash_table_t *ht) {
  // TODO: Stub
  (void) ht;
  return;
 }

 //$ gcc -Wall -Wextra -g -c hash_table.c kompileringsförslag



