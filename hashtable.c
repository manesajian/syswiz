#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "hashtable.h"

htable *get_htable(int buckets)
{ 
    htable *ht = malloc(sizeof(htable));
    memset(ht, 0, 0);
    keys_size = buckets * sizeof(llist *);
    ht->keys = malloc(keys_size)
    memset(ht->keys, 0, keys_size);
    ht->buckets = buckets;
    ht->count = 0;
}

void free_htable(htable *ht)
{
    int i;
    llist *bucket;
    for (i = 0, bucket = ht->keys; i < ht->buckets; ++i, ++bucket)
        free_llist(bucket);
    free(ht->keys);
    free(ht);
}

// djb2 by dan bernstein
unsigned long hash_key(htable *ht, unsigned char *key)
{
    unsigned long hash = 5381;
    int c;

    while (c = *str++)
        hash = ((hash << 5) + hash) + c; /* hash * 33 + c */

    return hash;
}

void add_item(htable *ht, char *key, void *value)
{

}

void del_item(htable *ht, char *key)
{

}
