#include <pthread.h>

struct s {
  int i;
};

struct s* v2i(void *v) {
  return (struct s *) v;
}

void *dostuff(void *v) {
  struct s *s1;
  s1 = v2i(v);
  s1->i = 3;
  return 0;
}

int main(int argc, char **argv) {
  struct s a;
  struct s *b;
  pthread_t t1;
  pthread_create(&t1, NULL, dostuff, &a);
  dostuff(&a);
  b = v2i(&a);
}
