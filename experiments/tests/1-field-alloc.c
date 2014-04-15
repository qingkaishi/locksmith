#include <pthread.h>

struct pair {
  int data;
  int data2;
};

int main() {
  pthread_t t1, t2;

  struct pair *p = (struct pair *) malloc(sizeof(struct pair));
  p->data = 1;
  return 1;
}
