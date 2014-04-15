/* This is a duplicate of uniq.c with a wrapper for malloc(), used
   to test the "unique" attribute. */
#include <pthread.h>
#include <stdio.h>

int *j;
pthread_mutex_t l;

void * malloc(int);

void * __attribute((unique)) wrapper(int x) {
  return malloc(x);
}

void * dostuff(void * a) {
  int *k;
  int **m;
  
  k = (int*) wrapper(sizeof (int));
  *k = 2;
  pthread_mutex_lock(&l);
  j = k;
  *j = 3;
  pthread_mutex_unlock(&l);
  return NULL;
}

int main() {
  pthread_t t1;
  pthread_mutex_init(&l, NULL);
  int i = 1;
  pthread_create(&t1, NULL, dostuff, NULL);
  pthread_create(&t1, NULL, dostuff, NULL);
}


