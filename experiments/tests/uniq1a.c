#include <pthread.h>
#include <stdio.h>

int *j;
pthread_mutex_t l;

void * malloc(int);

void * dostuff(void * a) {
  int k;
  int *m;
  
  pthread_mutex_lock(&l);
  m = &k; // makes m non-unique
  j = &k; // makes &k shared
  pthread_mutex_unlock(&l);
  *m = 3; // non-unique access to k indirectly through m; race
  return NULL;
}

int main() {
  pthread_t t1;
  pthread_mutex_init(&l, NULL);
  int i = 1;
  pthread_create(&t1, NULL, dostuff, NULL);
  pthread_create(&t1, NULL, dostuff, NULL);
}


