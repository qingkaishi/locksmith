#include <pthread.h>
#include <stdio.h>

char *g;
pthread_mutex_t l;

void * dostuff(void *a) {
  char *s = malloc(3);
  char *s2;
  s[1] = 3; // unique
  pthread_mutex_lock(&l);
  g = s;    // makes s global, but prior access unique; no race
  *g = 1;
  pthread_mutex_unlock(&l);
  return NULL;
}
int main() {
  pthread_t t1;
  pthread_t t2;
  pthread_mutex_init(&l,NULL);
  pthread_create(&t1, NULL, dostuff, NULL);
  pthread_create(&t2, NULL, dostuff, NULL);
}


