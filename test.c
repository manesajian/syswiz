#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <sys/time.h>

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

int timeval_subtract(struct timeval *result, struct timeval *t2, struct timeval *t1)
{
    long int diff = (t2->tv_usec + 1000000 * t2->tv_sec) -
                    (t1->tv_usec + 1000000 * t1->tv_sec);
    result->tv_sec = diff / 1000000;
    result->tv_usec = diff % 1000000;

    return (diff < 0);
}

void timeval_print(struct timeval *tv)
{
    char buffer[30];
    time_t curtime;

    printf("%ld.%06ld", tv->tv_sec, tv->tv_usec);
    curtime = tv->tv_sec;
    strftime(buffer, 30, "%m-%d-%Y  %T", localtime(&curtime));
    printf(" = %s.%06ld\n", buffer, tv->tv_usec);
}

# define tvcmp(a, b, CMP)                                                \
  (((a).tv_sec == (b).tv_sec) ?                                          \
   ((a).tv_usec CMP (b).tv_usec) :                                       \
   ((a).tv_sec CMP (b).tv_sec))

const int NUM_SORTS = 3;
const int SIZE_SORT = 10000;
void test_sort(llist *(*sort)(llist *ll))
{
    struct timeval min_diff;
    struct timeval max_diff;

    printf("Performing %i sort(s) of %i elements ...\n", NUM_SORTS, SIZE_SORT);

    int i;
    for (i = 0; i < NUM_SORTS; ++i) {
        printf("\tStarting sort %i\n", i + 1);

        llist *ll = generate_llist(SIZE_SORT);

        struct timeval start;
        struct timeval stop;

        gettimeofday(&start, NULL);
        ll = sort(ll);
        gettimeofday(&stop, NULL);

        struct timeval diff;
        timeval_subtract(&diff, &stop, &start);

        if (i == 0)
            max_diff = min_diff = diff;
        else {
            if (tvcmp(diff, min_diff, <))
                min_diff = diff;
            if (tvcmp(diff, max_diff, >))
                max_diff = diff;
        }

        llnode *cur = ll->head;
        while (cur && cur->next) {
            if (ll->compare(cur, cur->next) > 0) {
                fprintf(stderr, "\t\tSort verification failed.\n");
                break;
            }

            cur = cur->next;
        }
        if (cur->next == NULL)
            printf("\t\tSort verification successful.\n");

        free_llist(ll);
    }

    printf("Min run: %ld.%06ld, Max run: %ld.%06ld\n", min_diff.tv_sec,
                                                       min_diff.tv_usec,
                                                       max_diff.tv_sec,
                                                       max_diff.tv_usec);
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


    test_sort(&insertion_sort);

/*
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
*/
    printf("Creating list ...\n");
    ll = generate_llist(5);

    printf("Sorting list with quicksort ...\n");

    quicksort(ll, 0, ll->count - 1);

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

    printf("Completed.\n");

    return 0;
}
