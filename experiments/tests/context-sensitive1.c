/* Takes the address of a local variable in two different threads.
   Should not report a race, due to use of (Down) at pthread_create. */
#include <pthread.h>

void *g(int *i) {
  (*i) = 2;
  return NULL;
}

void * thread(void *ign) {
  int j;
  g(&j);
}

int main() {
  pthread_t t1, t2;

  pthread_create(&t1, NULL, thread, NULL);
  pthread_create(&t2, NULL, thread, NULL);
  return 1;
}
