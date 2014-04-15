#include <pthread.h>
#include <stdio.h>

void f() {
  int *j;
  *j = 2;
}
void * dostuff(void *ign) {
	f();
  return NULL;
}
int main() {
	pthread_t t1;
  pthread_create(&t1, NULL, dostuff, NULL);
  pthread_create(&t1, NULL, dostuff, NULL);
}


