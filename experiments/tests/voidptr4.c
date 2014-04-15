#include <pthread.h>

void *g; /* models a conflated container */
pthread_mutex_t l;

struct foo {
  int u;    /* no race */
};

struct bar {
  float v;  /* should be a race on this */
  int m;    /* but no race on this */
};

void *dostuff1(void *x) {
  struct foo *z;

  pthread_mutex_lock(&l);
  g = x;
  z = (struct foo *) g;
  pthread_mutex_unlock(&l);
  z->u = 5;
}

void *dostuff2(void *y) {
  struct bar *w;

  pthread_mutex_lock(&l);
  g = y;
  w = (struct bar *) g;
  pthread_mutex_unlock(&l);
  w->v = 5;
}

void *dostuff3(void *z) {
  struct bar *t;
  pthread_mutex_lock(&l);
  g = z;
  t = (struct bar *) g;
  pthread_mutex_unlock(&l);
  t->v = 6;
}

int main(int argc, char **argv) {
  struct foo a;
  struct bar b;
  pthread_t t1;
  pthread_mutex_init(&l, NULL);
  pthread_create(&t1, NULL, dostuff1, &a);
  pthread_create(&t1, NULL, dostuff2, &b);
  pthread_create(&t1, NULL, dostuff3, &b);
}
