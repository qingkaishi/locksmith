#include <pthread.h>
#include <stdio.h>

int *j;
pthread_mutex_t l;

void * dostuff(void * a) {
  int k;
  
  pthread_mutex_lock(&l);
  j = &k;
  pthread_mutex_unlock(&l);
  return NULL;
}

int main() {
  pthread_t t1;
  pthread_mutex_init(&l, NULL);
  void* (*aa)(void*);
  aa = &dostuff;
  int i = 1;
  pthread_create(&t1, NULL, aa, NULL);
  pthread_create(&t1, NULL, &dostuff, NULL);
}


