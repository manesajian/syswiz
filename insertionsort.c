#include "insertionsort.h"

/* TODO: need to pass in a compare function */

llist *insertion_sort(llist *ll)
{
    llist *sorted = get_llist();

/* TODO: examine optimization which looks at both ends of the list to decide
   which end to start from. I.e., detects direction of possible orderedness. */

    while (ll->count > 0) {
        llnode *cur = pop_llist_head(ll);

        llnode *tmp = sorted->head;
        while (tmp) {
            //if (((compare)(tmp, cur)) <= 0) {
            //    add_llnode_before(sorted, tmp, cur);
            //    break;
            //}

            tmp = tmp->next;
        }

        if (tmp)
            add_llnode_tail(ll, cur);
    }

    return sorted;
}
