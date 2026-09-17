#pragma once
#include <stdbool.h>
#include <stddef.h>

#define No_Buckets 17

/**
* @file hash_table.h
* @author Elvin Porter och Anton Äng
* @date 14/09-2026
* @brief Simple hash table that maps string keys to integer values.
*
* Here typically goes a more extensive explanation of what the header
* defines. Doxygens tags are words preceeded by either a backslash @\
* or by an at symbol @@.
*
*/
typedef struct entry entry_t;
typedef struct hash_table ioopm_hash_table_t;
typedef union element elem_t;

union element {
  char *string;
  int integer;
  float floating_point;
  bool boolean;
  size_t unsigned_integer;
};

struct entry
{
  char *key;    // holds the key
  entry_t *next; // points to the next entry (possibly NULL)
  elem_t value;
};

struct hash_table
{
  entry_t buckets[No_Buckets];
  size_t ht_size;
};



/// @brief Create a new hash table
/// @return A new empty hash table
ioopm_hash_table_t *ioopm_hash_table_create(void);

/// @brief Delete a hash table and free its memory
/// @param ht a hash table to be deleted
//void ioopm_hash_table_destroy(ioopm_hash_table_t *ht);



void ioopm_hash_table_destroy_iter(ioopm_hash_table_t *ht);


/// @brief add key => value entry in hash table ht
/// @param ht hash table operated upon
/// @param key key to insert
/// @param value value to insert
void ioopm_hash_table_insert(ioopm_hash_table_t *ht, char *key, int value);

/// @brief lookup value for key in hash table ht and writes it to result
/// @param ht hash table operated upon
/// @param key key to lookup
/// @param result pointer to where the result gets written
/// @return true/false depending on wether lookup was sucessfull    
bool ioopm_hash_table_lookup(ioopm_hash_table_t *ht, char *key, int *result);

/// @brief remove any mapping from key to a value
/// @param ht hash table operated upon
/// @param key key to remove
/// @param result variable to store removed value in.
/// @return the value mapped to by key (FIXME: what if the key does not exist?)
bool ioopm_hash_table_remove(ioopm_hash_table_t *ht, char *key, int *result);

//TODO
unsigned long string_sum_hash(const char *str);

//TODO
bool ioopm_hash_table_has_key(ioopm_hash_table_t *ht, char *key);

// TODO: documentation
bool ioopm_hash_table_is_empty(ioopm_hash_table_t *ht);

// TODO: documentation
size_t ioopm_hash_table_size(ioopm_hash_table_t *ht);

//TODO: documentation
entry_t *find_previous(ioopm_hash_table_t *ht, char *key);
