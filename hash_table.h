#pragma once

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
struct entry
{
  char *key;
  int value;
  entry_t *next; 
};

struct hash_table
{
  entry_t *buckets[17];
};

/// @brief Create a new hash table
/// @return A new empty hash table
ioopm_hash_table_t *ioopm_hash_table_create(void);

/// @brief Delete a hash table and free its memory
/// @param ht a hash table to be deleted
void ioopm_hash_table_destroy(ioopm_hash_table_t *ht);

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
/// @return the value mapped to by key (FIXME: what if the key does not exist?)
int ioopm_hash_table_remove(ioopm_hash_table_t *ht, char *key);

unsigned long string_sum_hash(const char *str);
