#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

int shared;
pthread_mutex_t lock;

void *run(void* arg) {
  int *s;
  s = &shared;
  //A(&s);
  B(&s);
  printf("Run\n");
  return NULL;
}

void A(int **s)
__attribute__((atomic))
{
  *s = &shared;
}

void B(int** s) 
__attribute__((atomic))
{
  ++(**s);
}

int main(){
  pthread_t t1, t2;

  pthread_mutex_init(&lock, NULL);

  pthread_create(&t1, NULL, run, NULL);
  pthread_create(&t2, NULL, run, NULL);

  pthread_join(t1, NULL);
  pthread_join(t2, NULL);

  return 0;
}

