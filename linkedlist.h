#ifndef INCLUDED_LINKEDLIST_H
#define INCLUDED_LINKEDLIST_H

typedef struct llnode llnode;
typedef struct llist llist;

typedef struct llnode
{
    llnode *prev;
    llnode *next;
    void *data;
} llnode;

typedef struct llist
{
    llnode *head;
    llnode *tail;
    int count;
    int (*compare)(llnode *, llnode *);
} llist;

llist *get_llist();
void free_llist(llist *ll);
void add_llnode(llist *ll, llnode *node);
void add_llnode_head(llist *ll, llnode *node);
void add_llnode_tail(llist *ll, llnode *node);
void add_llnode_before(llist *ll, llnode *cur, llnode *new);
void add_llnode_after(llist *ll, llnode *cur, llnode *new);
void move_llnode_up(llist *ll, llnode *node);
void move_llnode_down(llist *ll, llnode *node);
llnode *pop_llist_head(llist *ll);
llnode *pop_llist_tail(llist *ll);
llnode *pop_llist_node(llist *ll, llnode *node);
void free_llnode(llist *ll, llnode *node);

#endif
