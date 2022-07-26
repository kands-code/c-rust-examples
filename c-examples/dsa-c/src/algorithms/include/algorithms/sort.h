#pragma once
#ifndef __SORT_H__
#define __SORT_H__

/** ================
    Includes
 ================ */

#include <stddef.h>

/** ================
    Sort
 ================ */

/**
 * @func bubbleSort : sort array by bubble sort algorithm
 * @param array : the array          [ void * ]
 * @param type  : the size of type   [ size_t ]
 * @param start : the start of range [ size_t ]
 * @param end   : the end of range   [ size_t ]
 * @descript    : this function will change the original array
 */
void bubbleSort(void *array, size_t type, size_t start, size_t end);

#endif