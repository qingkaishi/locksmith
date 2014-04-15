// no fields are used. the graph shouldn't have alloc nodes for fields.

#include <pthread.h>

void *g(int *i) {
  (*i) = 2;
  return NULL;
}

void * thread(void *ign) {
  int i;
  g(&i);
}

int main() {
  pthread_t t1, t2;

  pthread_create(&t1, NULL, thread, NULL);
  pthread_create(&t2, NULL, thread, NULL);
  return 1;
}
