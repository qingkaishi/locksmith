#include <pthread.h>
#include <stdio.h>

int *j, foo, bar;

void f() { *j= 0; }

void doit1(void) __attribute__((atomic)) {
  f();
  foo++;
}

void doit2(void) __attribute__((atomic)) {
  *j = 0;
  bar++;
}

void * dostuff(void * a) __attribute__((atomic)) {
  int k;
  
  *j = &k;
  k = 1;
  return NULL;
}

int main() {
  pthread_t t1;
  j = (int*) malloc(sizeof(int));
  while(1){
    pthread_create(&t1, NULL, dostuff, NULL);
    pthread_create(&t1, NULL, doit1, NULL);
    pthread_create(&t1, NULL, doit2, NULL);
  }
}


