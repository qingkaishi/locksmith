#include <stdio.h>		/* Input/Output */
#include <pthread.h>		/* POSIX Threads */
  pthread_mutex_t L1, L2;
int x, y;

void
munge (pthread_mutex_t * l, int *p)
{
  pthread_mutex_lock (l);
  *p = 3;
  pthread_mutex_unlock (l);
}

void*
f (void *ptr)
{
  munge (&L1, &x);
  munge (&L2, &y);
  return NULL;
}

int
main ()
{
  pthread_t thread1, thread2;

  pthread_mutex_init (&L1, NULL);
  pthread_mutex_init (&L2, NULL);

  pthread_create (&thread1, NULL, f, NULL);
  pthread_create (&thread2, NULL, f, NULL);
}
