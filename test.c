#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "hashtable.h"
#include "linkedlist.h"
#include "insertionsort.h"

typedef struct test_st test_st;

typedef struct test_st
{
    llnode hdr;
    int val;
} test_st;

int main(int argc, char *argv[])
{
    llist *ll = NULL;

    printf("Allocating list ...\n");
    ll = malloc(sizeof(llist));
    memset(ll, 0, sizeof(llist));

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
        free_llnode(ll, ll->head);
    }

    free_llist(ll);

    printf("Allocating hashtable ...\n");
    htable *ht = get_htable(65536);

    int num_elems = 1000000;
    printf("Populating hashtable with %i elements ...\n", num_elems);
    for (i = 0; i < num_elems; ++i) {
        char key[HT_MAX_KEY_LEN];
        snprintf(key, HT_MAX_KEY_LEN, "%i", i + 1);
        void *value = malloc(128);
        add_item(ht, key, value);
    }

    printf("Freeing hashtable ...\n");
    free_htable(ht); 

    printf("Allocating list ...\n");
    ll = malloc(sizeof(llist));
    memset(ll, 0, sizeof(llist));

    printf("Initializing unsorted list ...\n");

    add_llnode_tail(ll, (llnode *)calloc(sizeof(test_st), 1));
    ((test_st *)(ll->tail))->val = 5;
    add_llnode_tail(ll, (llnode *)calloc(sizeof(test_st), 1));
    ((test_st *)(ll->tail))->val = 2;
    add_llnode_tail(ll, (llnode *)calloc(sizeof(test_st), 1));
    ((test_st *)(ll->tail))->val = 1;
    add_llnode_tail(ll, (llnode *)calloc(sizeof(test_st), 1));
    ((test_st *)(ll->tail))->val = 4;
    add_llnode_tail(ll, (llnode *)calloc(sizeof(test_st), 1));
    ((test_st *)(ll->tail))->val = 3;

    printf("Sorting list with insertion sort ...\n");

    ll = insertion_sort(ll);

    printf("Verifying sort ...\n");

    int sorted = 1;
    llnode *cur = ll->head;
    int val = ((test_st *)(ll->head))->val;
    while (cur->next) {
        cur = cur->next;

        if (((test_st *)cur)->val > val) {
            sorted = 0;
            break;
        }
    }

    if (sorted)
        printf("\tVerification successful.\n");
    else {
        fprintf(stderr, "\tVerification failed.\n");
    }

    printf("Freeing list ...\n");

    while (ll->count) {
        printf("\tFreeing element val %i ...\n", ((test_st *)(ll->head))->val);
        free_llnode(ll, ll->head);
    }

    printf("Completed.\n");

    return 0;
}
