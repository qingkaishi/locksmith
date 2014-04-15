#include <pthread.h>
#include <stdio.h>
int shared;
pthread_mutex_t t;

void * dostuff(void * a) {
	pthread_mutex_lock(&t);
	pthread_mutex_unlock(&t);
	shared++;
}
void f() {
	pthread_t t1;
	pthread_create(&t1, NULL, dostuff, NULL);
}

int main() {
  int i = 1;
	pthread_mutex_init(&t,NULL);
	f();
	f();
}

