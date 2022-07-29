# Matrix

> C Version

This library is an implementation about matrix operations

If something wrong, please tell me.

## Simple Examples

```c
#include "matrix/matrix-ext.h"
#include "matrix/matrix.h"
#include <stdio.h>

int main() {
  Matrix *A = InitMatrixByInput();
  Matrix *b = InitMatrixByInput();

  puts("Solve Linear Equations:");
  puts("A:");
  PrintMatrix(A);
  puts("b:");
  PrintMatrix(b);

  puts("result:");
  Matrix *res = SolveLinearEqs(A, b);
  PrintMatrix(res);

  DestroyMatrix(A);
  DestroyMatrix(b);
  DestroyMatrix(res);

  return 0;
}
```

compile it

```bash
clang main.c -o main -L./ -lmatrix
```

output

```text
In[2]:= ./main 
Out[2]:= 
Input the Size of Matrix (r, c): 3 3
Input the Elements: 
3 2 4
2 2 3
1 2 3
Input the Size of Matrix (r, c): 3 1
Input the Elements: 
500 190 90
Solve Linear Equations:
A:

<<Matrix
 [ 3.00  2.00  4.00  ]
 [ 2.00  2.00  3.00  ]
 [ 1.00  2.00  3.00  ]
Matrix>>

b:

<<Matrix
 [ 500.00 ]
 [ 190.00 ]
 [ 90.00 ]
Matrix>>

result:

<<Matrix
 [ 100.00 ]
 [ -320.00 ]
 [ 210.00 ]
Matrix>>
```