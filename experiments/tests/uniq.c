/* Basic uniqueness test on a local variable; accesses to the variable
   before it becomes shared are legal. */
#include <pthread.h>
#include <stdio.h>

int *j;
pthread_mutex_t l;

void * malloc(int);

void * dostuff(void * a) {
  int *k;
  int **m;
  
  k = (int*) malloc(sizeof (int));
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


