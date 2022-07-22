/********************************************************************************* 
 * * Kevin Kang, ktkang 
 * * 2022 Spring CSE101 PA4
 * * MatrixTest.c
 * * Test file for Matrix ADT 
 * *********************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include"Matrix.h"

int main(int argc, char **argv) {
  printf("extra sum tests\n----------------------------\n");
  Matrix A = newMatrix(10);
  printf("A:\n");
  changeEntry(A, 1, 1, 4);
  changeEntry(A, 1, 2, 2);
  changeEntry(A, 1, 3, 0);
  changeEntry(A, 2, 1, 2);
  changeEntry(A, 3, 1, 0);
  changeEntry(A, 2, 2, 2);
  changeEntry(A, 3, 3, 0);
  printMatrix(stdout, A);
  
  printf("NNZ: %d\n", NNZ(A));
  printf("\n");

  Matrix Sum = sum(A, A);
  printMatrix(stdout, Sum);
  printf("NNZ: %d\n\n", NNZ(Sum));
  freeMatrix(&Sum);

  printf("B:\n");
  Matrix B = newMatrix(10);
  changeEntry(B, 1, 1, -4);
  changeEntry(B, 1, 2, 0);
  changeEntry(B, 2, 1, 0);
  changeEntry(B, 2, 2, -2);
  changeEntry(B, 2, 4, 2);
  changeEntry(B, 3, 1, 0);
  changeEntry(B, 3, 2, 2);
  changeEntry(B, 7, 8, 5);
  printMatrix(stdout, B);

  printf("\nSum A+B:\n");
  Matrix thesum = sum(A, B);
  printMatrix(stdout, thesum);
  printf("NNZ: %d\n", NNZ(thesum));

  freeMatrix(&A);
  freeMatrix(&B);
  freeMatrix(&thesum);

  Matrix mult = newMatrix(3);
  changeEntry(mult, 1, 1, 1);
  changeEntry(mult, 1, 2, 2); 
  changeEntry(mult, 1, 3, 3);
  changeEntry(mult, 2, 1, 4);
  changeEntry(mult, 2, 2, 5);   
  changeEntry(mult, 2, 3, 6);
  changeEntry(mult, 3, 1, 7);
  changeEntry(mult, 3, 2, 8);   
  changeEntry(mult, 3, 3, 9);
  printMatrix(stdout, mult);

  Matrix mult1 = newMatrix(3);
  changeEntry(mult1, 1, 1, 1);
  changeEntry(mult1, 1, 2, 2);
  changeEntry(mult1, 1, 3, 3);
  changeEntry(mult1, 2, 1, 3);
  changeEntry(mult1, 2, 2, 2);
  changeEntry(mult1, 2, 3, 1);
  changeEntry(mult1, 3, 1, 1);
  changeEntry(mult1, 3, 2, 2);
  changeEntry(mult1, 3, 3, 3);
  printMatrix(stdout, mult1);

  Matrix prod = product(mult, mult1);
  printMatrix(stdout, prod);

  freeMatrix(&mult);
  freeMatrix(&mult1);
  freeMatrix(&prod);

  printf("extra changeEntry tests\n-------------------------\n");
  A = newMatrix(10);
  changeEntry(A, 2, 1, 2);
  changeEntry(A, 3, 1, 5);
  changeEntry(A, 1, 2, 2);
  changeEntry(A, 1, 3, 5);
  changeEntry(A, 1, 1, 4);
  changeEntry(A, 2, 2, 2);
  changeEntry(A, 2, 5, 0);
  changeEntry(A, 2, 3, 0);
  changeEntry(A, 3, 3, 5);
  printMatrix(stdout, A);
  printf("\n");

  changeEntry(A, 1, 3, 0);
  changeEntry(A, 3, 1, 0);
  changeEntry(A, 3, 3, 0);
  printMatrix(stdout, A);
  printf("NNZ: %d\n", NNZ(A));
  freeMatrix(&A);

  printf("testing matrix\n--------------------------\n");
  A = newMatrix(3);
  printf("DEFAULT size: %d\n", size(A));
  printf("DEFAULT NNZ: %d\n\n", NNZ(A));

  printf("changeEntry Tests\n");
  changeEntry(A, 1, 1, 0);
  changeEntry(A, 1, 3, 3);
  changeEntry(A, 1, 2, 2);
  changeEntry(A, 1, 1, 0); // case1: Mij = 0, x = 0

  changeEntry(A, 2, 1, 0);
  changeEntry(A, 2, 1, 3); // case2: Mij = 0, x != 0
  changeEntry(A, 2, 2, 69);
  changeEntry(A, 2, 2, 2); // case3: Mij != 0, x != 0
  changeEntry(A, 2, 3, 1);

  changeEntry(A, 3, 1, 1);
  changeEntry(A, 3, 2, 2);
  changeEntry(A, 3, 3, 3);
  changeEntry(A, 3, 1, 0); // case4: Mij != 0, x = 0

  printf("setting entries in matrix\n");
    
  printf("Matrix A:\n");
  printMatrix(stdout, A);
  printf("\nAFTER size: %d\n", size(A));
  printf("AFTER NNZ: %d\n", NNZ(A));
  
  printf("\nequals tests\n---------------------------\n");
  B = newMatrix(3);
  changeEntry(B, 1, 1, 0);
  changeEntry(B, 1, 3, 3);
  changeEntry(B, 1, 2, 2);
  changeEntry(B, 1, 1, 0); 

  changeEntry(B, 2, 1, 0);
  changeEntry(B, 2, 1, 3); 
  changeEntry(B, 2, 2, 69);
  changeEntry(B, 2, 2, 2);   
  changeEntry(B, 2, 3, 1);

  changeEntry(B, 3, 1, 1);
  changeEntry(B, 3, 2, 2);
  changeEntry(B, 3, 3, 3);
  changeEntry(B, 3, 1, 0);
  
  printf("A:\n");
  printMatrix(stdout, A);
  printf("\n");
  printf("B:\n");
  printMatrix(stdout, B);
  printf("\n");

  if (equals(A, B)) {
    printf("SUCCESS A equals B\n");
  } else {
    printf("FAILURE A does not equal B\n");
  }

  printf("\nmakeZero tests\n--------------------------\n");
  makeZero(A);
  printMatrix(stdout, A);
  Matrix empty = newMatrix(3);
  if (equals(empty, A)) {
    printf("SUCCESS reset A to zero state\n");
  } else {
    printf("FAILURE did not reset A to zero state\n");
  }

  printf("\ntranspose and copy tests\n--------------------------\n");
  makeZero(B);
  changeEntry(B, 1, 1, 1);
  changeEntry(B, 1, 2, 2); 
  changeEntry(B, 1, 3, 3);
  changeEntry(B, 2, 1, 4);
  changeEntry(B, 2, 2, 5);   
  changeEntry(B, 2, 3, 6);
  changeEntry(B, 3, 1, 7);
  changeEntry(B, 3, 2, 8);   
  changeEntry(B, 3, 3, 9);

  printf("T:\n");
  printMatrix(stdout, B);
  printf("\n");

  Matrix Tcopy = copy(B);
  Matrix T = transpose(Tcopy);
  printf("transposed T:\n");
  printMatrix(stdout, T);
  printf("\n");
  
  printf("\nscalarMult tests\n--------------------------\n");
  Matrix sM = scalarMult(10, B);
  printf("scalar Mult of B:\n");
  printMatrix(stdout, sM);
  printf("\n");

  printf("\nsum tests\n---------------------------\n");
  Matrix sumCopy = copy(B);
  Matrix sumM = newMatrix(3);
  changeEntry(sumM, 1, 1, 1);
  changeEntry(sumM, 1, 2, 2);
  changeEntry(sumM, 1, 3, 3);
  changeEntry(sumM, 2, 1, 3);
  changeEntry(sumM, 2, 2, 2);
  changeEntry(sumM, 2, 3, 1);
  changeEntry(sumM, 3, 1, 1);
  changeEntry(sumM, 3, 2, 2);
  changeEntry(sumM, 3, 3, 3);

  printf("A:\n");
  printMatrix(stdout, sumCopy);
  printf("\nPLUS\n\nB:\n");
  printMatrix(stdout, sumM);
  printf("\nEQUALS\n\n");
  Matrix sum_matrix = sum(sumCopy, sumM);
  printMatrix(stdout, sum_matrix);
  
  printf("\nanother sum test\n");
  printf("A:\n");
  printMatrix(stdout, sumCopy);
  printf("\nPLUS\n\nB:\n");
  printMatrix(stdout, sumCopy);
  printf("\nEQUALS\n\n");
  Matrix id_matrix = sum(sumCopy, sumCopy);
  printMatrix(stdout, id_matrix);

  printf("\ndiff test\n--------------------------\n");
  printf("A:\n");
  printMatrix(stdout, sumCopy);
  printf("NNZ: %d\n", NNZ(sumCopy));
  printf("\nMINUS\n\nB;\n");
  printMatrix(stdout, sumM);
  printf("\nEQUALS\n\n");
  Matrix diff_matrix = diff(sumCopy, sumM);
  printMatrix(stdout, diff_matrix);
  printf("NNZ: %d\n", NNZ(diff_matrix));

  freeMatrix(&A);
  freeMatrix(&B);
  freeMatrix(&empty);
  freeMatrix(&T);
  freeMatrix(&Tcopy);
  freeMatrix(&sM);
  freeMatrix(&sumCopy);
  freeMatrix(&sumM);
  freeMatrix(&sum_matrix);
  freeMatrix(&diff_matrix);
  freeMatrix(&id_matrix);

  return 0;
}
