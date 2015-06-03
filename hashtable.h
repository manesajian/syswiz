#include <linkedlist.h>

#define HT_MAX_KEY_LEN 1024

typedef struct htnode
{
    llnode node;
    char *key;
} htnode;

typedef struct htable
{
    llist **keys;
    int buckets;
} htable;

typedef struct ht

htable *get_htable(int buckets);
unsigned long count_htable(htable *ht);
void free_htable(htable *ht);
unsigned long hash_key(htable *ht, unsigned char *key);
void add_item(htable *ht, char *key, void *value);
void get_item(htable *ht, char *key);
void del_item(htable *ht, char *key);
