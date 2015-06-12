#include <stdio.h>

#include "insertionsort.h"

/*
 * This implementation is not a stable sort currently.
 */

llist *insertion_sort(llist *ll)
{
    // Can't sort without a compare function.
    if (ll->compare == NULL)
        return ll;

    llist *sorted = get_llist();
    sorted->compare = ll->compare;

/* TODO: examine optimization which looks at both ends of the list to decide
   which end to start from. I.e., detects direction of possible orderedness. */

    while (ll->count > 0) {
        llnode *cur = pop_llist_head(ll);

/* TODO: examine similar optimization to previous which decides which end
   of the ordered list to start searching from (or possibly starts from the
   middle). */

        llnode *tmp = sorted->head;
        while (tmp) {
            if (ll->compare(tmp, cur) >= 0) {
                add_llnode_before(sorted, tmp, cur);
                break;
            }

            tmp = tmp->next;
        }

        // tmp will be NULL if end of sorted list was reached
        if (!tmp)
            add_llnode_tail(sorted, cur);
    }

    return sorted;
}
