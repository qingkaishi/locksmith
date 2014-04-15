#include <pthread.h>
#include <stdio.h>

int *j;
struct foo {
  void (*f)(struct foo*);
};

struct foo *foo = 0;

void g(struct foo* foo1) {
  if(foo1) foo1->f(foo1);
}

void a(struct foo *foo1) {
  foo1->f(foo1);
}

void * dostuff(void * ign) {
  int k;
  
  a(foo);
  j = &k; //race
  return NULL;
}

int main() {
  pthread_t t1;
  foo = (struct foo *) malloc(1);
  foo->f = g;

  pthread_create(&t1, NULL, dostuff, NULL);
  j++; //race
}


