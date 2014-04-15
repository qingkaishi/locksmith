/* Data race on a local variable from main().  Notice that j, a global
   variable, is accessed in a thread-local manner, and so is not cause
   for a race. */
  
#include <pthread.h>
#include <stdio.h>

int j;
void f(void) {
  j = 3;
  return;
}

void * dostuff(void * a) {
  *(int *)a = 0;
  f();
}

int main() {
  pthread_t t1;
  int i = 1; // doesn't count as guarded-by; not shared
  f();
  pthread_create(&t1, NULL, dostuff, &i);
  i = 0;
}


