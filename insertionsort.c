/* TODO: need to pass in a compare function */

llist *insertion_sort(llist *lst)
{
    llist *sorted = get_llist();

/* TODO: examine optimization which looks at both ends of the list to decide
   which end to start from. I.e., detects direction of possible orderedness. */

    while (lst->count > 0) {
        llnode *cur = pop_llist_head(llist *ll);

        llnode *tmp = sorted->head;
        while(tmp) {
            if ((compare)(tmp, cur)) <= 0) {
                add_llnode_before(sorted, tmp, cur);
                break;
            }

            tmp = tmp->next;
        }

        if (tmp)
            add_llnode_tail(cur);
    }

    return sorted;
}
