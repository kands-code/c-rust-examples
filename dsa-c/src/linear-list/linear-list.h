#pragma once

/**
 * @macroConst InitSize : the initial size of list
 */
#define InitSize 100

/**
 * @type OrderedListStatic
 * @content data    : the data of list     [ int * ]
 * @content length  : the length of `data` [ int   ]
 * @content maxSize : max size of `data`   [ int   ]
 */
typedef struct {
  int data[];
} OrderedListStatic;
