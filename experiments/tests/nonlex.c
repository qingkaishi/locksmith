/* Should have no race conditions.  j and k are both guarded by l. */

#include <pthread.h>

pthread_mutex_t l;
int j;
int k;

void *foo(void *a) {
  int x = (int)a;
  pthread_mutex_lock (&l);
  if (x) {
    j = 1;
    pthread_mutex_unlock (&l);
    return 0;
  }
  // the lock is not released here, because of the return
  k = 1;
  pthread_mutex_unlock (&l);
}

int main() { 
  pthread_t t1, t2;
  pthread_mutex_init (&l, NULL);
  pthread_create(&t1, NULL, foo, (void *)1);
  pthread_create(&t2, NULL, foo, (void *)0);
  return 0;
}
