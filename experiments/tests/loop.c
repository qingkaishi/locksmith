#include <pthread.h>
#include <stdio.h>

int *j;

pthread_mutex_t l;

void * dostuff(void * a) {
  pthread_mutex_lock(&l);
  j = 0;
  pthread_mutex_unlock(&l);
  return NULL;
}

int main() {
  pthread_t t1, t2;

  int i = 1;
  while(1) {
    pthread_mutex_init(&l, NULL);  // makes lock non-linear
  }
  pthread_create(&t1, NULL, dostuff, NULL);
  pthread_create(&t2, NULL, dostuff, NULL);
  return 1;
}

