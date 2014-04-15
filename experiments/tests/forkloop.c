#include <pthread.h>
#include <stdio.h>

void * dostuff(void * a) {
  *(int *)a = 0;
}

int main() {
  pthread_t t1;
  int i = 1; // not shared yet
  while(1) {
    pthread_create(&t1, NULL, dostuff, &i);
  }
}


