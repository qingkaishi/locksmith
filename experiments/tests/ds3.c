/* Data structure example 3:  A non-recursive triple data structure.
   One element in the structure is protected by the lock in the
   structure, the other element is protected by a global lock. */

#include <pthread.h>

struct pair {
  pthread_mutex_t lock;
  int data;
  int other_data;
};

pthread_mutex_t global_lock;
struct pair shared;

void *run(void *arg) {
  pthread_mutex_lock(&shared.lock);
  shared.data++;
  pthread_mutex_unlock(&shared.lock);

  pthread_mutex_lock(&global_lock);
  shared.other_data++;
  pthread_mutex_unlock(&global_lock);

  return NULL;
}
int main() {
  pthread_t t1, t2;

  pthread_mutex_init(&global_lock, NULL);
  pthread_mutex_init(&shared.lock, NULL);
  pthread_create(&t1, NULL, run, NULL);
  pthread_create(&t2, NULL, run, NULL);
  return 1;
}
