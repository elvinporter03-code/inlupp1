#pragma once
#include <stddef.h>
#include <stdbool.h>

#define int_elem(x)   ((elem_t) { .i = (x) })
#define bool_elem(x)  ((elem_t) { .b = (x) })
#define string_elem(x) ((elem_t) { .s = (x) })
#define No_Buckets 17

typedef struct entry entry_t;
typedef struct hash_table ioopm_hash_table_t;
typedef union element elem_t;
typedef bool ioopm_eq_function(elem_t a, elem_t b);
typedef size_t ioopm_hash_function(elem_t key);

union element {
  char *s;
  int i;
  bool b;
};

struct entry
{
  elem_t key;    // holds the key
  entry_t *next; // points to the next entry (possibly NULL)
  elem_t value;
};

struct hash_table
{
  entry_t buckets[No_Buckets];
  size_t ht_size;
  ioopm_hash_function *hash;
  ioopm_eq_function *is_equal;
};

