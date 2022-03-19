/**
 * linked-list.c -- function realization
 */
#include "sl-list.h"
#include "utils.h"
#include <stdio.h>
#include <stdlib.h>

/**********************************************************
 * Linked List
 **********************************************************/

/**
 * @func SL_Sington : get a head pinter
 * @return L        : the linked list [ SL_List ]
 */
SL_List SL_Sington() {
    SL_List L = (SL_List) calloc(1, sizeof(SL_Node));
    L->data = 0;
    L->next = NULL;
    return L;
}

/**
 * @func SL_HeadInsert : initialize a list by head insert method
 * @param L            : the linked list        [ SL_List ]
 * @param len          : the length of the list [ int     ]
 */
void SL_HeadInsert(SL_List L, int len) {
    SL_Node *node;
    int cnt = 0;
    ElemType data;
    while (cnt < len) {
        node = (SL_Node *) calloc(1, sizeof(SL_Node));
        scanf("%d", &data);
        node->data = data;
        node->next = L->next;
        L->next = node;
        cnt++;
    }
}

/**
 * @func SL_TailInsert : initialize a list by tail insert method
 * @param L            : the linked list        [ SL_List ]
 * @param len          : the length of the list [ int     ]
 */
void SL_TailInsert(SL_List L, int len) {
    /// rear pointer
    SL_List rear = L;
    SL_Node *node;
    int cnt = 0;
    ElemType data;
    while (cnt < len) {
        node = (SL_Node *) calloc(1, sizeof(SL_Node));
        scanf("%d", &data);
        node->data = data;
        rear->next = node;
        rear = node;
        cnt++;
    }
    rear->next = NULL;
}

/**
 * @func SL_GetElem : find element by location
 * @param L         : the linked list [ SL_List   ]
 * @param loc       : the location    [ int       ]
 * @return p        : the node        [ SL_Node * ]
 * @descript        : function will return NULL when then location
 *                    is too small or too big
 */
SL_Node *SL_GetElem(SL_List L, int loc) {
    if (loc == 0)
        return L;
    if (loc < 1)
        return NULL;

    SL_Node *p = L->next;
    int cnt = 1;
    while (p != NULL && cnt < loc) {
        p = p->next;
        cnt++;
    }
    return p;
}

/**
 * @func SL_LocateElem : locate an element
 * @param L            : the linked list                     [ SL_List   ]
 * @param elem         : the element                         [ ElemType  ]
 * @return p           : the node which contains the element [ SL_Node * ]
 */
SL_Node *SL_LocateElem(SL_List L, ElemType elem) {
    SL_Node *p = L->next;
    while (p != NULL && p->data != elem) {
        p = p->next;
    }
    return p;
}

/**
 * @func SL_InsertAfter : insert element after the node
 * @param L             : the linked list [ SL_List  ]
 * @param loc           : the location    [ int      ]
 * @param elem          : the element     [ ElemType ]
 */
void SL_InsertAfter(SL_List L, int loc, ElemType elem) {
    if (loc < 1) {
        puts("Please confirm the location!");
        return;
    }

    SL_Node *p = L->next;
    int cnt = 0;
    while (p->next != NULL && cnt < loc) {
        p = p->next;
        cnt++;
    }
    SL_Node *node = (SL_Node *) calloc(1, sizeof(SL_Node));
    node->data = elem;
    node->next = p->next;
    p->next = node;
}

/**
 * @func SL_InsertBefore : insert element before the node
 * @param L              : the linked list [ SL_List  ]
 * @param loc            : the location    [ int      ]
 * @param elem           : the element     [ ElemType ]
 */
void SL_InsertBefore(SL_List L, int loc, ElemType elem) {
    if (loc < 1) {
        puts("Please confirm the location!");
        return;
    }

    SL_Node *p = L;
    int cnt = 0;
    while (p->next != NULL && cnt < loc - 1) {
        p = p->next;
        cnt++;
    }
    SL_Node *node = (SL_Node *) calloc(1, sizeof(SL_Node));
    node->data = elem;
    node->next = p->next;
    p->next = node;
}

/**
 * @func SL_DeleteElem : delete the element
 * @param L            : the linked list [ SL_List ]
 * @param loc          : the location    [ int     ]
 */
void SL_DeleteElem(SL_List L, int loc) {
    if (loc < 1 && loc > SL_Length(L)) {
        puts("Please confirm the location!");
        return;
    }
    SL_Node *p = SL_GetElem(L, loc - 1);
    SL_Node *q = p->next;
    p->next = q->next;
    free(q);
}

/**
 * @func SL_Length : get the length of a list
 * @param L        : the linked list [ SL_List ]
 * @return len     : the length      [ int     ]
 */
int SL_Length(SL_List L) {
    SL_Node *p = L->next;
    int len = 0;
    while (p != NULL) {
        p = p->next;
        len++;
    }
    return len;
}
