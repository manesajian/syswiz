#include <linkedlist.h>

#define NUM_BUCKETS 65536

typedef struct htable
{
    llist **keys;
    int buckets;
} htable;

htable *get_htable(int buckets);
unsigned long count_htable(htable *ht);
void free_htable(htable *ht);
unsigned long hash_key(htable *ht, unsigned char *key);
void add_item(htable *ht, char *key, void *value);
void get_item(htable *ht, char *key);
void del_item(htable *ht, char *key);
