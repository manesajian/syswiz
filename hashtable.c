#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "hashtable.h"

htable *get_htable(int buckets)
{ 
    htable *ht = malloc(sizeof(htable));
    memset(ht, 0, 0);
    int keys_size = buckets * sizeof(llist *);
    ht->keys = malloc(keys_size);
    memset(ht->keys, 0, keys_size);
    ht->buckets = buckets;
    return ht;
}

void free_htable(htable *ht)
{
    int i = 0;
    llist *bucket = ht->keys[0];
    for (; i < ht->buckets; ++i, ++bucket)
        free_llist(bucket);
    free(ht->keys);
    free(ht);
}

unsigned long count_htable(htable *ht)
{
    int sum = 0;
    int i = 0;
    llist *bucket = ht->keys[0];
    for (; i < ht->buckets; ++i, ++bucket)
        sum += bucket->count;
    return sum;
}

// djb2 by dan bernstein
unsigned long hash_key(htable *ht, char *str)
{
    unsigned long hash = 5381;
    int c;

    while ((c = *str++))
        hash = ((hash << 5) + hash) + c; /* hash * 33 + c */

    return hash % ht->buckets;
}

void add_item(htable *ht, char *key, void *value)
{
    unsigned long hash = hash_key(ht, key);

    llist *bucket = ht->keys[hash];
    if (bucket == NULL)
        bucket = ht->keys[hash] = get_llist();

    int keylen = (int)strnlen(key, HT_MAX_KEY_LEN) + 1;

    htnode *node = malloc(sizeof(htnode) + keylen);
    node->elem.data = value;

    strncpy(node->key, key, keylen - 1);
    node->key[keylen - 1] = 0;

    add_llnode_head(bucket, (llnode *)node);
}

void *get_item(htable *ht, char *key)
{
    unsigned long hash = hash_key(ht, key);

    llist *bucket = ht->keys[hash];
    if (bucket == NULL)
        return NULL;

    llnode *node = bucket->head;
    while (node) {
        if (!strncmp(key, ((htnode *)node)->key, HT_MAX_KEY_LEN))
            break;
        node = node->next;
    }
    return node;
}

void del_item(htable *ht, char *key)
{
    unsigned long hash = hash_key(ht, key);

    llist *bucket = ht->keys[hash];
    if (bucket == NULL)
        return;

    llnode *node = bucket->head;
    while (node) {
        if (!strncmp(key, ((htnode *)node)->key, HT_MAX_KEY_LEN))
            break;
        node = node->next;
    }

    if (node)
        del_llnode(bucket, node);
}
