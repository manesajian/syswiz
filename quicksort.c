#include <stdio.h>

#include "quicksort.h"

llist *quick_sort(llist *ll, unsigned int lo, unsigned int hi)
{
    // Verify there is a compare and do bounds checking
    if (ll->compare == NULL || ((int)hi - lo) <= 1 || hi > ll->count)
        return ll;

    int pivot_idx = lo + ((hi - lo) / 2);
    llnode *pivot = get_llnode_idx(ll, pivot_idx);

    // Remember the node to the right of the pivot
    llnode *post_pivot = pivot->next;

    int i;
    int count_left = 0;
    int count_right = 0;
    llnode *cur;

    cur = pivot->prev;
    for (i = 0; i < pivot_idx - lo; ++i) {
        if (ll->compare(cur, pivot) > 0) {
            llnode *prev = cur->prev;
            add_llnode_after(ll, pivot, pop_llist_node(ll, cur));
            cur = prev;
            count_right += 1;
        }
        else {
            cur = cur->prev;
            count_left += 1;
        }
    }

    cur = post_pivot;
    for (i = 0; i < hi - pivot_idx; ++i) {
        if (ll->compare(cur, pivot) < 0) {
            llnode *next = cur->next;
            add_llnode_before(ll, pivot, pop_llist_node(ll, cur));
            cur = next;
            count_left += 1;
        }
        else {
            cur = cur->next;
            count_right += 1;
        }
    }

    // Adjust pivot_idx to new value
    pivot_idx += count_left - (pivot_idx - lo);

    // Sort sublist left of pivot
    quick_sort_pivot(ll, pivot_idx - count_left, pivot_idx - 1);

    // Sort sublist right of pivot
    quick_sort_pivot(ll, pivot_idx + 1, pivot_idx + count_right);
}
