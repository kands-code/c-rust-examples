/**
 * sq-list.c -- function realization
 */
#include "sq-list.h"
#include <stdio.h>
#include <stdlib.h>

/**********************************************************
 * Sequence List
 **********************************************************/

/**
 * @func SqList_Init : initialize a sequence list
 * @param sqlist     : raw list [ SqList * ]
 */
void SqList_Init(SqList *sqlist) {
  sqlist->maxSize = InitSize;
  sqlist->length = 0;

  sqlist->data = malloc(sqlist->maxSize * sizeof(ElemType));

  for (int i = 0; i < sqlist->maxSize; ++i) {
    sqlist->data[i] = 0;
  }
}

/**
 * @func SqList_Length : get the length of sequence list
 * @param sqlist       : the sequence list      [ SqList ]
 * @return length      : the length of the list [ int    ]
 */
int SqList_Length(SqList sqlist) { return sqlist.length; }

/**
 * @func SqList_LocateElem : get the index of element in the sqlist
 * @param sqlist           : the sequence list        [ SqList   ]
 * @param elem             : the element              [ ElemType ]
 * @return i               : the index of the element [ int      ]
 * @descript               : function return `-1` for not found
 */
int SqList_LocateElem(SqList sqlist, ElemType elem) {
  for (int i = 0; i < sqlist.length; ++i) {
    if (sqlist.data[i] == elem) {
      return i;
    }
  }

  return -1;
}

/**
 * @func SqList_GetElem : get the element at the index in the sqlist
 * @param sqlist        : the sequence list                [ SqList   ]
 * @param i             : the index of the element         [ int      ]
 * @return elem         : the element which's index is `i` [ ElemType ]
 * @descript            : function exit when the index is illegal
 */
ElemType SqList_GetElem(SqList sqlist, int i) {
  if (i < 0 || i > sqlist.length) {
    exit(EXIT_FAILURE);
  }
  return sqlist.data[i];
}

/**
 * @func SqList_ListInsert : insert an element to the list
 * @param sqlist           : the list           [ SqList * ]
 * @param i                : the index          [ int      ]
 * @param elem             : the element        [ ElemType ]
 * @return result          : whether successful [ int      ]
 * @descript               : function return -1 for failed and 1 for successful
 */
int SqList_ListInsert(SqList *sqlist, int i, ElemType elem) {
  if (i < 0 || i >= sqlist->maxSize) {
    puts("Illegal Index!");
    return -1;
  } else if (sqlist->maxSize <= sqlist->length + 1) {
    puts("The List is Full!");
    return -1;
  }

  // move element backward
  for (int j = sqlist->length - 1; j >= i; --j) {
    sqlist->data[j + 1] = sqlist->data[j];
  }
  sqlist->length = sqlist->length + 1 > i + 1 ? sqlist->length + 1 : i + 1;
  sqlist->data[i] = elem;
  return 1;
}

/**
 * @func SqList_ListDelete : delete an element from the list
 * @param sqlist           : the list               [ SqList *   ]
 * @param i                : the index              [ int        ]
 * @param elem             : the pointer of element [ ElemType * ]
 * @return result          : whether successful     [ int        ]
 * @descript               : function return -1 for failed and 1 for successful,
 *                           deleted element will return by the `elem`
 */
int SqList_ListDelete(SqList *sqlist, int i, ElemType *elem) {
  if (i < 0 || i >= sqlist->length) {
    puts("Illegal Index");
    return -1;
  }

  *elem = sqlist->data[i];
  for (int j = i; j < sqlist->length - 1; ++j) {
    sqlist->data[j] = sqlist->data[j + 1];
  }
  sqlist->length--;
  return 1;
}

/**
 * @func SqList_PrintList : print the list
 * @param sqlist          : the list [ SqList ]
 */
void SqList_PrintList(SqList sqlist) {
  for (int i = 0; i < sqlist.length; ++i) {
    printf("%d ", sqlist.data[i]);
  }
  puts("\b\n");
}

/**
 * @func SqList_Empty : test whether the list is empty
 * @param sqlist      : the list      [ SqList ]
 * @return result     : whether empty [ int    ]
 * @descript          : function return 1 for empty and 0 for not empty
 */
int SqList_Empty(SqList sqlist) { return sqlist.length == 0; }

/**
 * @func SqList_DestoryList : destory the sequence list
 * @param sqlist            : the list [ SqList * ]
 * @descript                : the function will exit when the sqlist is null
 */
void SqList_DestoryList(SqList *sqlist) { free(sqlist->data); }
