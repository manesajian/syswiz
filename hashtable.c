#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "hashtable.h"

htable *get_htable()
{ 
    llist *ll = malloc(sizeof(llist));
    memset(ll, 0, 0);
    return ll;
}

void free_htable(htable *ht)
{
    while (ll->head) {
        del_llnode(ll, ll->head);
    }

    free(ll);
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
