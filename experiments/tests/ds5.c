/* Data structure example 5:  A recursive data structure.  All
   elements of the list are protected by the lock in that element.
   Will report a race since the lock will be non-linear. */
#include <pthread.h>

struct list {
  int data;
  pthread_mutex_t lock;
  struct list *next;
};

struct list *shared = NULL;

void *run(void *arg) {
  struct list *cur;

  for (cur = shared; cur; cur = cur->next) {
    pthread_mutex_lock(&cur->lock);
    cur->data++;
    pthread_mutex_unlock(&cur->lock);
  }

	cur = cur->next;
  return NULL;
}
int main() {
  pthread_t t1, t2;
  int i;

  for (i = 0; i < 42; i++) {
    struct list *new;
	  new = (struct list *) malloc(sizeof(struct list));
    new->next = shared;
    pthread_mutex_init(&new->lock, NULL);
    shared = new;
  }
  for (i = 0; i < 42; i++) {
    struct list *new = (struct list *) malloc(sizeof(struct list));
    new->next = shared;
    pthread_mutex_init(&new->lock, NULL);
    shared = new;
  }
  pthread_create(&t1, NULL, run, NULL);
  pthread_create(&t2, NULL, run, NULL);
  return 1;
}
