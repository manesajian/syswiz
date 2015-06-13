#include <stdio.h>

#include "heapsort.h"

llist *heapsort(llist *ll)
{
    // Can't sort without a compare function.
    if (ll->compare == NULL)
        return ll;



    return NULL;

/*
    llist *sorted = get_llist();

    while (ll->count > 0) {
        llnode *cur = pop_llist_head(ll);

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

*/
}
