/********************************************************************************* 
 * * Kevin Kang, ktkang 
 * * 2022 Spring CSE101 PA4
 * * Matrix.h
 * * Header file for Matrix ADT
 * *********************************************************************************/

#ifndef MATRIX_H_INCLUDE_
#define MATRIX_H_INCLUDE_

#include "List.h"

typedef struct MatrixObj* Matrix;

// Constructors-destructors
Matrix newMatrix(int n); // Returns a reference to a new nXn Matrix object in the zero state.
void freeMatrix(Matrix* pM); // Frees heap memory associated with *pM, sets *pM to NULL.

// Access functions
int size(Matrix M); // Return the size of square Matrix M.
int NNZ(Matrix M);  // Return the number of non-zero elements in M. 
int equals(Matrix A, Matrix B); // Returns true if matrices A and B are equal, false otherwise.

// Manipulation procedures
void makeZero(Matrix M);  // Re-sets M to the zero Matrix state.
void changeEntry(Matrix M, int i, int j, double x);  // Changes the ith row, jth column of M
                                                    // to the value x.
                                                    // Pre: 1<=i<=size(M), 1<=j<=size(M)
// Matrix Arithmetic operations
Matrix copy(Matrix A); // Returns a reference to a new Matrix object having the same entries as A.
Matrix transpose(Matrix A); // Returns a reference to a new transposed Matrix of A.
Matrix scalarMult(double x, Matrix A); // Returns a reference to a new Matrix representing xA.
Matrix sum(Matrix A, Matrix B); // Returns a reference to a new Matrix object representing A+B.
                                // Pre: size(A)==size(B)
Matrix diff(Matrix A, Matrix B);  // Returns a reference to a new Matrix object representing A-B.
                                  // Pre: size(A)==size(B)
Matrix product(Matrix A, Matrix B); // Returns a reference to a new Matrix object representing AB.
                                    // Pre: size(A)==size(B)
void printMatrix(FILE* out, Matrix M);  // Prints string representation of Matrix M to FILE out.

#endif
