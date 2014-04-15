/* Data structure example 6: A recursive data structure.  All elements
   of the list are protected by one global lock while the edges will
   be protected by another. */
#include <pthread.h>

struct list {
  int data;
  struct list *next;
};

pthread_mutex_t global_lock;
pthread_mutex_t local_lock;

struct list *shared = NULL;

void *run(void *arg) {
  struct list *cur;

  pthread_mutex_lock(&global_lock);
  for (cur = shared; cur; cur = cur->next) {
    int *data = &cur->data;
    struct list *next = cur->next;
    cur->next = next; // fake write
    pthread_mutex_unlock(&global_lock);
    pthread_mutex_lock(&local_lock);
    (*data)++;
    pthread_mutex_unlock(&local_lock);
    pthread_mutex_lock(&global_lock);
  }
  pthread_mutex_unlock(&global_lock);

  return NULL;
}
int main() {
  pthread_t t1, t2;
  int i;

  pthread_mutex_init(&global_lock, NULL);
  pthread_mutex_init(&local_lock, NULL);
  for (i = 0; i < 42; i++) {
    struct list *new = (struct list *) malloc(sizeof(struct list));
    // these accesses should not be counted because the data
    // is not shared yet.  Uniqueness should catch it.
    new->data = 1;
    new->next = shared;
    shared = new;
  }
  pthread_create(&t1, NULL, run, NULL);
  pthread_create(&t2, NULL, run, NULL);
  return 1;
}
