# Linear Algebra

In this repo, I want to do some common linear algebra calculate, such as find a inverse of a matrix or calculate the determinant of a matrix

## Definitions

Some definitions in the lib

### STRUCT

The `struct` in this lib

|struct|description|
|:--:|:--:|
|`__MATRIX`|The matrix struct|
|`__VECTOR`|The vector struct|

### ALIAS

Some type aliases

|name|alias|
|:--:|:--:|
|`__MATRIX`|`matrix`|
|`__VECTOR`|`vector`|

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
#include <stdio.h>

int main(void) {
    double a[] = {1, -1, -1, 2, -1, -3, 3, 2, 5};
    matrix * matA = matrixGetMatrixByArray(3, 3, a);
    // print the original matrix
    matrixPrint(matA);
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
gcc -o test test.c LinearAlgebra.c
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

See source code, the comments are comprehensive

*if the orientations of two vectors are not equal, they cannot do vector calculate, must turn them into matrices*
