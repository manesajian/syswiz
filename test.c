#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "hashtable.h"
#include "linkedlist.h"
#include "insertionsort.h"
#include "quicksort.h"


typedef struct test_st test_st;

typedef struct test_st
{
    llnode hdr;
    int val;
} test_st;

// comparison function for test_st linked list nodes
int compare(llnode *left, llnode *right)
{
    test_st *l = (test_st *)left;
    test_st *r = (test_st *)right;

    if (l->val < r->val)
        return -1;
    if (l->val > r->val)
        return 1;
    return 0;
}

// linked list generation function to produce unsorted list
llist *generate_llist(int count)
{
    srand(time(NULL));

    llist *ll = get_llist();

    int i;
    for (i = 0; i < count; ++i) {
        test_st *node = calloc(sizeof(test_st), 1);
        node->val = rand() % 1000;
        add_llnode(ll, (llnode *)node);
    }

    ll->compare = &compare;

    return ll;
}

int main(int argc, char *argv[])
{
    llist *ll = NULL;

    printf("Creating list ...\n");
    ll = generate_llist(5);

    printf("Freeing list ...\n");

    while (ll->count) {
        printf("\tFreeing element val %i ...\n", ((test_st *)(ll->head))->val);
        free_llnode(ll, ll->head);
    }

    free_llist(ll);

    printf("Allocating hashtable ...\n");
    htable *ht = get_htable(65536);

    int i;
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

    printf("Creating list ...\n");
    ll = generate_llist(5);

    printf("Sorting list with insertion sort ...\n");

    ll = insertion_sort(ll);

    printf("Verifying sort ...\n");

    llnode *cur = ll->head;
    while (cur && cur->next) {
        if (ll->compare(cur, cur->next) > 0) {
            fprintf(stderr, "\tVerification failed.\n");
            break;
        }

        cur = cur->next;
    }

    if (cur->next == NULL)
        printf("\tVerification successful.\n");

    printf("Freeing list ...\n");

    while (ll->count) {
        printf("\tFreeing element val %i ...\n", ((test_st *)(ll->head))->val);
        free_llnode(ll, ll->head);
    }

    printf("Creating list ...\n");
    ll = generate_llist(5);

    printf("Sorting list with quicksort ...\n");

    quicksort(ll, 0, ll->count - 1);

    printf("Verifying sort ...\n");

    cur = ll->head;
    while (cur && cur->next) {
        if (ll->compare(cur, cur->next) > 0) {
            fprintf(stderr, "\tVerification failed.\n");
            break;
        }

        cur = cur->next;
    }

    if (cur->next == NULL)
        printf("\tVerification successful.\n");

    printf("Freeing list ...\n");

    while (ll->count) {
        printf("\tFreeing element val %i ...\n", ((test_st *)(ll->head))->val);
        free_llnode(ll, ll->head);
    }

    printf("Completed.\n");

    return 0;
}
