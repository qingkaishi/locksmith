#include <pthread.h>
#include <stdio.h>

void * dostuff(void * a) {
  *(int *)a = 0;
}

int main() {
  pthread_t t1;
  while(1) {
    int * mem = malloc(sizeof(int));
    *mem = 1;
    pthread_create(&t1, NULL, dostuff, mem);
    *mem = 1;
  }
}


