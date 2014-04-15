#include <pthread.h>
#include <stdio.h>

int *j;

void * dostuff(void * a) {
  int k;
  pthread_mutex_t l;
  
  pthread_mutex_init(&l, NULL);
  pthread_mutex_lock(&l);
  j = &k;
  pthread_mutex_unlock(&l);
  return NULL;
}

int main() {
  pthread_t t1;
  int i = 1;
  pthread_create(&t1, NULL, dostuff, NULL);
  pthread_create(&t1, NULL, dostuff, NULL);
}


