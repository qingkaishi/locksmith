#include <pthread.h>

void (*fp)(int x);

void foo(int x) {
  return x;
}

void setfp(void) {
  fp = & foo;
}

void *thread(void *ign) {
  int i;
  fp(1); 
  // (2) cont effect will include accesses following (1)
  i++;
}

void main() {
  pthread_mutex_t t;
  int optval;
  int *tmp;
  //setfp();  // doesn't matter if this is called
  tmp = &optval;
  while (1) {
    optval = 1;
    pthread_create(&t,0,thread,0);
    fp(1);
    // (1) cont effect will include accesses following (2)
  }
}
