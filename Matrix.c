/********************************************************************************* 
 * * Kevin Kang, ktkang 
 * * 2022 Spring CSE101 PA4
 * * Matrix.c
 * * Implementation file for Matrix ADT
 * *********************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "Matrix.h"

typedef struct EntryObj *Entry;

typedef struct EntryObj {
  int col;
  double val;
} EntryObj;

typedef struct MatrixObj {
  int size;
  int NNZ;
  List *row;
} MatrixObj;

// Returns a reference to a new nXn Matrix object in the zero state.
Matrix newMatrix(int n) {
  Matrix M = malloc(sizeof(MatrixObj));
  if (M) {
    M->row = malloc((n+1)*sizeof(List));
    for (int i = 1; i <= n; i++) {
      M->row[i] = newList();
    }
    M->size = n;
    M->NNZ = 0;
  }
  return M;
}

// Creates and returns a new Entry.
Entry newEntry(int col, double val) {
  Entry N = malloc(sizeof(EntryObj));
  N->col = col;
  N->val = val;
  return N;
}

// Frees all heap memory associated with *pE, and sets *pE to NULL.
void freeEntry(Entry *pE) {
  if (pE != NULL && *pE != NULL) {
    free(*pE);
    *pE = NULL;
  }
}

// Frees heap memory associated with *pM, sets *pM to NULL.
void freeMatrix(Matrix* pM) {
  if (pM != NULL && *pM != NULL) {
    for (int i = 1; i <= (*pM)->size; i++) {
      List Row = (*pM)->row[i];
      if (length(Row) != 0) {
        moveFront(Row);
        while (index(Row) >= 0) {
          Entry E = get(Row);
          freeEntry(&E);
          moveNext(Row);
        }
      }
      freeList(&Row);
    }
  }
  free((*pM)->row);
  free(*pM);
  *pM = NULL;
}

// Return the size of square Matrix M.
int size(Matrix M) {
  return M->size;
}

// Return the number of non-zero elements in M.
int NNZ(Matrix M) {
  return M->NNZ;
}

// Return True (1) if matrices A and B are equal, false (0) otherwise.
int equals(Matrix A, Matrix B) {
  if (A->size != B->size || A->NNZ != B->NNZ) {
    return 0;
  }

  for (int i = 1; i <= size(A); i++) {
    List rowA = A->row[i];
    List rowB = B->row[i];
    moveFront(rowA);
    moveFront(rowB);
    if (length(rowA) != length(rowB)) {
      return 0;
    }
    while (index(rowA) >= 0 && index(rowA) >= 0) {
      Entry entryA = get(rowA);
      Entry entryB = get(rowB);
      if (entryA->col != entryB->col || entryA->val != entryB->val) {
        return 0;
      }
      moveNext(rowA);
      moveNext(rowB);
    }
  }
  return 1;
}

// Manipulation Procedures

// Re-sets M to the zero Matrix state.
void makeZero(Matrix M) {
  Entry E;
  M->NNZ = 0;
  for (int i = 1; i <= size(M); i++) {
    List Row = M->row[i];
    if (length(Row) == 0) {
      continue;
    }
    moveFront(Row);
    while (index(Row) >= 0) {
      E = get(Row);
      freeEntry(&E);
      moveNext(Row);
    }
    clear(Row);
  }
}

// Changes the ith row, jth column of M to the value x.
// Pre: 1 <= i <= size(M), 1 <= j <= size(M)
void changeEntry(Matrix M, int i, int j, double x) {
  if (i > M->size || i < 1) {
    printf("Matrix Error: ith row is out of range.\n");
    exit(EXIT_FAILURE);
  }
  if (j > M->size || j < 1) {
    printf("Matrix Error: jth collumn is out of range.\n");
    exit(EXIT_FAILURE);
  }
/*
  Entry E = newEntry(j, x);
  Entry curr;
  List R = M->row[i];

  if (length(R) == 0) {
    if (x != 0) {
      append(R, E);
      M->NNZ++;
    } else {
      freeEntry(&E);
      return;
    }
  } else {
    moveFront(R);
    while (index(R) >= 0) {
      curr = get(R);
      if (j > curr->col) {
        moveNext(R);
      } else {
        break;
      }
    }
    if (index(R) == -1) {
      if (x != 0) {
        append(R, E);
        M->NNZ++;  
      } else {
        freeEntry(&E);
      }
    } else if (j < ((Entry)get(R))->col) {
      if (x != 0) {
        insertBefore(R, E);
        M->NNZ++;
      } else {
        freeEntry(&E);
      }
    } else {
      if (x != 0) {
        freeEntry(&curr);
        set(R, E);
      } else {
        freeEntry(&curr);
        delete(R);
        M->NNZ--;
      }
    }
  }*/
  
  List R = M->row[i];
  Entry E = newEntry(j, x);
  if (x == 0) {
    freeEntry(&E);
  }

  if (length(R) == 0 && x != 0) {
    append(R, E);
    M->NNZ++;
  } else {
    moveFront(R);
    while (index(R) >= 0) {
      Entry T = get(R);
      if (T->col < j) {
        if (T == back(R) && x != 0) {
          insertAfter(R, E);
          M->NNZ++;
        } else {
          moveNext(R);
          continue;
        }
      } else if (T->col == j) {
        if (x == 0) {
          freeEntry(&T);
          delete(R);
          M->NNZ--;
        } else {
          freeEntry(&T);
          set(R, E);
        }
      } else if (T->col > j && x != 0) {
        insertBefore(R, E);
        M->NNZ++;
      }
      break;
    }
  }
}

// Matrix Arithmetic Operations

// Returns a reference to a new Matrix object having the same entries as A.
Matrix copy(Matrix A) {
  Matrix copy = newMatrix(size(A));
  for (int i = 1; i <= size(A); i++) {
    List rowC = A->row[i];
    moveFront(rowC);
    if (length(rowC) >= 0) {
      while (index(rowC) >= 0) {
        Entry E = get(rowC);
        changeEntry(copy, i, E->col, E->val);
        moveNext(rowC);
      }
    }
  }
  return copy;
}

// Returns a reference to a new matrix object representing the transpose of A.
Matrix transpose(Matrix A) {
  Matrix T = newMatrix(size(A));
  for (int i = 1; i <= size(A); i++) {
    List rowT = A->row[i];
    moveFront(rowT);
    if (length(rowT) >= 0) {
      while (index(rowT) >= 0) {
        Entry E = get(rowT);
        changeEntry(T, E->col, i, E->val);
        moveNext(rowT);
      }
    }
  }
  return T;
}

// Returns a reference to a new Matrix object representing xA
Matrix scalarMult(double x, Matrix A) {
  Matrix xA = newMatrix(size(A));
  for (int i = 1; i <= size(A); i++) {
    List Row = A->row[i];
    moveFront(Row);
    if (length(Row) >= 0) {
      while (index(Row) >= 0) {
        Entry E = get(Row);
        changeEntry(xA, i, E->col, x*E->val);
        moveNext(Row);
      }
    }
  }
  return xA;
}

// helper function to add rows
List sumList(List A, List B) {
  List sum = newList();
  Entry new;
  if (length(A) == 0 && length(B) == 0) {
    return sum;
  }
  if (length(A) == 0) {
    moveFront(B);
    while (index(B) >= 0) {
      new = get(B);
      Entry newE = newEntry(new->col, new->val);
      append(sum, newE);
      moveNext(B);
    }
    return sum;
  }
  if (length(B) == 0) {
    moveFront(A);
    while (index(A) >= 0) {
      new = get(A);
      Entry newE = newEntry(new->col, new->val);
      append(sum, newE);
      moveNext(A);
    }
    return sum;
  }

  moveFront(A);
  moveFront(B);
  while (index(A) >= 0 && index(B) >= 0) {
    Entry a = get(A);
    Entry b = get(B);
    if (a->col == b->col) {
      if ((a->val + b->val) != 0) {
        new = newEntry(a->col, a->val+b->val);
        append(sum, new);
        moveNext(A);
        moveNext(B);
      } else { 
        moveNext(A);
        moveNext(B);
      }
    } else {
      while (b->col < a->col) {
        new = newEntry(b->col, b->val);
        append(sum, new);
        moveNext(B);
        if (index(B) == -1) {
          break;
        }
        b = get(B);
      }
      while (a->col < b->col) {
        new = newEntry(a->col, a->val);
        append(sum, new);
        moveNext(A);
        if (index(A) == -1) {
          break;
        }
        a = get(A);
      }
    }
    if (index(B) == -1) {
      while (index(A) >= 0) {
        a = get(A);
        new = newEntry(a->col, a->val);
        append(sum, new);
        moveNext(A);
      }
    }
    if (index(A) == -1) {
      while (index(B) >= 0) {
        b = get(B);
        new = newEntry(b->col, b->val);
        append(sum, new);
        moveNext(B);
      }
    }
  }
  return sum;
}

// returns a reference to a new Matrix object representing A+B.
// pre: size(A)==size(B)
Matrix sum(Matrix A, Matrix B) {
  if (size(A) != size(B)) {
    printf("Matrix Error: Matrices A and B are of different dimensions.\n");
    exit(EXIT_FAILURE);
  }
  if (equals(A, B)) {
    Matrix eqm = scalarMult(2, A);
    return eqm;
  }
  Matrix sum = newMatrix(size(A));
  for (int i = 1; i <= size(A); i++) {
    freeList(&(sum->row[i]));
    List list_sum = sumList(A->row[i], B->row[i]);
    sum->row[i] = list_sum;
    sum->NNZ += length(list_sum);
  }
  return sum;
}

// returns a reference to a new Matrix object representing A-B.
// pre: size(A)==size(B)
Matrix diff(Matrix A, Matrix B) {
  if (size(A) != size(B)) {
    printf("Matrix Error: Matrices A and B are of different dimensions.\n");
    exit(EXIT_FAILURE);
  }
  Matrix negB = scalarMult(-1, B);
  Matrix diff = sum(A, negB);
  freeMatrix(&negB);
  return diff;
}

// product helper function to return product of 2 lists
double vectorDot(List A, List B) {
  double product = 0.0;
  moveFront(A);
  moveFront(B);

  while (index(A) >= 0 && index(B) >= 0) {
    Entry a = get(A);
    Entry b = get(B); 
    if (a->col == b->col) {
      product += a->val * b->val;
      moveNext(A);
      moveNext(B);
    } else {
      while (b->col < a->col) {
        moveNext(B);
        if (index(B) == -1) {
          break;
        }
        b = get(B);
      }
      while (a->col < b->col) {
        moveNext(A);
        if (index(A) == -1) {
          break;
        }
        a = get(A);
      }
    }
  }
  return product;
}

// returns a reference to a new Matrix object representing AB
// pre: size(A)==size(B)
Matrix product(Matrix A, Matrix B) {
  if (size(A) != size(B)) {
    printf("Matrix Error: Matrices A and B are of different dimensions.\n");
    exit(EXIT_FAILURE);
  }
  Matrix P = newMatrix(size(A));
  Matrix T = transpose(B);

  for (int i = 1; i <= size(A); i++) {
    List rowA = A->row[i];
    for (int j = 1; j <= size(T); j++) {
      List rowB = T->row[j];
      double list_product = vectorDot(rowA, rowB);
      changeEntry(P, i, j, list_product);
    }
  }
  freeMatrix(&T);
  return P;
}

// prints a string representation of Matrix M to filestream out.
void printMatrix(FILE* out, Matrix M) {
  for (int i = 1; i <= M->size; i++) {
    List R = M->row[i];
    if (length(R) == 0) {
      continue;
    }
    fprintf(out, "%d: ", i);
    for (moveFront(R); index(R) >= 0; moveNext(R)) {
      Entry E = get(R); 
      fprintf(out, "(%d, %0.1f) ", E->col, E->val); 
    }
    fprintf(out, "\n");
  }
}

