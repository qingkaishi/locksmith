/* Data structure example 2: A non-recursive pair data structure.  The
   data in the pair is protected by the lock in the pair. */

#include <pthread.h>

struct pair {
  pthread_mutex_t lock;
  int data;
};

struct pair shared;

void *run(void *arg) {
  pthread_mutex_lock(&shared.lock);
  shared.data++;
  pthread_mutex_unlock(&shared.lock);
  return NULL;
}
int main() {
  pthread_t t1, t2;

  pthread_mutex_init(&shared.lock, NULL);
  pthread_create(&t1, NULL, run, NULL);
  pthread_create(&t2, NULL, run, NULL);
  run(0);
  return 1;
}
