/**
 * linear-list.c -- function realization
 */
#include "linear-list.h"
#include "../utilities/utilities.h"
#include <stdio.h>
#include <stdlib.h>

/**********************************************************
 * Ordered List -- static
 **********************************************************/

/**
 * @func InitOLS : initialize a static ordered list
 * @param ols    : raw list [ OrderedListStatic * ]
 */
void InitOLS(OrderedListStatic *ols) {
  ols->maxSize = InitSize;
  ols->length = 0;
  // clear data
  for (int i = 0; i < ols->maxSize; ++i) {
    ols->data[i] = 0;
  }
}

/**
 * @func LengthOfOLS : get the length of a static ordered list
 * @param ols        : static ordered list [ OrderedListStatic ]
 * @return length    : the length of the list
 */
int LengthOfOLS(OrderedListStatic ols) { return ols.length; }

/**
 * @func LocateElemOfOLS : get the index of element in the static ordered list
 * @param ols            : the static ordered list  [ OrderedListStatic ]
 * @param elem           : the element              [ ElemType          ]
 * @return i             : the index of the element [ int               ]
 * @descript function return `-1` for not found
 */
int LocateElemOfOLS(OrderedListStatic ols, ElemType e) {
  for (int i = 0; i < ols.length; ++i) {
    if (ols.data[i] == e) {
      return i;
    }
  }

  return -1;
}

/**
 * @func GetElemOfOLS : get the element at the index in the static ordered list
 * @param ols         : the static ordered list          [ OrderedListStatic ]
 * @param i           : the index of the element         [ int               ]
 * @return elem       : the element which's index is `i` [ ElemType          ]
 * @descript function exit when the index is illegal
 */
ElemType GetElemOfOLS(OrderedListStatic ols, int i) {
  if (i < 0 || i > ols.length) {
    exit(EXIT_FAILURE);
  }
  return ols.data[i];
}

/**
 * @func ListInsertOfOLS : insert an element to the specified index of the list
 * @param ols            : the list           [ OrderedListStatic * ]
 * @param i              : the index          [ int                 ]
 * @param elem           : the element        [ ElemType            ]
 * @return result        : whether successful [ int                 ]
 * @descript function return -1 for failed and 1 for successful
 */
int ListInsertOfOLS(OrderedListStatic *ols, int i, ElemType elem) {
  if (i < 0 || i >= ols->maxSize) {
    puts("Illegal Index!");
    return -1;
  } else if (ols->maxSize <= ols->length + 1) {
    puts("The List is Full!");
    return -1;
  }

  // move element backward
  for (int j = ols->length - 1; j >= i; --j) {
    ols->data[j + 1] = ols->data[j];
  }
  ols->length = max(ols->length + 1, i + 1);
  ols->data[i] = elem;
  return 1;
}

/**
 * @func ListDeleteOfOLS : delete an element at the specified index of the list
 * @param ols            : the list               [ OrderedListStatic * ]
 * @param i              : the index              [ int                 ]
 * @param elem           : the pointer of element [ ElemType *          ]
 * @return result        : whether successful     [ int                 ]
 * @descript function return -1 for failed and 1 for successful,
 *           deleted element will return by the `elem`
 */
int ListDeleteOfOLS(OrderedListStatic *ols, int i, ElemType *elem) {
  if (i < 0 || i >= ols->length) {
    puts("Illegal Index");
    return -1;
  }

  *elem = ols->data[i];
  for (int j = i; j < ols->length - 1; ++j) {
    ols->data[j] = ols->data[j + 1];
  }
  ols->length--;
  return 1;
}

/**
 * @func PrintListOfOLS : print the list
 * @param ols           : the list [ OrderedListStatic ]
 */
void PrintListOfOLS(OrderedListStatic ols) {
  for (int i = 0; i < ols.length; ++i) {
    printf("%d ", ols.data[i]);
  }
  puts("\b\n");
}

/**
 * @func EmptyOfOLS : test whether the list is empty
 * @param ols       : the list      [ OrderedListStatic ]
 * @return result   : whether empty [ int               ]
 * @descript function return 1 for empty and 0 for not empty
 */
int EmptyOfOLS(OrderedListStatic ols) { return ols.length == 0; }
