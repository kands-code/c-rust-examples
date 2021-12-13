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

## API

|function|parameters|return|description|
|:--:|:--:|:--:|:--:|
|`getNumberOfInversions`|`len : int`, `arr : int *`|the number of inversions of the array `int`|calculate the number of inversions of an array|
|`matrixInit`|rows `i : int`, columns `j : int`|a matrix pointer `matrix *`|matrix init|
