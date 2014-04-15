#include <pthread.h>

static pthread_mutex_t _hashmutex  ;
static int _hashreads  =    0;

// this function is called sometimes when
// the lock is acquired, and sometimes when
// it's released.
int sem_wait() { return 1; }

void trc_trace() 
{
  pthread_mutex_lock(& _hashmutex);
  sem_wait();
  _hashreads ++;
  pthread_mutex_unlock(& _hashmutex);
}

void *thread2(void *arg ) 
{
  sem_wait();
  trc_trace();
}

int main(int argc , char **argv ) 
{
  pthread_t tid2 ;
  pthread_mutex_init(&_hashmutex);

  pthread_create(& tid2, 0, & thread2, 0);
  pthread_create(& tid2, 0, & thread2, 0);
}
