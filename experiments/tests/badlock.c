/* Should cause a non-linearity warning, since lock will be
   initialized twice. */
#include <pthread.h>

pthread_mutex_t lock;
int shared;

void *run(void *arg) {
  pthread_mutex_lock(&lock);
  shared++;
  pthread_mutex_unlock(&lock);
  return NULL;
}
void doit(int *j) {
  pthread_t t1;
  pthread_mutex_init(&lock, NULL);
  pthread_create(&t1, NULL, run, j);
}

int main() {
  int i = 0;
  doit(&i);
  doit(&i);
  return 1;
}
