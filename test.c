
typedef struct test_st test_st;

typedef struct test_st
{
    llnode hdr;
    int val;
} test_st;

int main(int argc, char *argv[])
{
    llist *ll = NULL;
    ll = malloc(sizeof(llist));
    memset(ll, 0, 0);

    printf("Allocating list ...\n");
    ll = malloc(sizeof(llist));
    memset(ll, 0, 0);

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
        del_llnode(ll, ll->head);
    }

    free_llist(ll);

    printf("Completed.\n");

    return 0;
}
