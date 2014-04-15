#include <pthread.h>

int x;
pthread_mutex_t l;

void bar(void) {
  x = 3;
}

void (*f)(void) = bar;

void *dostuff(void *a) {
  pthread_mutex_lock(&l);
  f();
  pthread_mutex_unlock(&l);
}

int main() {
  pthread_t t1;
  pthread_mutex_init(&l, NULL);
  pthread_create(&t1, NULL, dostuff, NULL);
  pthread_create(&t1, NULL, dostuff, NULL);
}
