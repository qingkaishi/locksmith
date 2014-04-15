#include <pthread.h>

int x;

void *f(void *a) {
  int y = x;
  int *p = (int *) malloc(sizeof(int));
  *p = y;
}

int main(void) {
  pthread_t t1;
  x = 42;
  pthread_create(&t1, 0, f, 0);
  pthread_create(&t1, 0, f, 0);
}
