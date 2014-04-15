#include <pthread.h>
#include <stdio.h>
int **j;

pthread_mutex_t l;
void * dostuff(void * a) {
  int * k;

  pthread_mutex_lock(&l);
  j = &k; // aliasing k
  *j = 0;
  pthread_mutex_unlock(&l);
  k = a; // race on k
  return 0;
}

int main() {
  int i = 1;
	pthread_t t1;
  pthread_mutex_init(&l, NULL);

  pthread_create(&t1, NULL, dostuff, &i);
  pthread_create(&t1, NULL, dostuff, &i);
}


