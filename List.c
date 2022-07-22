/********************************************************************************* 
 * * Kevin Kang, ktkang 
 * * 2022 Spring CSE101 PA4
 * * List.c 
 * * Implementation file for List ADT 
 * *********************************************************************************/


// implementation of list ADT

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "List.h"

typedef struct NodeObj* Node;

typedef struct NodeObj {
  void* data;
  Node prev;
  Node next;
} NodeObj;

// structs
typedef struct ListObj {
  Node front;
  Node back;
  Node cursor;
  int idx;
  int length;
} ListObj;

// constructors-destructors

// Creates and returns a new empty List.
List newList() {
  List L;
  L = malloc(sizeof(ListObj));
  L->front = L->back = L->cursor = NULL;
  L->idx = -1;
  L->length = 0;
  return L;
}

// Creates and returns a new Node for the List ADT.
Node newNode(void* data) {
  Node N = malloc(sizeof(NodeObj));
  N->data = data;
  N->next = N->prev = NULL;
  return N;
}

// Frees all heap memory associated with *pN, and sets *pN to NULL.
void freeNode(Node *pN) {
  if (pN != NULL && *pN != NULL) {
    free(*pN);
    *pN = NULL;
  }
}

// Frees all heap memory associated with *pL, and sets *pL to NULL.
void freeList(List *pL) {
  if (pL != NULL && *pL != NULL) {
    while (length(*pL) != 0) {
      deleteFront(*pL);
    }
    free(*pL);
    *pL = NULL;
  }
}

// Returns the number of elements in L.
int length(List L) {
  if (L == NULL) {
    printf("List Error: calling length() on NULL List reference\n");
    exit(EXIT_FAILURE);
  }
  return L->length;
}

// Returns index of cursor element if defined, -1 otherwise.
int index(List L) {
  return L->idx;
}

// Returns front element of L. Pre: length()>0
void* front(List L) {
  if (L == NULL) {
    printf("List Error: calling front() on NULL List reference\n");
    exit(EXIT_FAILURE);
  }
  if (length(L) == 0) {
    printf("List Error: calling front() on an empty List\n");
    exit(EXIT_FAILURE);
  }
  return L->front->data;
}

// Returns back element of L. Pre: length()>0
void* back(List L) {
  if (L == NULL) {
    printf("List error: calling back() on NULL List reference\n");
    exit(EXIT_FAILURE);
  }
  if (length(L) == 0) {
    printf("List Error: calling back() on an empty List\n");
    exit(EXIT_FAILURE);
  }
  return L->back->data;
}

// Returns cursor element of L. Pre: length()>0, index()>=0
void* get(List L) {
  if (length(L) == 0) {
    printf("List error: calling get() on an empty List\n");
    exit(EXIT_FAILURE);
  }
  if (index(L) == -1) {
    printf("List error: calling get() on List with no cursor defined\n");
    exit(EXIT_FAILURE);
  }
  return L->cursor->data;
}

// manipulation procedures

// Resets L to its original empty state.
void clear(List L) {
  if (L != NULL) {
    while (length(L) != 0) {
      deleteFront(L);
    }
  }
  L->idx = -1;
  L->cursor = NULL;
}

// Overwrites the cursor element’s data with x. Pre: length()>0, index()>=0
void set(List L, void* x) {
  if (length(L) == 0) {
    printf("List error: calling set() on an empty List\n");
    exit(EXIT_FAILURE);
  }
  if (index(L) == -1) {
    printf("List error: calling set() on List with no cursor defined\n");
    exit(EXIT_FAILURE);
  }
  L->cursor->data = x;
}

// If L is non-empty, sets cursor under the front element, otherwise does nothing.
void moveFront(List L) {
  if (length(L) != 0) {
    L->cursor = L->front;
    L->idx = 0;
  }
}

// If L is non-empty, sets cursor under the back element, otherwise does nothing.
void moveBack(List L) {
  if (length(L) != 0) {
    L->cursor = L->back;
    L->idx = L->length - 1;
  }
}

// If cursor is defined and not at front, move cursor one
// step toward the front of L; if cursor is defined and at
// front, cursor becomes undefined; if cursor is undefined
// do nothing
void movePrev(List L) {
  if (L->cursor != NULL && index(L) != 0) {
    L->idx -= 1;
    L->cursor = L->cursor->prev;
  } else if (L->cursor != NULL && index(L) == 0) {
    L->idx = -1;
    L->cursor = NULL;
  } 
}

// If cursor is defined and not at back, move cursor one
// step toward the back of L; if cursor is defined and at
// back, cursor becomes undefined; if cursor is undefined
// do nothing
void moveNext(List L) {
  if (L->cursor != NULL && index(L) != length(L)-1 /*L->cursor->data != back(L)*/) {
    L->idx += 1;
    L->cursor = L->cursor->next;
  } else if (L->cursor != NULL && index(L) == length(L)-1) {
    L->idx = -1;
    L->cursor = NULL;
  }
}

// Insert new element into L. If L is non-empty,
// insertion takes place before front element.
void prepend(List L, void* x) {
  Node N = newNode(x);

  if (L == NULL) {
    printf("List Error: calling prepend() on NULL List reference\n");
    freeNode(&N);
    exit(EXIT_FAILURE);
  }
  if (L->idx > -1) {
    L->idx++;
  }
  if (length(L) == 0) {
    L->front = L->back = N;
  } else {
    N->next = L->front;
    N->prev = NULL;
    L->front->prev = N;
    L->front = N;
  }
  L->length++;
}

// Insert new element into L. If L is non-empty,
// insertion takes place after back element.
void append(List L, void* x) {
  Node N = newNode(x);

  if (L == NULL) {
    printf("List Error: calling append() on NULL List reference\n");
    freeNode(&N);
    exit(EXIT_FAILURE);
  } 
  if (length(L) == 0) {
    L->front = L->back = N;
  } else {
    N->next = NULL;
    N->prev = L->back;
    L->back->next = N;
    L->back = N;
  }
  L->length++;
}

// Insert new element before cursor.
// Pre: length()>0, index()>=0
void insertBefore(List L, void* x) {
  if (length(L) == 0) {
    printf("List error: calling insertBefore() on an empty List\n");
    exit(EXIT_FAILURE);
  }
  if (index(L) == -1) {
    printf("List error: calling insertBefore() on List with no cursor defined\n");
    exit(EXIT_FAILURE);
  }
  
  if (L->cursor->prev == NULL) {
    prepend(L, x);
  } else {

  Node N = newNode(x);

  N->next = L->cursor;
  N->prev = L->cursor->prev;
  L->cursor->prev->next = N;
  L->cursor->prev = N;
  L->length++;
  L->idx++;
  }
}

// Insert new element after cursor. Pre: length()>0, index()>=0
void insertAfter(List L, void* x) {
  if (length(L) == 0) {
    printf("List error: calling insertAfter() on an empty List\n");
    exit(EXIT_FAILURE);
  }
  if (index(L) == -1) {
    printf("List error: calling insertAfter() on List with no cursor defined\n");
    exit(EXIT_FAILURE);
  }
  
  if (L->cursor->next == NULL) {
    append(L, x);
  } else {

  Node N = newNode(x);

  N->next = L->cursor->next;
  N->prev = L->cursor;
  L->cursor->next = N;
  N->next->prev = N;
  
  //L->cursor->next->prev = N;
  //L->cursor->next = N;
  L->length++;
  }
}

// Delete the front element. Pre: length()>0
void deleteFront(List L) {
  Node N = NULL;

  if (L == NULL) {
    printf("List Error: calling deleteFront() on NULL List reference\n");
    exit(EXIT_FAILURE);
  }
  if (length(L) == 0) {
    printf("List Error: calling deleteFront() on an empty List\n");
    exit(EXIT_FAILURE);
  }

  N = L->front;
  if (length(L) > 1) {
    L->front = L->front->next;
    if (L->front->prev == L->cursor) {
      L->cursor = NULL;
    }
    L->front->prev = NULL;
    L->idx--;
  } else {
    L->front = L->back = L->cursor = NULL;
    L->idx = -1;
  }
  L->length--;
  freeNode(&N);
  N = NULL;
}

// Delete the back element. Pre: length()>0
void deleteBack(List L) {
  Node N = NULL;

  if (L == NULL) {
    printf("List Error: calling deleteBack() on NULL List reference\n");
    exit(EXIT_FAILURE);
  }
  if (length(L) == 0) {
    printf("List Error: calling deleteBack() on an empty List\n");
    exit(EXIT_FAILURE);
  }

  N = L->back;
  if (length(L) > 1) {
    if (L->back == L->cursor) {
      L->cursor = NULL;
      L->idx = -1;
    }
    L->back = L->back->prev;
    L->back->next = NULL;
  } else {
    L->front = L->back = L->cursor = NULL;
    L->idx = -1;
  }
  L->length--;
  freeNode(&N);
  N = NULL;
}

// Delete cursor element, making cursor undefined. Pre: length()>0, index()>=0
void delete(List L) {
  if (length(L) == 0) {
    printf("List error: calling delete() on an empty List\n");
    exit(EXIT_FAILURE);
  }
  if (index(L) == -1) {
    printf("List error: calling delete() on List with no cursor defined\n");
    exit(EXIT_FAILURE);
  }

  if (L->front == L->cursor && length(L) != 1) {
    L->front = L->cursor->next;
    L->front->prev = NULL;
  }
  if (L->cursor->next != NULL) {
    L->cursor->next->prev = L->cursor->prev;
  }
  if (L->cursor->prev != NULL) {
    if (L->cursor->next == NULL) {
      L->back = L->cursor->prev;
    }
    L->cursor->prev->next = L->cursor->next;
  }
  L->idx = -1;
  L->length--;
  freeNode(&L->cursor);
  L->cursor = NULL;
}

