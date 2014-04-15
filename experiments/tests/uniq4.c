// Tests that deref of a unique variable does not change its uniqueness.
#include <pthread.h>
#include <stdio.h>

int *j;
pthread_mutex_t l;

void * malloc(int);

void * dostuff(void * a) {
  int *k;
  
  k = (int*) malloc(sizeof (int));
  *k = 2;
  j = k; // race on j, not k
  pthread_mutex_lock(&l);
  j = 3;
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


