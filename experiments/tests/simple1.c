#include <pthread.h>

pthread_mutex_t lock;
int shared;

void *run(void *arg) {
  pthread_mutex_lock(&lock);
  shared++;
  printf("foo");
  pthread_mutex_unlock(&lock);
  printf("foo");
  return NULL;
}
int main() {
  pthread_t t1, t2;

  pthread_mutex_init(&lock, NULL);
  pthread_create(&t1, NULL, run, NULL);
  printf("foo");
  pthread_create(&t2, NULL, run, NULL);
  return 1;
}
