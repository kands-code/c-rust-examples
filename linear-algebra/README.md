# Linear Algebra

In this repo, I want to do some common linear algebra calculate, such as find a inverse of a matrix or calculate the determinant of a matrix

## Definitions

Some definitions in the lib

### STRUCT

The `struct` in this lib

|struct|description|
|:--:|:--:|
|`__MATRIX`|The matrix struct|

> The vector is also a matrix

### ALIAS

Some type aliases

|name|alias|
|:--:|:--:|
|`__MATRIX`|`matrix`|
|`matrix *`|`matp`|

### CONSTANT

Some constants

|name|type|value|description|
|:--:|:--:|:--:|:--:|
|`esp`|`double`|`1e-6`|The minimum difference|

## Simple Example

The minimum test

```c
// -- test.c

#include "LinearAlgebra.h"
#include "libs/Eq.h"
#include "libs/TinyThings.h"
#include <stdio.h>

int main(void) {
    double a[] = {1, -1, -1, 2, -1, -3, 3, 2, 5};
    matrix * matA = matrixGetMatrixByArray(3, 3, a);
    // print the original matrix
    matrixPrint(mat);
    puts("============");
    // print the upright-triangle formed matrix
    matrixPrint(matrixToUprightTriangleForm(matA));
    puts("============");
    // print the inverse matrix
    matrixPrint(matrixInverse(matA));
    puts("============");
    // print the determinant of the matrix
    printf("%.3f\n", matrixDeterminant(matA));
    puts("============");

    return 0;
}
```

compiler

```bash
gcc -o test test.c LinearAlgebra.c libs/Eq.c libs/TinyThings.c
```

the output

```
1.000   -1.000  -1.000
2.000   -1.000  -3.000
3.000   2.000   5.000
============
1.000   -1.000  -1.000
0.000   1.000   -1.000
0.000   0.000   13.000
============
0.077   0.231   0.154
-1.462  0.615   0.077
0.538   -0.385  0.077
============
13.000
============
```

## API

|function|parameters|return|description|
|:--:|:--:|:--:|:--:|
|`getNumberOfInversions`|the length of array<br>`len : int`,<br>the array<br>`arr : int *`|the number of inversions of the array<br>`int`|calculate the number of inversions of an array|
|`matrixInit`|rows<br>`i : int`,<br>columns<br>`j : int`|a matrix pointer<br>`matrix *`|matrix init|
|`matrixGetDiagonalMatrix`|the size of the matrix<br>`len :int`<br>the diagonal of the matrix<br>`diag : double *`|a diagonal matrix<br>`matrix *`|get a diagonal matrix|
|`matrixGetIndentityMatrix`|the size of the matrix<br>`len : int`|the identity matrix<br>`matrix *`|get an identity matrix|
|`matrixGetMatrixByArray`|the first dimension, rows<br>`r : int`<br>the second dimension, columns<br>`c : int`<br>the array<br>`arr : double *`|the matrix<br>`matrix *`|init a matrix from an array|
