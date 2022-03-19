/**
 * linear-algebra.c -- function realization
 */

/************************************************************
 * Includes
 ************************************************************/

#include "linalgs.h"
#include <stdio.h>
#include <stdlib.h>

/************************************************************
 * Init the matrix
 ************************************************************/

/**
 * @func InitMatrix : initialize a matrix
 * @param r         : the row number    [ int      ]
 * @param c         : the column number [ int      ]
 * @param d         : the default value [ double   ]
 * @return mat      : the matrix        [ Matrix * ]
 * @descript        : function will return null for illegal size
 */
Matrix *InitMatrix(int r, int c, double d) {
    if (r < 1 || c < 1) { // size must greater equal than [1, 1]
        return NULL;
    }

    Matrix *mat = calloc(1, sizeof(Matrix));
    mat->data = calloc(r * c, sizeof(double));

    mat->size[0] = r;
    mat->size[1] = c;

    for (int i = 0; i < r * c; ++i) {
        mat->data[i] = d;
    }

    return mat;
}

/**
 * @func InitMatrixFromArray : initialize a matrix from an array
 * @param r                  : the row number      [ int      ]
 * @param c                  : the column number   [ int      ]
 * @param len                : the length of array [ int      ]
 * @param arr                : the array           [ double * ]
 * @return mat               : the matrix          [ Matrix * ]
 * @descript                 : function will return null for illegal size,
 *                             if size is bigger than array, fill with `0`,
 *                             if size is smaller than array, truncate
 */
Matrix *InitMatrixFromArray(int r, int c, int len, double *arr) {
    if (r < 1 || c < 1) { // size must greater equal than [1, 1]
        return NULL;
    }

    Matrix *mat = calloc(1, sizeof(Matrix));
    mat->data = calloc(r * c, sizeof(double));

    mat->size[0] = r;
    mat->size[1] = c;

    int m = len < r * c ? len : r * c;
    for (int i = 0; i < m; ++i) {
        mat->data[i] = arr[i];
    }

    if (len < r * c) {
        for (int i = len; i < r * c; ++i) {
            mat->data[i] = 0.0;
        }
    }

    return mat;
}

/**
 * @func InitMatrixByInput : initialize a matrix by user input
 * @return mat             : the matrix [ Matrix * ]
 * @descript               : input element separate by blank character;
 *                           function will return wrong matrix,
 *                           if user do not follow the correct way of typing
 */
Matrix *InitMatrixByInput() {
    int r, c;
    printf("Input the Size of Matrix (r, c): ");
    scanf("%d %d", &r, &c);

    Matrix *mat = calloc(1, sizeof(Matrix));

    mat->data = calloc(r * c, sizeof(double));

    mat->size[0] = r;
    mat->size[1] = c;

    puts("Input the Elements: ");
    for (int i = 0; i < r; ++i) {
        for (int j = 0; j < c; ++j) {
            scanf("%lf", &(mat->data[i * c + j]));
        }
    }

    return mat;
}

/**
 * @func DestroyMatrix : destroy matrix
 * @param mat          : the matrix [ Matrix * ]
 */
void DestroyMatrix(Matrix *mat) {
    free(mat->data);
    free(mat);
}

/************************************************************
 * Matrix tools
 ************************************************************/

/**
 * @func PrintMatrixP : print the matrix with precision
 * @param mat         : the matrix    [ Matrix * ]
 * @param p           : the precision [ int      ]
 */
void PrintMatrixP(Matrix *mat, int p) {
    puts("<<Matrix");
    for (int i = 0; i < mat->size[0]; ++i) {
        printf(" [ ");
        for (int j = 0; j < mat->size[1]; ++j) {
            printf("%-*.*f ", p + 3, p, mat->data[mat->size[1] * i + j]);
        }
        printf("]\n");
    }
    puts("Matrix>>");
}

/**
 * @func PrintMatrix : print the matrix
 * @param mat        : the matrix [ Matrix * ]
 * @descript         : default precision is 2
 */
void PrintMatrix(Matrix *mat) { PrintMatrixP(mat, 2); }

/**
 * @func GetMatrixVal : get the element from the matrix by coordinate
 * @param mat         : the matrix [ Matrix * ]
 * @param r           : the row    [ int      ]
 * @param c           : the column [ int      ]
 * @return val        : the value  [ double   ]
 * @descript          : function will exit when the coordinate is illegal
 */
double GetMatrixVal(Matrix *mat, int r, int c) {
    if (r < 0 || r >= mat->size[0] || c < 0 || c >= mat->size[1]) {
        fputs("Wrong Position!\n", stderr);
        exit(EXIT_FAILURE);
    }
    return mat->data[r * mat->size[1] + c];
}

/**
 * @func SetMatrixVal : get the element from the matrix by coordinate
 * @param mat         : the matrix [ Matrix * ]
 * @param r           : the row    [ int      ]
 * @param c           : the column [ int      ]
 * @param v           : the value  [ double   ]
 * @descript          : function will exit when the coordinate is illegal
 */
void SetMatrixVal(Matrix *mat, int r, int c, double v) {
    if (r < 0 || r >= mat->size[0] || c < 0 || c >= mat->size[1]) {
        fputs("Wrong Position!\n", stderr);
        exit(EXIT_FAILURE);
    }

    mat->data[r * mat->size[1] + c] = v;
}

/************************************************************
 * some matrix manipulations
 ************************************************************/

/**
 * @func MatAdd : add up two matrices
 * @param m1    : the first matrix        [ Matrix * ]
 * @param m2    : the second matrix       [ Matrix * ]
 * @return mat  : the sum of two matrices [ Matrix * ]
 * @descript    : the size must be matched
 */
Matrix *MatAdd(Matrix *m1, Matrix *m2) {
    if (m1->size[0] != m2->size[0] || m1->size[1] != m2->size[1]) {
        fputs("The Sizes Are Not Matched\n", stderr);
        exit(EXIT_FAILURE);
    }

    Matrix *mat = InitMatrix(m1->size[0], m2->size[1], 0);

    for (int i = 0; i < m1->size[0]; ++i) {
        for (int j = 0; j < m2->size[1]; ++j) {
            SetMatrixVal(mat, i, j, GetMatrixVal(m1, i, j) + GetMatrixVal(m2, i, j));
        }
    }

    return mat;
}

/**
 * @func MatSub : subtract m2 from m1
 * @param m1    : the first matrix        [ Matrix * ]
 * @param m2    : the second matrix       [ Matrix * ]
 * @return mat  : the diff of two matrices [ Matrix * ]
 * @descript    : the size must be matched
 */
Matrix *MatSub(Matrix *m1, Matrix *m2) {
    if (m1->size[0] != m2->size[0] || m1->size[1] != m2->size[1]) {
        fputs("The Sizes Are Not Matched\n", stderr);
        exit(EXIT_FAILURE);
    }

    Matrix *mat = InitMatrix(m1->size[0], m2->size[1], 0);

    for (int i = 0; i < m1->size[0]; ++i) {
        for (int j = 0; j < m2->size[1]; ++j) {
            SetMatrixVal(mat, i, j, GetMatrixVal(m1, i, j) - GetMatrixVal(m2, i, j));
        }
    }

    return mat;
}

/**
 * @func MatMul : multiply m1 and m2
 * @param m1    : the first matrix            [ Matrix * ]
 * @param m2    : the second matrix           [ Matrix * ]
 * @return mat  : the product of two matrices [ Matrix * ]
 * @descript    : the size must be matched
 */
Matrix *MatMul(Matrix *m1, Matrix *m2) {
    if (m1->size[1] != m2->size[0]) {
        fputs("The Sizes Are Not Matched\n", stderr);
        exit(EXIT_FAILURE);
    }

    Matrix *mat = InitMatrix(m1->size[0], m2->size[1], 0);

    for (int i = 0; i < m1->size[0]; ++i) {
        for (int j = 0; j < m2->size[1]; ++j) {
            double sum = 0;
            for (int k = 0; k < m1->size[1]; ++k) {
                sum += GetMatrixVal(m1, i, k) * GetMatrixVal(m2, k, j);
            }
            SetMatrixVal(mat, i, j, sum);
        }
    }

    return mat;
}

/************************************************************
 * some vector manipulations -- based on matrix manipulations
 ************************************************************/

/**
 * @func VecAdd : add up two vectors
 * @param v1    : the first vector       [ Matrix * ]
 * @param v2    : the second vector      [ Matrix * ]
 * @return vec  : the sum of two vectors [ Matrix * ]
 * @descript    : vectors has orientation
 *                if orientations are not matched
 *                function will exit with failure
 */
Matrix *VecAdd(Matrix *v1, Matrix *v2) {
    if ((v1->size[0] != 1 && v1->size[1] != 1) ||
        (v2->size[0] != 1 && v2->size[1] != 1)) {
        fputs("The Function Is for Vectors!\n", stderr);
        exit(EXIT_FAILURE);
    }

    return MatAdd(v1, v2);
}
