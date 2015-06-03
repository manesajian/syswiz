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

void add_item(htable *ht, char *key, void *value)
{

}

void del_item(htable *ht, char *key)
{

}
