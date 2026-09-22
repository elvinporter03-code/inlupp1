#include <stddef.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <stdio.h>
#include "common2.h"

ioopm_hash_table_t *ioopm_hash_table_create(ioopm_hash_function *hash_fn, ioopm_eq_function *key_eq_fn)
{
  ioopm_hash_table_t *ht = calloc(1, sizeof(ioopm_hash_table_t));
  ht->no_buckets = 17;
  ht->buckets = calloc(ht->no_buckets, sizeof(entry_t));
  ht->ht_size = 0;
  ht->hash = hash_fn;
  ht->is_equal = key_eq_fn;

  return ht;
}

/// @brief Frees allocated memory of an entry_t
/// @pre current is allocated in memory before this function is called
/// @param current A pointer to the entry_t that will be freed
/// @return void
static void entry_destroy(entry_t *current)
{
  free(current);
}

/// @brief Frees the allocated memory of a bucket in a hash table
/// @param e pointer to a entry_t
/// @return void
static void free_bucket(entry_t *e)
{
  entry_t *current = e->next;

  while (current != NULL) // traverse the bucket from current to the last non-NULL entry
  {
    entry_t *next = current->next;
    entry_destroy(current);
    current = next; // update current pointer to next entry_t
  }
}

/// @brief Finds the previous entry in relation to key in a hash table,
///        or the last entry if the key does not exist
/// @param ht Pointer to a hash table
/// @param key the key of an entry_t in ht
/// @return the previous entry of key in ht
static entry_t *find_previous_entry(ioopm_hash_table_t *ht, elem_t key)
{
  size_t bucket = ht->hash(key) % ht->no_buckets;
  entry_t *previous = &ht->buckets[bucket];

  while (previous->next != NULL && !(ht->is_equal(previous->next->key, key)))
  {
    previous = previous->next;
  }
  return previous;
}



void ioopm_hash_table_destroy(ioopm_hash_table_t *ht)
{
  for (size_t index = 0; index < ht->no_buckets; index++)
  {
    entry_t *entry = &ht->buckets[index];
    free_bucket(entry);
  }
  free(ht->buckets);
  free(ht); // when all buckets only contains sentinel nodes, free ht
}

/// @brief Creates and returns an entry from the inputs
/// @param key Key for hashing the entry
/// @param value Value associated with the entry
/// @return Entry with pointer to NULL
static entry_t *entry_create(elem_t key, elem_t value)
{
  entry_t *next;
  next = calloc(1, sizeof(entry_t));
  next->key = key;
  next->value = value;

  return next;
}


static void rehash_bucket(ioopm_hash_table_t *ht, entry_t *arr, entry_t *old_arr)
{
  entry_t *current = old_arr->next; //initierar till första efter sentinelnoden

  while (current != NULL) // traverse the bucket from current to the last non-NULL entry
  {
    entry_t *next = current->next;
    ioopm_hash_table_insert(ht, current->key, current->value);
    entry_destroy(current);
    current = next; // update current pointer to next entry_t
  }
}

static void rehash(ioopm_hash_table_t *ht, entry_t *new_buckets)
{
  for (size_t index = 0; index < ht->no_buckets; index++)
  {
    entry_t *entry = &ht->buckets[index];
    rehash_bucket(ht, new_buckets, entry);
  }
  free(ht->buckets);
}

static void resize_table(ioopm_hash_table_t *ht)
{
  float load_factor = 0.5;
  size_t primes[] = {17, 31, 67, 127, 257, 509, 1021, 2053, 4099, 8191, 16381};
  size_t required_capacity = (ht->ht_size) / load_factor;

  for (int i = 0; i < 11; i++)
  {
    if (required_capacity < primes[i])
    {
      ht->no_buckets = primes[i];
      entry_t *new_buckets = calloc(ht->no_buckets, sizeof(entry_t));
      rehash(ht, new_buckets);
      free(ht->buckets);
      ht->buckets = new_buckets;
      return;
    }
  }

  return;
}

void ioopm_hash_table_insert(ioopm_hash_table_t *ht, elem_t key, elem_t value)
{
  entry_t *previous = find_previous_entry(ht, key);

  // if the key exists, update the value, otherwise create a new entry
  if (previous->next != NULL)
  {
    previous->next->value = value;
  }
  else
  {
    previous->next = entry_create(key, value);

    (ht->ht_size)++; // increment ht_size when entry added.
    resize_table(ht);
  }
}

bool ioopm_hash_table_remove(ioopm_hash_table_t *ht, elem_t key, elem_t *result)
{
  entry_t *previous = find_previous_entry(ht, key);
  entry_t *current = previous->next;

  if (current == NULL) // if current is a NULL-entry, there is nothing to remove
  {
    return false;
  }
  else
  {
    previous->next = current->next;
    *result = current->value;
    entry_destroy(current);

    (ht->ht_size)--; // decrement ht_size by one after removal.
    resize_table(ht);

    return true;
  }
}

bool ioopm_hash_table_lookup(ioopm_hash_table_t *ht, elem_t key, elem_t *result)
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

bool ioopm_hash_table_has_key(ioopm_hash_table_t *ht, elem_t key)
{
  // function uses same logic as lookup, therefore conveniant to reuse it.

  elem_t tmp; // this is a filler, not important for has_key but needed for lookup.

  return ioopm_hash_table_lookup(ht, key, &tmp);
}

size_t ioopm_hash_table_size(ioopm_hash_table_t *ht)
{
  return ht->ht_size;
}

bool ioopm_hash_table_is_empty(ioopm_hash_table_t *ht)
{
  return ioopm_hash_table_size(ht) == 0;
}
