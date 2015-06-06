#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "hashtable.h"
#include "linkedlist.h"

typedef struct test_st test_st;

typedef struct test_st
{
    llnode hdr;
    int val;
} test_st;

int main(int argc, char *argv[])
{
    llist *ll = NULL;
    ll = malloc(sizeof(llist));
    memset(ll, 0, 0);

    printf("Allocating list ...\n");
    ll = malloc(sizeof(llist));
    memset(ll, 0, 0);

    printf("Initializing list ...\n");

    int i;
    for (i = 0; i < 5; ++i) {
        test_st *node = malloc(sizeof(test_st));
        node->val = i;
        printf("\tAdding element val %i ...\n", node->val);
        add_llnode(ll, (llnode *)node);
    }

    printf("Freeing list ...\n");

    while (ll->count) {
        printf("\tFreeing element val %i ...\n", ((test_st *)(ll->head))->val);
        del_llnode(ll, ll->head);
    }

    free_llist(ll);

    printf("Allocating hashtable ...\n");
    htable *ht = get_htable(65536);

    int num_elems = 10000000;
    printf("Populating hashtable with %i elements ...\n", num_elems);
    for (i = 0; i < num_elems; ++i) {
        char key[HT_MAX_KEY_LEN];
        snprintf(key, HT_MAX_KEY_LEN, "%i", i + 1);
        void *value = malloc(128);
        add_item(ht, key, value);
    }

    printf("Freeing hashtable ...\n");
    free_htable(ht); 

    printf("Completed.\n");

    return 0;
}
