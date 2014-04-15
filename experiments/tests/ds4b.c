/* Data structure example 4:  A recursive data structure.  
   The list elements themselves are protected, but what
   they point to is not. */

#include <pthread.h>

struct list {
  int data;
  struct list *next;
};

pthread_mutex_t global_lock;
struct list *shared = NULL;

void *run(void *arg) {
  struct list *cur;

  pthread_mutex_lock(&global_lock);
  for (cur = shared; cur; cur = cur->next) {
    int *data = &cur->data;
    pthread_mutex_unlock(&global_lock);
    (*data)++; // Race!
    pthread_mutex_lock(&global_lock);
  }
  pthread_mutex_unlock(&global_lock);

  return NULL;
}
int main() {
  pthread_t t1, t2;
  int i;

  for (i = 0; i < 42; i++) {
    struct list *new = (struct list *) malloc(sizeof(struct list));
    new->next = shared;
    shared = new;
  }
  pthread_mutex_init(&global_lock, NULL);
  pthread_create(&t1, NULL, run, NULL);
  pthread_create(&t2, NULL, run, NULL);
  return 1;
}
