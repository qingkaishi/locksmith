#include <pthread.h>
#include <stdio.h>

int f() {return 0;}

struct foo {
  void (*bar)(struct foo* a);
};

struct foo a;

void b(struct foo *a) {
  a->bar = b;
  a->bar(a);
}

pthread_mutex_t l;

int i;

void * dostuff(void * z) {
  pthread_mutex_lock(&l);
  a.bar = b;
  a.bar(NULL);
  pthread_mutex_unlock(&l);
  return NULL;
}

int main() {
  pthread_t t1;
  int i = 1;
  pthread_mutex_init(&l,NULL);
  pthread_create(&t1, NULL, dostuff, NULL);
  pthread_create(&t1, NULL, dostuff, NULL);
}


