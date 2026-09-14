#include <stddef.h>
#include <stdlib.h>

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

ioopm_hash_table_t *ioopm_hash_table_create()
{
  /// Allocate zeroed-out space for a ioopm_hash_table_t = 17 pointers to entry_t's
  return calloc(1, sizeof(ioopm_hash_table_t));
}

void ioopm_hash_table_destroy(ioopm_hash_table_t *ht)
{
  free(ht);
}

void ioopm_hash_table_insert(ioopm_hash_table_t *ht, char *key, int value) {
  // TODO: Stub
  (void) ht;
  (void) key;
  (void) value;
}

int ioopm_hash_table_lookup(ioopm_hash_table_t *ht, char *key) {
  // TODO: Stub
  (void) ht;
  (void) key;
  return -1;
}

 //gcc -Wall -Wextra -g hash_table.c hash_table_tests.c -o hash_table_tests



