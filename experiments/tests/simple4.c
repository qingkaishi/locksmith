/* Initializes a lock in a function called from main().  Race on 
   non_protected. */
#include <pthread.h>

pthread_mutex_t lock;
int shared;
int non_protected;

void *run(void *arg) {
  pthread_mutex_lock(&lock);
  shared++;
	pthread_mutex_unlock(&lock);
	non_protected++;
//	*(int*) arg = 1;
  return NULL;
}
void doit(int *j) {
  pthread_t t1, t2;
  pthread_mutex_init(&lock, NULL);
  pthread_create(&t1, NULL, run, j);
  pthread_create(&t1, NULL, run, j);
}

int main() {
	int i = 0;
	doit(&i);
  return 1;
}
