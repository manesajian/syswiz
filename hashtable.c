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
}

void free_htable(htable *ht)
{
    int i = 0;
    llist *bucket = ht->keys;
    for (; i < ht->buckets; ++i, ++bucket)
        free_llist(bucket);
    free(ht->keys);
    free(ht);
}

unsigned long count_htable(htable *ht)
{
    int sum = 0;
    int i = 0;
    llist *bucket = ht->keys;
    for (; i < ht->buckets; ++i, ++bucket)
        sum += bucket->count;
    return sum;
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
    unsigned long key = hash_key(ht, key);

    llist *bucket = ht->keys[key];
    if (bucket == NULL)
        ht->keys[key] = bucket = get_llist();

    llnode *node = malloc(sizeof(llnode));
    node->data = value;

    add_llnode_head(bucket, node);
}

void get_item(htable *ht, char *key)
{

}

void del_item(htable *ht, char *key)
{
//    unsigned long key = hash_key(ht, key);

//    llist *bucket = ht->keys[key];
//    if (bucket == NULL)

}
