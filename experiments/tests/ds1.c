/* Data structure example 1:  A non-recursive data structure, all of
   whose elements are protected by a single, global lock. */

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

void *run(struct other *a) {
  struct other *a = (struct other *) malloc(sizeof(struct other));
  pthread_mutex_lock(&global_lock);
	a->other_data=1;
  shared.data++;
  shared.other->other_data++;
  shared.other = a;
  a->other_data++;
	if(1) {
		pthread_mutex_unlock(&global_lock); // Gamma(a)
	}
	else {
		pthread_mutex_unlock(&global_lock); // Gamma(a)
	}
  return NULL;
}
int main() {
  pthread_t t1, t2;

  shared.other = (struct other *) malloc(sizeof(struct other));
  pthread_mutex_init(&global_lock, NULL);
  pthread_create(&t1, NULL, run, NULL);
  pthread_create(&t2, NULL, run, NULL);
  return 1;
}
