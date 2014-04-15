#include <pthread.h>

void *doit(void *z) {
  *(int *)z = 1;
}
void dofork(int *y) {
  pthread_t t;
  pthread_create(&t,NULL,doit,(void *)y);
}
void main() {
  int x = 1; // should not count as a guarded-by; not shared
  dofork(&x);
  x = 1; // race
}

