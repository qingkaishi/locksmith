#include <pthread.h>
#include <stdio.h>

void f() {
  int *j;
  *j = 2;
}
void * dostuff(void *ign) {
	char *s;
	f();
  s = (char*) malloc(3);
	s[1] = 3;
	return NULL;
}
int main() {
	pthread_t t1;
  pthread_create(&t1, NULL, dostuff, NULL);
  pthread_create(&t1, NULL, dostuff, NULL);
}


