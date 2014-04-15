/* Tests conflation of thread function int* arg to type void*.  Race
   on foo. */
#include <pthread.h>
#include <stdio.h>

void f(int *j) {
  *j = 2;
}
int main() {
  int foo;
  pthread_t t1, t2;
  pthread_create(&t1, NULL, f, &foo);
  pthread_create(&t2, NULL, f, &foo);
}
