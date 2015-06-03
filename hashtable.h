#include <linkedlist.h>

#define NUM_BUCKETS 65536

typedef struct htable
{
    llist *keys[NUM_BUCKETS];
    int count;
} htable;

htable *get_htable();
void free_htable(htable *ht);

void add_item(htable *ht, char *key, void *value);
void del_item(htable *ht, char *key);
