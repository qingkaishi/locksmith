#include <pthread.h>
#include <stdio.h>

pthread_t t1;

void * dostuff(void * a) {
  int j;
  int** b = (int**)a;
  (**b) = 1; // read on (2), write on (1)
}

int main() {
  int *i = (int *) malloc(sizeof(int));    /* (1) */
  int ** a = (int**) malloc(sizeof(int*)); /* (2) */
  (*a) = i;
  pthread_create(&t1, NULL, dostuff, a);
  **a = 1; // should cause a race on (1), but not (2) (read-only)
}


