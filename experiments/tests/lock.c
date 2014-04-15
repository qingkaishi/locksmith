#include <pthread.h>
#include <stdio.h>

int f(pthread_mutex_t *l) {
	int x;
  pthread_mutex_init(l, NULL);
  pthread_mutex_init(l, NULL);
}

int main() { return 1; }
