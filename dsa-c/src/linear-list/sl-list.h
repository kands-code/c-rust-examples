#pragma once

/**********************************************************
 * Includes
 *********************************************************/
#include "utils.h"

/**********************************************************
 * Linked List
 **********************************************************/

/**
 * @type SL_Node : the node of linked list
 * @content data : the data in the node [ ElemType  ]
 * @content next : the next node        [ SL_Node * ]
 */
typedef struct SL_Node {
  ElemType data;
  struct SL_Node *next;
} SL_Node;

/**
 * @type SL_List : the single linked list
 */
typedef SL_Node *SL_List;

/**
 * @func SL_Sington : get a head pinter
 * @return L        : the linked list [ SL_List ]
 */
SL_List SL_Sington();
/**
 * @func SL_HeadInsert : initialize a list by head inseart method
 * @param L            : the linked list        [ SL_List ]
 * @param len          : the length of the list [ int     ]
 */
void SL_HeadInsert(SL_List L, int len);

/**
 * @func SL_TailInsert : initialize a list by tail insert method
 * @param L            : the linked list        [ SL_List ]
 * @param len          : the length of the list [ int     ]
 */
void SL_TailInsert(SL_List L, int len);

/**
 * @func SL_GetElem : find element by location
 * @param L         : the linked list [ SL_List   ]
 * @param loc       : the location    [ int       ]
 * @return p        : the node        [ SL_Node * ]
 * @descript        : function will return NULL when then location
 *                    is too small or too big
 */
SL_Node *SL_GetElem(SL_List L, int loc);

/**
 * @func SL_LocateElem : locate an element
 * @param L            : the linked list                     [ SL_List   ]
 * @param elem         : the element                         [ ElemType  ]
 * @return p           : the node which contains the element [ SL_Node * ]
 */
SL_Node *SL_LocateElem(SL_List L, ElemType elem);

/**
 * @func SL_InsertAfter : insert element after the node
 * @param L             : the linked list [ SL_List  ]
 * @param loc           : the location    [ int      ]
 * @param elem          : the element     [ ElemType ]
 */
void SL_InsertAfter(SL_List L, int loc, ElemType elem);

/**
 * @func SL_InsertBefore : insert element before the node
 * @param L              : the linked list [ SL_List  ]
 * @param loc            : the location    [ int      ]
 * @param elem           : the element     [ ElemType ]
 */
void SL_InsertBefore(SL_List L, int loc, ElemType elem);

/**
 * @func SL_DeleteElem : delete the element
 * @param L            : the linked list [ SL_List ]
 * @param loc          : the location    [ int     ]
 */
void SL_DeleteElem(SL_List L, int loc);

/**
 * @func SL_Length : get the length of a list
 * @param L        : the linked list [ SL_List ]
 * @return len     : the length      [ int     ]
 */
int SL_Length(SL_List L);
