#include <stdio.h>
#include "linalgs.h"

int main() {
    printf("Hello, World!\n");
    Matrix * m = GetMatrix(2, 3, 2);
    PrintMatrix(m);

    return 0;
}
