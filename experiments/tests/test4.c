#include <pthread.h>
#include <stdio.h>

int f(pthread_mutex_t *l) {
  int k, *j;
  
  pthread_mutex_init(l, NULL);
  pthread_mutex_lock(l);

  j = &k;
  if(pthread_mutex_trylock(l)) {
    *j = 5;
  }
  else {
    j = (int *) &l;
  }
  pthread_mutex_unlock(l);
  return 2;
}

void *dostuff(void*);

int main() {
  int i = 1;
	pthread_t t1;

	for(i = 0; i<10; i++) { // init i=0 not shared
		pthread_create(&t1, NULL, dostuff, &i);
	}
}

void *dostuff(void*);

void * dostuff(void * a) {
	int *i = (int*) a;
  pthread_mutex_t t;
  printf("foo");
  *i = 0;
  f(&t);
}
