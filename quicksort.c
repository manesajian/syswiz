#include <stdio.h>

#include "quicksort.h"

/*
 * This implementation is an in-place non-stable sort currently.
 */

void quicksort(llist *ll, unsigned int lo, unsigned int hi)
{
    // Verify there is a compare and do bounds checking
    if (ll->compare == NULL || (int)(hi - lo) < 0 || hi > ll->count)
        return;

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
    pivot_idx -= (pivot_idx - lo) - count_left;

    int left_lo = pivot_idx - count_left;
    int left_hi = pivot_idx - 1;
    int right_lo = pivot_idx + 1;
    int right_hi = pivot_idx + count_right;

    // Sort sublist left of pivot
    if (left_hi - left_lo > 0)
        quicksort(ll, pivot_idx - count_left, pivot_idx - 1);

    // Sort sublist right of pivot
    if (right_hi - right_lo > 0)
        quicksort(ll, pivot_idx + 1, pivot_idx + count_right);
}
