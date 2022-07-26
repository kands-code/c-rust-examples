/// Array List

/** ================
    Includes
 ================ */

#include "collections/ArrayList.h"

#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

#include "collections/utils.h"

/** ================
    Realization
 ================ */

/**
 * @func InitArrayList : get an empty array list
 * @return   : empty array list [ ArrayList * ]
 * @descript : the default capacity is *16*
 */
ArrayList *InitArrayList(void) { return InitArrayListWithCapacity(16); }

/**
 * @func InitArrayListWithCapacity : get an empty array list
 * @param capacity : the initial capacity of
 *                   the array list   [ const size_t ]
 * @return         : empty array list [ ArrayList *  ]
 */
ArrayList *InitArrayListWithCapacity(const size_t capacity) {
  ArrayList *arrayList = calloc(1, sizeof(ArrayList));

  arrayList->capacity = capacity;
  arrayList->data = calloc(arrayList->capacity, sizeof(ElemType));
  arrayList->size = 0;

  for (int i = 0; i < arrayList->capacity; ++i) {
    arrayList->data[i] = 0;
  }

  return arrayList;
}

/**
 * @func InitArrayListFromArray : get an array list which has
 *                                stored all the element in the array
 * @param len   : length of the array [ const size_t ]
 * @param elems : the array           [ ElemType *   ]
 * @return      : the array list      [ ArrayList *  ]
 * @descript    : the default capacity of array list is
 *                double of the length of the array
 */
ArrayList *InitArrayListFromArray(const size_t len, ElemType elems[len]) {
  ArrayList *arrayList = InitArrayListWithCapacity(len * 2);
  for (int i = 0; i < len; ++i) {
    arrayList->data[i] = elems[i];
  }
  arrayList->size = len;

  return arrayList;
}

/**
 * @func DestroyArrayList : destroy the array list
 * @param linkedList : the array list [ ArrayList * ]
 */
void DestroyArrayList(ArrayList *arrayList) {
  if (arrayList != NULL) {
    free(arrayList->data);
    free(arrayList);
  }
}

/**
 * @func GetArrayListElement : get the element at a specific position
 * @param arrayList : the array list [ const ArrayList *  ]
 * @param position  : the position   [ const size_t       ]
 * @return          : the element    [ ElemType           ]
 * @descript        : function will crash when the position
 *                    is out of the boundary
 */
ElemType GetArrayListElement(const ArrayList *arrayList,
                             const size_t position) {
  if (position > arrayList->size || position < 1) {
    fprintf(stderr, "Out of the boundary!");
    exit(1);
  }
  return arrayList->data[position - 1];
}

/**
 * @func SetArrayListElement : set the value of a specific position
 * @param arrayList : the array list [ ArrayList *    ]
 * @param value     : the value      [ const ElemType ]
 * @param position  : the position   [ const size_t   ]
 * @descript        : function will crash when the position
 *                    is out of the boundary
 */
void SetArrayListElement(ArrayList *arrayList, const ElemType value,
                         const size_t position) {
  if (position > arrayList->size || position < 1) {
    fprintf(stderr, "Out of the boundary!");
    exit(1);
  }
  arrayList->data[position - 1] = value;
}

/**
 * @func FindArrayListElement : get the element at a specific position
 * @param arrayList : the array list       [ ArrayList *    ]
 * @param elem      : value of the element [ const ElemType ]
 * @return          : the position         [ int            ]
 * @descript        : function will return -1 when the element
 *                    cannot find in the linked list
 */
int FindArrayListElement(const ArrayList *arrayList, const ElemType elem) {
  if (arrayList->size < 1) {
    fprintf(stderr, "Empty Array List");
    return -1;
  }
  for (int i = 0; i < arrayList->size; ++i) {
    if (arrayList->data[i] == elem) {
      return i + 1;
    }
  }
  return -1;
}

/**
 * @func ExpandArrayListCapacity : expand the capacity of array list
 * @param arrayList : array list [ ArrayList * ]
 */
void ExpandArrayListCapacity(ArrayList *arrayList) {
  ElemType *newData = calloc(arrayList->capacity * 2, sizeof(ElemType));
  for (int i = 0; i < arrayList->capacity * 2; ++i) {
    newData[i] = 0;
  }

  for (int i = 0; i < arrayList->size; ++i) {
    newData[i] = arrayList->data[i];
  }
  ElemType *trash = arrayList->data;
  arrayList->data = newData;
  arrayList->capacity *= 2;
  free(trash);
}

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
                              const size_t position) {
  if (position < 1) {
    fprintf(stderr, "Out of the boundary!");
    exit(1);
  }
#define MAX(a, b) (a) > (b) ? (a) : (b)
  while (arrayList->capacity < position - 1) {
    ExpandArrayListCapacity(arrayList);
  }
  for (int i = arrayList->capacity - 1; i > position - 1; --i) {
    arrayList->data[i] = arrayList->data[i - 1];
  }
  arrayList->data[position - 1] = value;
  arrayList->size = MAX(arrayList->size + 1, position);
#undef MAX
}

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
                                    const size_t position) {
  if (position < 1 || position > arrayList->size) {
    fprintf(stderr, "Out of the boundary!");
    exit(1);
  }

  ElemType val = arrayList->data[position - 1];

  for (int i = position - 1; i < arrayList->size - 1; ++i) {
    arrayList->data[i] = arrayList->data[i + 1];
  }
  arrayList->data[arrayList->size - 1] = 0;
  arrayList->size--;

  return val;
}

/**
 * @func PrintArrayList : print elements in array list
 * @param arrayList : the array list [ ArrayList * ]
 */
void PrintArrayList(ArrayList *arrayList) {
  printf("[");
  for (int i = 0; i < arrayList->size; ++i) {
    printf("%d, ", arrayList->data[i]);
  }
  printf("\b\b]\n");
}

/**
 * @func reverseArrayList : reverse a array list
 * @param arrayList : the array list          [ const ArrayList * ]
 * @return          : the reversed array list [ ArrayList *       ]
 */
ArrayList *reverseArrayList(const ArrayList *arrayList) {
  ArrayList *revArrayList = InitArrayListWithCapacity(arrayList->capacity);
  for (size_t i = arrayList->size; i > 0; --i) {
    InsertElementToArrayList(revArrayList, GetArrayListElement(arrayList, i),
                             arrayList->size - i + 1);
  }
  return revArrayList;
}

/**
 * @func reversedArrayList : reverse original array list
 * @param arrayList : the array list [ ArrayList * ]
 */
void reversedArrayList(ArrayList *arrayList) {
  for (size_t i = 1; i < arrayList->size / 2 + 1; ++i) {
    ElemType temp = GetArrayListElement(arrayList, i);
    SetArrayListElement(
        arrayList, GetArrayListElement(arrayList, arrayList->size - i + 1), i);
    SetArrayListElement(arrayList, temp, arrayList->size - i + 1);
  }
}