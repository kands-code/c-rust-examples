#pragma once
#ifndef __ARRAYLIST_H__
#define __ARRAYLIST_H__

/** ================
    Includes
 ================ */

#include "collections/utils.h"
#include <stddef.h>

/** ================
    Array List
 ================ */

typedef struct ArrayList {
  ElemType *data;
  size_t size;
  size_t capacity;
} ArrayList;

/**
 * @func InitArrayList : get an empty array list
 * @return   : empty array list [ ArrayList * ]
 * @descript : the default capacity is *16*
 */
ArrayList *InitArrayList(void);

/**
 * @func InitArrayListWithCapacity : get an empty array list
 * @param capacity : the initial capacity of
 *                   the array list   [ const size_t ]
 * @return         : empty array list [ ArrayList *  ]
 */
ArrayList *InitArrayListWithCapacity(const size_t capacity);

/**
 * @func InitArrayListFromArray : get an array list which has
 *                                stored all the element in the array
 * @param len   : length of the array [ const size_t ]
 * @param elems : the array           [ ElemType *   ]
 * @return      : the array list      [ ArrayList *  ]
 * @descript    : the default capacity of array list is
 *                double of the length of the array
 */
ArrayList *InitArrayListFromArray(const size_t len, ElemType elems[len]);

/**
 * @func DestroyArrayList : destroy the array list
 * @param linkedList : the array list [ ArrayList * ]
 */
void DestroyArrayList(ArrayList *arrayList);

/**
 * @func GetArrayListElement : get the element at a specific position
 * @param arrayList : the array list [ const ArrayList *  ]
 * @param position  : the position   [ const size_t       ]
 * @return          : the element    [ ElemType           ]
 * @descript        : function will crash when the position
 *                    is out of the boundary
 */
ElemType GetArrayListElement(const ArrayList *arrayList, const size_t position);

/**
 * @func SetArrayListElement : set the value of a specific position
 * @param arrayList : the array list [ ArrayList *    ]
 * @param value     : the value      [ const ElemType ]
 * @param position  : the position   [ const size_t   ]
 * @descript        : function will crash when the position
 *                    is out of the boundary
 */
void SetArrayListElement(ArrayList *arrayList, const ElemType value,
                         const size_t position);

/**
 * @func FindArrayListElement : get the element at a specific position
 * @param arrayList : the array list       [ ArrayList *    ]
 * @param elem      : value of the element [ const ElemType ]
 * @return          : the position         [ int            ]
 * @descript        : function will return -1 when the element
 *                    cannot find in the linked list
 */
int FindArrayListElement(const ArrayList *arrayList, const ElemType elem);

/**
 * @func InsertElementToArrayList : insert element to a specific position
 *                                  of the array list
 * @param arrayList : the array list                      [ ArrayList *    ]
 * @param value      : the value of element               [ const ElemType ]
 * @param position   : the position the element insert to [ const size_t   ]
 * @descript         : function will crash when the position
 *                     is out of the boundary
 */
void InsertElementToArrayList(ArrayList *arrayList, const ElemType value,
                              const size_t position);

/**
 * @func RemoveElementFromArrayList : remove the element at
 *                                    a specific position
 * @param arrayList : the array list      [ ArrayList *  ]
 * @param position  : the position        [ const size_t ]
 * @return          : the removed element [ ElemType     ]
 * @descript        : function will crash when the position
 *                    is out of the boundary
 */
ElemType RemoveElementFromArrayList(ArrayList *arrayList,
                                    const size_t position);

/**
 * @func PrintArrayList : print elements in array list
 * @param arrayList : the array list [ ArrayList * ]
 */
void PrintArrayList(ArrayList *arrayList);

/**
 * @func reverseArrayList : reverse a array list
 * @param arrayList : the array list          [ const ArrayList * ]
 * @return          : the reversed array list [ ArrayList *       ]
 */
ArrayList *reverseArrayList(const ArrayList *arrayList);

/**
 * @func reversedArrayList : reverse original array list
 * @param arrayList : the array list [ ArrayList * ]
 */
void reversedArrayList(ArrayList *arrayList);

#endif