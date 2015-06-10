#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "linkedlist.h"

llist *get_llist()
{ 
    llist *ll = malloc(sizeof(llist));
    memset(ll, 0, 0);
    return ll;
}

void free_llist(llist *ll)
{
    while (ll->head) {
        free_llnode(ll, ll->head);
    }

    free(ll);
}

void add_llnode(llist *ll, llnode *node)
{
    if (ll->tail) {
        ll->tail->next = node;
        node->prev = ll->tail;
        node->next = NULL;
        ll->tail = node;
        ll->count += 1;
    }
    else {
        ll->head = ll->tail = node;
        node->prev = node->next = NULL;
        ll->count += 1;
    }
}

void add_llnode_head(llist *ll, llnode *node)
{
    if (ll->head) {
        ll->head->prev = node;
        node->prev = NULL;
        node->next = ll->head;
        ll->head = node;
        ll->count += 1;
    }
    else {
        ll->head = ll->tail = node;
        node->prev = node->next = NULL;
        ll->count += 1;
    }
}

void add_llnode_tail(llist *ll, llnode *node)
{
    add_llnode(ll, node);
}

void add_llnode_before(llist *ll, llnode *cur, llnode *new)
{
    if (cur->prev) {
        cur->prev->next = new;
        new->prev = cur->prev;
        new->next = cur;
        cur->prev = new;
        ll->count += 1;
    }
    else {
        ll->head->prev = new;
        new->prev = NULL;
        new->next = ll->head;
        ll->head = new;
        ll->count += 1;
    }
}

void add_llnode_after(llist *ll, llnode *cur, llnode *new)
{
    if (cur->next) {
        cur->next->prev = new;
        new->next = cur->next;
        new->prev = cur;
        cur->next = new;
        ll->count += 1;
    }
    else {
        ll->tail->next = new;
        new->prev = ll->tail;
        new->next = NULL;
        ll->tail = new;
        ll->count += 1;
    }
}

void move_llnode_up(llist *ll, llnode *node)
{
    if (!node->prev)
        return;

    // Start with 4 nodes possibly affected
    llnode *top = node->prev->prev;
    llnode *above = node->prev;
    llnode *below = node;
    llnode *bottom = node->next;

    if (top)
        top->next = node;
    else
        ll->head = node;

    node->prev = top;
    above->prev = node;
    node->next = above;
    below = above;
    above = node;

    if (bottom)
        bottom->prev = below;
    else
        ll->tail = bottom;

    below->next = bottom;
}

void move_llnode_down(llist *ll, llnode *node)
{
    if (!node->next)
        return;

    // Start with 4 nodes possibly affected
    llnode *top = node->prev;
    llnode *above = node;
    llnode *below = node->next;
    llnode *bottom = node->next->next;

    if (bottom)
        bottom->prev = node;
    else
        ll->tail = node;

    node->next = bottom;
    below->next = node;
    node->prev = below;
    above = below;
    below = node;

    if (top)
        top->next = above;
    else
        ll->head = above;

    above->prev = top;
}

llnode *pop_llist_head(llist *ll)
{
    return pop_llist_node(ll, ll->head);
}

llnode *pop_llist_tail(llist *ll)
{
    return pop_llist_node(ll, ll->tail);
}

llnode *pop_llist_node(llist *ll, llnode *node)
{
    if (node->prev)
        node->prev->next = node->next;
    else
        ll->head = node->next;

    if (node->next)
        node->next->prev = node->prev;
    else
        ll->tail = node->prev;

    ll->count -= 1;

    return node;
}

void free_llnode(llist *ll, llnode *node)
{
    pop_llist_node(ll, node);

    if (node->data)
        free(node->data);

    free(node);
}
