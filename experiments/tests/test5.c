#include <pthread.h>
#include <stdio.h>

struct {
	int data;
} foo;
int shared = 1;
pthread_mutex_t t;

void * dostuff(void * a) {
	pthread_mutex_lock(&t);
	foo.data++;
	shared++;
	pthread_mutex_unlock(&t);
}
int main() {
  int i = 1;
	pthread_t t1;
	pthread_mutex_init(&t,NULL);

	for(i = 0; i<10; i++) {
		pthread_create(&t1, NULL, dostuff, NULL);
	}
}

