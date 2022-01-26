#pragma once

/**
 * @macroConst InitSize : the initial size of list
 */
#define InitSize 100

/**
 * @type ElemType : the type of element in list
 */
typedef int ElemType;

/**********************************************************
 * Ordered List -- static
 **********************************************************/

/**
 * @type OrderedListStatic : static memory allocated ordered list
 * @content data           : the data of list     [ ElemType * ]
 * @content length         : the length of `data` [ ElemType   ]
 * @content maxSize        : max size of `data`   [ ElemType   ]
 */
typedef struct {
  ElemType data[InitSize];
  ElemType length;
  ElemType maxSize;
} OrderedListStatic;

/**
 * @func InitOLS : initialize a static ordered list
 * @param ols    : raw list [ OrderedListStatic * ]
 */
void InitOLS(OrderedListStatic *ols);

/**
 * @func LengthOfOLS : get the length of a static ordered list
 * @param ols        : static ordered list    [ OrderedListStatic ]
 * @return length    : the length of the list [ int               ]
 */
int LengthOfOLS(OrderedListStatic ols);

/**
 * @func LocateElemOfOLS : get the index of element in the static ordered list
 * @param ols            : the static ordered list  [ OrderedListStatic ]
 * @param elem           : the element              [ ElemType          ]
 * @return i             : the index of the element [ int               ]
 * @descript             : function return `-1` for not found
 */
int LocateElemOfOLS(OrderedListStatic ols, ElemType elem);

/**
 * @func GetElemOfOLS : get the element at the index in the static ordered list
 * @param ols         : the static ordered list          [ OrderedListStatic ]
 * @param i           : the index of the element         [ int               ]
 * @return elem       : the element which's index is `i` [ ElemType          ]
 * @descript          : function exit when the index is illegal
 */
ElemType GetElemOfOLS(OrderedListStatic ols, int i);

/**
 * @func ListInsertOfOLS : insert an element to the specified index of the list
 * @param ols            : the list           [ OrderedListStatic * ]
 * @param i              : the index          [ int                 ]
 * @param elem           : the element        [ ElemType            ]
 * @return result        : whether successful [ int                 ]
 * @descript             : function return -1 for failed and 1 for successful
 */
int ListInsertOfOLS(OrderedListStatic *ols, int i, ElemType elem);

/**
 * @func ListDeleteOfOLS : delete an element at the specified index of the list
 * @param ols            : the list               [ OrderedListStatic * ]
 * @param i              : the index              [ int                 ]
 * @param elem           : the pointer of element [ ElemType *          ]
 * @return result        : whether successful     [ int                 ]
 * @descript             : function return -1 for failed and 1 for successful,
 *                         deleted element will return by the `elem`
 */
int ListDeleteOfOLS(OrderedListStatic *ols, int i, ElemType *elem);

/**
 * @func PrintListOfOLS : print the list
 * @param ols           : the list [ OrderedListStatic ]
 */
void PrintListOfOLS(OrderedListStatic ols);

/**
 * @func EmptyOfOLS : test whether the list is empty
 * @param ols       : the list      [ OrderedListStatic ]
 * @return result   : whether empty [ int               ]
 * @descript        : function return 1 for empty and 0 for not empty
 */
int EmptyOfOLS(OrderedListStatic ols);

/// no function for DestoryList of OrderedListStatic type
