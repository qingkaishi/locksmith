/* Data structure example 1:  A non-recursive data structure.
   The first element of pair shared but protected, while
   the second element is not (accessed by three threads).
*/

#include <pthread.h>

struct other {
  int other_data;
};

struct pair {
  int data;
  struct other *other;
};

pthread_mutex_t global_lock;
struct pair shared;

void *run(void *arg) {
  pthread_mutex_lock(&global_lock);
  shared.data++;
  pthread_mutex_unlock(&global_lock);
  shared.other->other_data++;
  return NULL;
}
int main() {
  pthread_t t1, t2;

  shared.other = (struct other *) malloc(sizeof(struct other));
  pthread_mutex_init(&global_lock, NULL);
  pthread_create(&t1, NULL, run, NULL);
  pthread_create(&t2, NULL, run, NULL);
  shared.other->other_data++;
  return 1;
}
