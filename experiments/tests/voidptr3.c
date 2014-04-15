#include <pthread.h>

struct foo {
  int u;
};

struct bar {
  float v;  /* should be a race on this */
  int m;    /* but no race on this */
};

void *dostuff1(void *x) {
  struct foo *z = (struct foo *) x;
  z->u = 5;
}

void *dostuff2(void *y) {
  struct bar *w = (struct bar *) y;
  w->v = 5;
  w->m = 3;
}

void *dostuff3(void *z) {
  struct bar *t = (struct bar *) z;
  t->v = 6;
}

void *dostuff4(void *s) {
  int *r = (int *) s;
  *r = 3;
}

void *dostuff5(void *q) {
  int *p = (int *) q;
  *p = 4;
}

int main(int argc, char **argv) {
  struct foo a;
  struct bar b;
  int c;
  pthread_t t1;
  pthread_create(&t1, NULL, dostuff1, &a);
  pthread_create(&t1, NULL, dostuff2, &b);
  pthread_create(&t1, NULL, dostuff3, &b);
  pthread_create(&t1, NULL, dostuff4, &c);
  pthread_create(&t1, NULL, dostuff5, &c);
}
