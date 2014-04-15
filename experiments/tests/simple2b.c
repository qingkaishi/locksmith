#include <pthread.h>

pthread_mutex_t lock;

void *run(void*);
int main() {
  pthread_t t1, t2;
  pthread_mutex_init(&lock, NULL);
  pthread_create(&t1, NULL, run, NULL);
  pthread_create(&t1, NULL, run, NULL);
  return 1;
}
int shared;
int non_protected;
void *run(void *arg) {
	non_protected++;
  pthread_mutex_lock(&lock);
  shared++;
	pthread_mutex_unlock(&lock);
  return NULL;
}
