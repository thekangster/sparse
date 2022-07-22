/********************************************************************************* 
 * * Kevin Kang, ktkang 
 * * 2022 Spring CSE101 PA4
 * * Sparce.c
 * * Client file for Sparce
 * *********************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include"Matrix.h"

int main(int argc, char **argv) {
  FILE *in, *out;
  int n, a, b;
  if (argc != 3) {
    printf("Usage %s <input file> <output file>\n", argv[0]);
    exit(1);
  }
  in = fopen(argv[1], "r");
  if (in == NULL) {
    printf("Unable to open file %s for reading\n", argv[1]);
    exit(1);
  }
  out = fopen(argv[2], "w");
  if (out == NULL) {
    printf("Unable to open file %s for writing\n", argv[2]);
    exit(1);
  }
  int row, column;
  double value;
  Matrix A, B;
  int line = 0;

  fscanf(in, "%d %d %d\n", &n, &a, &b);
  A = newMatrix(n);
  B = newMatrix(n);
  while (!feof(in)) {
    fscanf(in, "%d %d %lf", &row, &column, &value);
    line += 1;
    if (line <= a) {
      changeEntry(A, row, column, value);
    } else {
      changeEntry(B, row, column, value);
    }
  }

  fprintf(out, "A has %d non-zero entries:\n", NNZ(A));
  printMatrix(out, A);
  fprintf(out, "\nB has %d non-zero entries:\n", NNZ(B));
  printMatrix(out, B);
  
  fprintf(out, "\n(1.5)*A =\n");
  Matrix SM = scalarMult(1.5, A);
  printMatrix(out, SM);

  fprintf(out, "\nA+B =\n");
  Matrix sumAB = sum(A, B);
  printMatrix(out, sumAB);

  fprintf(out, "\nA+A =\n");
  Matrix sumAA = sum(A, A);
  printMatrix(out, sumAA);

  fprintf(out, "\nB-A =\n");
  Matrix diffBA = diff(B, A);
  printMatrix(out, diffBA);

  fprintf(out, "\nA-A =\n");
  Matrix diffAA = diff(A, A);
  printMatrix(out, diffAA);

  fprintf(out, "\nTranspose(A) =\n");
  Matrix T = transpose(A);
  printMatrix(out, T);

  fprintf(out, "\nA*B =\n");
  Matrix prodAB = product(A, B);
  printMatrix(out, prodAB);
  
  fprintf(out, "\nB*B =\n");
  Matrix prodBB = product(B, B);
  printMatrix(out, prodBB);

  fclose(in);
  fclose(out);
  freeMatrix(&A);
  freeMatrix(&B);
  freeMatrix(&SM);
  freeMatrix(&sumAB);
  freeMatrix(&sumAA);
  freeMatrix(&diffBA);
  freeMatrix(&diffAA);
  freeMatrix(&T);
  freeMatrix(&prodAB);
  freeMatrix(&prodBB);
  return 0;
}

