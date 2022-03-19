#pragma once

/**********************************************************
 * Includes
 *********************************************************/
#include "utils.h"

/**
 * @macroConst InitSize : the initial size of list
 */
/// #define InitSize 101

/**********************************************************
 * Sequence List
 **********************************************************/

/**
 * @type SqList     : sequence list
 * @content data    : the data of list     [ ElemType * ]
 * @content length  : the length of `data` [ ElemType   ]
 * @content maxSize : max size of `data`   [ ElemType   ]
 */
typedef struct SqList {
  /// static version
  /// ElemType data[InitSize];
  ElemType *data;
  ElemType length;
  ElemType maxSize;
} SqList;

/**
 * @func SqList_Init : initialize a sequence list
 * @param sqlist     : raw list [ SqList * ]
 * @param maxSize    : the max size of sequence list
 */
void SqList_Init(SqList *sqlist, int maxSize);

/**
 * @func SqList_Length : get the length of sequence list
 * @param sqlist       : the sequence list      [ SqList ]
 * @return length      : the length of the list [ int    ]
 */
int SqList_Length(SqList sqlist);

/**
 * @func SqList_LocateElem : get the index of element in the sqlist
 * @param sqlist           : the sequence list        [ SqList   ]
 * @param elem             : the element              [ ElemType ]
 * @return i               : the index of the element [ int      ]
 * @descript               : function return `-1` for not found
 */
int SqList_LocateElem(SqList sqlist, ElemType elem);

/**
 * @func SqList_GetElem : get the element at the index in the sqlist
 * @param sqlist        : the sequence list                [ SqList   ]
 * @param i             : the index of the element         [ int      ]
 * @return elem         : the element which's index is `i` [ ElemType ]
 * @descript            : function exit when the index is illegal
 */
ElemType SqList_GetElem(SqList sqlist, int i);

/**
 * @func SqList_ListInsert : insert an element to the list
 * @param sqlist           : the list           [ SqList * ]
 * @param i                : the index          [ int      ]
 * @param elem             : the element        [ ElemType ]
 * @return result          : whether successful [ int      ]
 * @descript               : function return -1 for failed and 1 for successful
 */
int SqList_ListInsert(SqList *sqlist, int i, ElemType elem);

/**
 * @func SqList_ListDelete : delete an element from the list
 * @param sqlist           : the list               [ SqList *   ]
 * @param i                : the index              [ int        ]
 * @param elem             : the pointer of element [ ElemType * ]
 * @return result          : whether successful     [ int        ]
 * @descript               : function return -1 for failed and 1 for successful,
 *                           deleted element will return by the `elem`
 */
int SqList_ListDelete(SqList *sqlist, int i, ElemType *elem);

/**
 * @func SqList_PrintList : print the list
 * @param sqlist          : the list [ SqList ]
 */
void SqList_PrintList(SqList sqlist);

/**
 * @func SqList_Empty : test whether the list is empty
 * @param sqlist      : the list      [ SqList ]
 * @return result     : whether empty [ int    ]
 * @descript          : function return 1 for empty and 0 for not empty
 */
int SqList_Empty(SqList sqlist);

/**
 * @func SqList_DestroyList : destroy the sequence list
 * @param sqlist            : the list [ SqList * ]
 * @descript                : the function will exit when the sqlist is null
 */
void SqList_DestroyList(SqList *sqlist);
