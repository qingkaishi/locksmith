#include <pthread.h>
#include <stdio.h>

int shared;
pthread_mutex_t global_lock;

void f() {
  shared = 0;
}

void * dostuff(void * a) {
  pthread_mutex_lock(&global_lock);
  shared = 0;
  f();
  pthread_mutex_unlock(&global_lock);
  return 0;
}

int main() {
  int i = 1;
	pthread_t t1;

  pthread_mutex_init(&global_lock,NULL);

  pthread_create(&t1, NULL, dostuff, &i);
  pthread_create(&t1, NULL, dostuff, &i);
}

