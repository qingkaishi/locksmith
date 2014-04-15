#include <pthread.h>
#include <stdio.h>

void * dostuff(void *ign) {
  int *j;
  *j = 2;
  return NULL;
}
int main() {
	pthread_t t1;
  pthread_create(&t1, NULL, dostuff, NULL);
  pthread_create(&t1, NULL, dostuff, NULL);
}


