/********************************************************************************* 
 * * Kevin Kang, ktkang 
 * * 2022 Spring CSE101 PA4
 * * ListTest.c
 * * Test file for List ADT 
 * *********************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include"List.h"

int main(int argc, char **argv) {
  int arr[] = {0,1,2,3,4,5,6,7,8,9,10};
  List A = newList();
  List B = newList();
  int i;

  for(i=1; i<=10; i++){
    append(A,&arr[i]);
  }
  for(i=1; i<=10; i++){
    prepend(B,&arr[i]);
  }

  moveFront(A);
  moveBack(B);
  printf("A's Index: %d, Length: %d, Cursor: %d\nB's Index: %d Length: %d\n", index(A), length(A), index(A), index(B), length(B));

  for(moveFront(A); index(A)>=0; moveNext(A)){
    printf("%d ", *(int*)get(A));
  }
  printf("\n");

  for(moveFront(B); index(B)>=0; moveNext(B)){
    printf("%d ", *(int*)get(B));
  }
  printf("\n");

  printf("Front of A: %d\n", *(int*)front(A));
  printf("Back of A: %d\n", *(int*)back(A));

  for(moveBack(A); index(A)>=0; movePrev(A)){
    printf("%d ", *(int*)get(A));
  }
  printf("\n");

  for(moveBack(B); index(B)>=0; movePrev(B)){
    printf("%d ", *(int*)get(B));
  }
  printf("\n");

  int u = 96;
  int v = 24;
  int w = 1337;

  moveFront(A);
  for(i=0; i<5; i++) moveNext(A);
  printf("index(A)=%d\n", index(A));
  insertBefore(A, &u);
  printf("index(A)=%d\n", index(A));
  for(i=0; i<3; i++) moveNext(A);
  printf("index(A)=%d\n", index(A));
  insertAfter(A, &v);
  printf("index(A)=%d\n", index(A));
  for(i=0; i<5; i++) movePrev(A);
  printf("index(A)=%d\n", index(A));
  delete(A);
  printf("index(A)=%d\n", index(A));
  moveBack(A);
  printf("index(A)=%d\n", index(A));
  for(i=0; i<10; i++) movePrev(A);
  printf("index(A)=%d\n", index(A));
  set(A, &w);

  for(moveFront(A); index(A)>=0; moveNext(A)){
    printf("%d ", *(int*)get(A));
  }
  printf("\n");
 
  printf("B before deleting\n");
  for(moveFront(B); index(B)>=0; moveNext(B)){
    printf("%d ", *(int*)get(B));
  }
  printf("\n");

  moveFront(B);
  printf("length of B: %d\n", length(B));
  deleteFront(B);
  deleteBack(B);

  printf("B after deleting front and back\n");
  for(moveFront(B); index(B)>=0; moveNext(B)){
    printf("%d ", *(int*)get(B));
  }
  printf("\n");
  
  freeList(&A);
  freeList(&B);
  return(0);

}
