#include <pthread.h>
#include <stdio.h>

int f(pthread_mutex_t *l) {
  int k, *j;
  
  pthread_mutex_init(l, NULL);
  //pthread_mutex_lock(l);

  j = &k;
	*j = 3;
  if(pthread_mutex_trylock(l)) {
    *j = 5;
		pthread_mutex_unlock(l);
  }
  return 2;
}

void * dostuff(void * a) {
  pthread_mutex_t t;
  printf("foo");
	pthread_mutex_lock(&t);
  *(int *)a = 0;
	pthread_mutex_unlock(&t);
  f(&t);
}
int main() {
  int i = 1; // not shared here
	pthread_t t1;

  pthread_create(&t1, NULL, dostuff, &i);
  pthread_create(&t1, NULL, dostuff, &i);
	if (i) {
		i = 0;
	}
}


