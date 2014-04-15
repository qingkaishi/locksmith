#include <pthread.h>

void foo(int* x) {
  *x = 1;
  return;
}

void callfp(void (*fp)(int* x), int* i) {
  fp(i);
}

int i;
void *thread(void *ign) {
  callfp(&foo, &i); 
}

void main() {
  pthread_mutex_t t;
  pthread_create(&t,0,thread,0);
  pthread_create(&t,0,thread,0);
  //callfp(&f, &i);
}
