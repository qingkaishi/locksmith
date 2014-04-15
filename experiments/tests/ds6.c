/* Data structure example 6: A recursive data structure.  All elements
   of the list are protected by the lock in that element, and the list
   edges are protected by a global lock. Will report a race because
   the local lock will be treated as non-linear. */
#include <pthread.h>

struct list {
  int data;
  pthread_mutex_t lock;
  struct list *next;
};

pthread_mutex_t global_lock;
struct list *shared = NULL;

void *run(void *arg) {
  struct list *cur;

  pthread_mutex_lock(&global_lock);
  for (cur = shared; cur; cur = cur->next) {
    int *data = &cur->data;
    struct list *next = cur->next;
    cur->next = next; // fake write
    pthread_mutex_unlock(&global_lock);
    pthread_mutex_lock(&cur->lock);
    (*data)++;
    pthread_mutex_unlock(&cur->lock);
    pthread_mutex_lock(&global_lock);
  }
  pthread_mutex_unlock(&global_lock);

  return NULL;
}
int main() {
  pthread_t t1, t2;
  int i;

  pthread_mutex_init(&global_lock, NULL);
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
