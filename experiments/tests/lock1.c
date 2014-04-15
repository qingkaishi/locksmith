#include <pthread.h>
#include <stdio.h>

int x;

pthread_mutex_t l;

int f() {
  pthread_mutex_lock(&l);
  x++;
  pthread_mutex_unlock(&l);
}

int main() {
  pthread_t t;
  pthread_mutex_init(&l, NULL);
  pthread_mutex_init(&l, NULL);
  while(1)
  pthread_create(&t, NULL, &f, NULL);
  return 1;
}
