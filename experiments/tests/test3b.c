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

void * dostuff(void * a) {
  pthread_mutex_t t;
  printf("foo");
  *(int *)a = 0;
  f(&t);
}
int main() {
  int i = 1; // not shared here
	pthread_t t1;

  pthread_create(&t1, NULL, dostuff, &i);
	i++;
}


