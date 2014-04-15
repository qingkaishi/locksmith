// no fields are used. the graph shouldn't have alloc nodes for fields.

#include <pthread.h>

struct pair {
  int data;
  int data2;
};

int main() {
  pthread_t t1, t2;

  struct pair *p = (struct pair *) malloc(sizeof(struct pair));
  return 1;
}
