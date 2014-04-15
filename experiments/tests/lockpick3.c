#include <pthread.h>
#include <stdio.h>

int a, b, c;

void doit1(void) __attribute__((atomic)) {
  a++;
  b++;
}

void doit2(void) __attribute__((atomic)) {
  b++;
  c++;
}

void doit3(void) __attribute__((atomic)) {
  c++;
  a++;
}

int main() {
  pthread_t t1;
  while(1){
    pthread_create(&t1, NULL, doit1, NULL);
    pthread_create(&t1, NULL, doit2, NULL);
    pthread_create(&t1, NULL, doit3, NULL);
  }
}


