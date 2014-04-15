#include <pthread.h>
#include <stdio.h>

pthread_t t1;

void * dostuff(void * a) {
  int j;
  int** b = (int**)a;
  (*b) = &j;
}

int main() {
  int i;
  int ** a = (int**) malloc(sizeof(int*));
  (*a) = &i;
  pthread_create(&t1, NULL, dostuff, a);
  pthread_create(&t1, NULL, dostuff, a);
}


