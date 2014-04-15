#include <pthread.h>
#include <stdio.h>

int j; // local to t1
int m;
pthread_mutex_t l;

void * dostuff(void * a) {
  int *k = (int *)a;
  j = *k; // dereferences &i = &m, passed in by parent; race!
  return NULL;
}

void * dostuff2(void * a) {
  int *k2 = (int *)a; 
  m = *k2; // dereferences &i from parent, but parent never accesses
	   // it again, so it's not a race
  return NULL;
}

int main() {
  pthread_t t1;
  pthread_mutex_init(&l, NULL);
  void* (*aa)(void*);
  aa = dostuff;
  int i = 1;
  pthread_create(&t1, NULL, aa, &m);
  pthread_create(&t1, NULL, &dostuff2, &i);
}


