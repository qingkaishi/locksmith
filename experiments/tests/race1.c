// This is subtle.  There is not a race on &k because it is never
// actually deferenced.  There is a race on j because the protecting
// lock is non-linear.  However, we will think there is a race on k
// because we will infer it as shared, given that it is dereferenced
// in dostuff and reachable from j, which is live at the fork.
#include <pthread.h>
#include <stdio.h>

int *j;
pthread_mutex_t l;

void * dostuff(void * a) {
  int k;
  
  pthread_mutex_lock(&l);
  j = &k;
  k = 1;
  pthread_mutex_unlock(&l);
  return NULL;
}

int main() {
  pthread_t t1;
  pthread_mutex_init(&l, NULL);
  pthread_create(&t1, NULL, dostuff, NULL);
  pthread_create(&t1, NULL, dostuff, NULL);
}


