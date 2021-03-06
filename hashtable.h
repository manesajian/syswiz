#ifndef INCLUDED_HASHTABLE_H
#define INCLUDED_HASHTABLE_H

#include "linkedlist.h"

#define HT_MAX_KEY_LEN 1024

typedef struct htnode
{
    llnode elem;
    char key[0];
} htnode;

typedef struct htable
{
    int buckets;
    llist *keys[0];
} htable;

htable *get_htable(int buckets);
unsigned long count_htable(htable *ht);
void free_htable(htable *ht);
unsigned long hash_key(htable *ht, char *key);
void add_item(htable *ht, char *key, void *value);
void *get_item(htable *ht, char *key);
void del_item(htable *ht, char *key);

#endif
