#include <stdio.h>

#include "heapsort.h"

llist *heapsort(llist *ll)
{
    // Can't sort without a compare function.
    if (ll->compare == NULL)
        return ll;

    return NULL;
}
