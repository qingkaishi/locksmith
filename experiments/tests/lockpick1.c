#include <pthread.h>
#include <stdio.h>

int *j;

void * dostuff(void * a) __attribute__((atomic)) {
  int k;
  
  j = &k;
  k = 1;
  return NULL;
}

int main() {
  pthread_t t1;
  pthread_create(&t1, NULL, dostuff, NULL);
  pthread_create(&t1, NULL, dostuff, NULL);
}


