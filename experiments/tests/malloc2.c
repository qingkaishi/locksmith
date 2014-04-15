#include <pthread.h>
#include <stdio.h>

pthread_t t1;

void * dostuff(void * a) {
  int j;
  int** b = (int**)a;
  (**b) = 1; // read on (2), write on (1)
  (*b) = NULL; // write on (2)
}

int id(int **a) { return **a;  } // read on (1),(2)

int main() {
  int *i = (int *) malloc(sizeof(int));    /* (1) */
  int ** a = (int**) malloc(sizeof(int*)); /* (2) */
  (*a) = i; // no read on (2); unique
  pthread_create(&t1, NULL, dostuff, a);
  id(a);
}


