#include <pthread.h>

struct SPQ {
   int closed ;
   pthread_mutex_t mtx ;
};
typedef struct SPQ PQUEUE;

PQUEUE gqb  ;

void tolower(char x) { return; }

void *worker(void *arg ) 
{ 
  while (1) {
    pthread_mutex_lock(& gqb.mtx);
    gqb.closed = 1;
    pthread_mutex_unlock(& gqb.mtx);
    tolower('A'); // if we remove this, the race goes away
  }
  return ((void *)0);
}

int main(int argc , char **argv ) 
{ int j ;
  pthread_t tid ;

  tolower('c'); // probably important that this precedes write to .closed

  gqb.closed = 0; // should NOT be a race, but is
  pthread_mutex_init(& gqb.mtx, 0);
  while (1) {
    pthread_create(& tid, 0,& worker, 0);
  }
  pqueue_close(&gqb);
  return 0; 
}

