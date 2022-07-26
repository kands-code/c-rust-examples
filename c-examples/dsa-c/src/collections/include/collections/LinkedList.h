#pragma once
#ifndef __LINKEDLIST_H__
#define __LINKEDLIST_H__

/** ================
    Includes
 ================ */

#include "collections/utils.h"
#include <stddef.h>

/** ================
    Linked List
 ================ */

/**
 * @type Node : node of linkede list
 * @content val  : value of node [ ElemType ]
 * @content next : next node     [ Node *   ]
 */
typedef struct Node {
  ElemType val;
  struct Node *next;
} Node;

/**
 * @type LinkedList : linked list
 * @content head : head node of the linked list [ Node * ]
 * @content size : function that return
                   the size of linked list      [ size_t ]
 */
typedef struct LinkedList {
  Node *head;
  size_t size;
} LinkedList;

/**
 * @func InitNode : get a node
 * @param value : value the node hold [ ElemType ]
 * @return      : a node
 */
Node *InitNode(ElemType value);

/**
 * @func InitLinkedList : get an empty linked list
 * @return : empty linked list [ LinkedList * ]
 */
LinkedList *InitLinkedList(void);

/**
 * @func InitLinkedListByHead : get an linked list by head insert method
 * @param len : the length of the linked list [ const size_t ]
 * @return    : initialized linked list       [ LinkedList * ]
 */
LinkedList *InitLinkedListByHead(const size_t len);

/**
 * @func InitLinkedListByTail : get an linked list by head tail method
 * @param len : the length of the linked list [ const size_t ]
 * @return    : initialized linked list       [ LinkedList * ]
 */
LinkedList *InitLinkedListByTail(const size_t len);

/**
 * @func InitLinkedListFromArray : get an linked list which has
 *                                 stored all the element in the array
 * @param len   : length of the array [ const size_t ]
 * @param elems : the array           [ ElemType *   ]
 * @return      : the linked list     [ LinkedList * ]
 */
LinkedList *InitLinkedListFromArray(const size_t len, ElemType elems[len]);

/**
 * @func DestoryLinkedList : destory the linked list
 * @param linkedList : the linked list [ LinkedList * ]
 */
void DestoryLinkedList(LinkedList *linkedList);

/**
 * @func GetLinkedListElement : get the element at a specific position
 * @param linkedList : the linked list [ const LinkedList * ]
 * @param position   : the position    [ const size_t       ]
 * @return           : the element     [ ElemType           ]
 * @descript         : function will crash when the position
 *                     is out of the boundary
 */
ElemType GetLinkedListElement(const LinkedList *linkedList,
                              const size_t position);

/**
 * @func SetLinkedListElement : set the value of a specific position
 * @param linkedList : the linked list [ LinkedList *   ]
 * @param value      : the value       [ const ElemType ]
 * @param position   : the position    [ const size_t   ]
 * @descript         : function will crash when the position
 *                     is out of the boundary
 */
void SetLinkedListElement(LinkedList *linkedList, const ElemType value,
                          const size_t position);

/**
 * @func FindLinkedListElement : get the element at a specific position
 * @param linkedList : the linked list      [ LinkedList *   ]
 * @param elem       : value of the element [ const ElemType ]
 * @return           : the position         [ int            ]
 * @descript         : function will return -1 when the element
 *                     cannot find in the linked list
 */
int FindLinkedListElement(const LinkedList *linkedList, const ElemType elem);

/**
 * @func InsertElementToLinkedList : insert element to a specific position
 *                                   of the linked list
 * @param linkedList : the linked list                    [ LinkedList *   ]
 * @param value      : the value of element               [ const ElemType ]
 * @param position   : the position the element insert to [ const size_t   ]
 * @descript         : function will crash when the position
 *                     is out of the boundary
 */
void InsertElementToLinkedList(LinkedList *linkedList, const ElemType value,
                               const size_t position);

/**
 * @func RemoveElementFromLinkedList : remove the element at
 *                                     a specific position
 * @param linkedList : the linked list     [ LinkedList * ]
 * @param position   : the position        [ const size_t ]
 * @return           : the removed element [ ElemType     ]
 * @descript         : function will crash when the position
 *                     is out of the boundary
 */
ElemType RemoveElementFromLinkedList(LinkedList *linkedList,
                                     const size_t position);

/**
 * @func PrintLinkedList : print elements in linked list
 * @param linkedList : the linked list [ LinkedList * ]
 */
void PrintLinkedList(LinkedList *linkedList);

/**
 * @func reverseLinkedList : reverse a linked list
 * @param linkedList : the linked list          [ const LinkedList * ]
 * @return           : the reversed linked list [ LinkedList *       ]
 */
LinkedList *reverseLinkedList(const LinkedList *linkedList);

/**
 * @func reversedLinkedList : reverse original linked list
 * @param linkedList : the linked list [ LinkedList * ]
 */
void reversedLinkedList(LinkedList *linkedList);

#endif