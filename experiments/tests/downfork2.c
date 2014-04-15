#include <pthread.h>

int g; // written once

void *doit(void *z) {
  if (g == 1) return 0;
  return 0;
}
int main() {
  pthread_t t, t2;
  g = 1; // write to a global, but not in continuation
  pthread_create(&t,0,doit,0);
  pthread_create(&t2,0,doit,0);
  return 1;
}

