/* No races; values are shared flow-sensitively */
#include <pthread.h>

int g;
pthread_mutex_t l;

void *child1(void *data) {
  int *i = (int *)data;
  pthread_mutex_lock(&l);
  g++; // shared access to g
  *i = 1; // shared access to i
  pthread_mutex_unlock(&l);
}

void *child2(void *ign) {
  int i;
  pthread_t t1, t2;
  i = 1; // not shared yet
  pthread_create(&t1,0,child1,&i); // sharing i
  i++; // RACE!
  pthread_create(&t2,0,child1,&i);
  pthread_mutex_lock(&l);
  g++; // shared access to g
  i++; // shared access to i
  pthread_mutex_unlock(&l);
}

int main() {
  pthread_t t1, t2;
  g = 1; // not shared at this location
  pthread_mutex_init(&l,0);
  pthread_create(&t1,0,child2,0);
  pthread_create(&t2,0,child2,0);
}
