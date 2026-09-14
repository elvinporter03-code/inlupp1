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