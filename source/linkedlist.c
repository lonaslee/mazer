#include "linkedlist.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

LinkedList *llnew(int idata, void *vdata) {
    LinkedList *ll = calloc(1, sizeof(LinkedList));
    ll->len = 1;
    ll->first = calloc(1, sizeof(Node));
    ll->first->idata = idata;
    ll->first->vdata = vdata;
    ll->last = ll->first;
    return ll;
}

void lldel(LinkedList *llist) {
    for (Node *cur = llist->first; cur != NULL;) {
        Node *next = cur->next;
        free(cur);
        cur = next;
    }
    free(llist);
}

Node *llgetitem(LinkedList *llist, int idx) {
    int i = 0;
    for (Node *cur = llist->first; cur != NULL; cur = cur->next, i++)
        if (i == idx) return cur;
    return NULL;
}

void llprint(LinkedList *llist) {
    printf("\nlen: %d\n", llist->len);
    int i;
    Node *cur;
    for (i = 0, cur = llist->first; cur != NULL; cur = cur->next, i++)
        printf("%d:  int - %d;  void - %p\n", i, cur->idata, cur->vdata);
}

void llappend(LinkedList *llist, int idata, void *vdata) {
    llist->len++;
    llist->last->next = calloc(1, sizeof(Node));
    llist->last = llist->last->next;
    llist->last->idata = idata;
    llist->last->vdata = vdata;
}

void llshave(LinkedList *llist, int *idatabuf, void **vdatabuf) {
    llist->len--;
    Node *slast;
    for (slast = llist->first; slast->next->next != NULL; slast = slast->next)
        ;
    if (idatabuf) *idatabuf = slast->next->idata;
    if (vdatabuf) *vdatabuf = slast->next->vdata;
    free(slast->next);
    slast->next = NULL;
}

void llinsert(LinkedList *llist, int idx, int idata, void *vdata) {
    llist->len++;
    Node *new = calloc(1, sizeof(Node));
    new->idata = idata;
    new->vdata = vdata;
    if (idx == 0) {
        Node *prevfirst = llist->first;
        llist->first = new;
        new->next = prevfirst;
    } else {
        Node *prev = llgetitem(llist, idx - 1);
        Node *prevhere = prev->next;
        prev->next = new;
        new->next = prevhere;
    }
}

void llremove(LinkedList *llist, int idx, int *idatabuf, void **vdatabuf) {
    llist->len--;
    if (idx == 0) {
        if (idatabuf) *idatabuf = llist->first->idata;
        if (vdatabuf) *vdatabuf = llist->first->vdata;
        Node *newfirst = llist->first->next;
        free(llist->first);
        llist->first = newfirst;
    } else {
        Node *prev = llgetitem(llist, idx - 1);
        if (idatabuf) *idatabuf = prev->next->idata;
        if (vdatabuf) *vdatabuf = prev->next->vdata;
        Node *newhere = prev->next->next;
        free(prev->next);
        prev->next = newhere;
    }
}

LinkedList *llcopy(LinkedList *llist) {
    LinkedList *cpy = llnew(0, NULL);
    Node *old;
    Node *new;
    for (old = llist->first, new = cpy->first; old != NULL; old = old->next) {
        llappend(cpy, 0, NULL);
        memcpy(&new->idata, &old->idata, sizeof(int));
        memcpy(&new->vdata, &old->vdata, sizeof(void *));
    }
    llremove(cpy, 0, NULL, NULL);
    return cpy;
}

int llicount(LinkedList *llist, int ivalue, int *indices) {
    int count = 0;
    int i = 0;
    for (Node *cur = llist->first; cur != NULL; cur = cur->next, i++)
        if (cur->idata == ivalue) {
            if (indices) indices[count] = i;
            count++;
        }
    return count;
}

int llvcount(LinkedList *llist, void *vvalue, int *indices) {
    int count = 0;
    int i = 0;
    for (Node *cur = llist->first; cur != NULL; cur = cur->next, i++)
        if (cur->vdata == vvalue) {
            if (indices) indices[count] = i;
            count++;
        }
    return count;
}

int lliindex(LinkedList *llist, int ivalue) {
    int i = 0;
    for (Node *cur = llist->first; cur != NULL; cur = cur->next, i++)
        if (cur->idata == ivalue) return i;
    return -1;
}

int llvindex(LinkedList *llist, void *vvalue) {
    int i = 0;
    for (Node *cur = llist->first; cur != NULL; cur = cur->next, i++) {
        if (cur->vdata == vvalue) return i;
    }
    return -1;
}

void llreverse(LinkedList *llist) {
    Node *prev, *cur, *next;
    for (prev = NULL, cur = llist->first, next = NULL; cur != NULL; prev = cur, cur = next) {
        next = cur->next;
        cur->next = prev;
    }
    llist->first = prev;
    llist->last = llgetitem(llist, llist->len - 1);
}

void llpop(LinkedList *llist, int *idatabuf, void **vdatabuf) {
    llremove(llist, rand() % llist->len, idatabuf, vdatabuf);
}

void llclear(LinkedList *llist) {
    for (Node *cur = llist->first; cur != NULL; cur = cur->next) {
        cur->idata = 0;
        cur->vdata = NULL;
    }
}

int *llitolist(LinkedList *llist, int *iarr, int start, int stop) {
    if (start == -1) start = 0;
    if (stop == -1) stop = llist->len;
    Node *cur;
    int i;
    for (i = 0, cur = llgetitem(llist, start); cur != NULL && i < stop; cur = cur->next, i++)
        iarr[i] = cur->idata;
    return iarr;
}

void **llvtolist(LinkedList *llist, void **varr, int start, int stop) {
    if (start == -1) start = 0;
    if (stop == -1) stop = llist->len;
    Node *cur;
    int i;
    for (i = 0, cur = llgetitem(llist, start); cur != NULL && i < stop; cur = cur->next, i++)
        varr[i] = cur->vdata;
    return varr;
}
