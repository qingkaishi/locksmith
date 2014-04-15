#include <pthread.h>
#include <stdio.h>

int *j;

pthread_mutex_t* rec() {
  int i;
  pthread_mutex_t *t;
  if(i) {
    return rec();
  } else {
    pthread_mutex_init(t,0);
    return t;
  }
}

pthread_mutex_t *l;// = rec();
void * dostuff(void * a) {
  int k;
  
  pthread_mutex_lock(l);
  j = &k;
  pthread_mutex_unlock(l);
  return NULL;
}

int main() {
  pthread_t t1;
  int i = 1;
  l = rec();
  while (1)
  pthread_create(&t1, NULL, dostuff, NULL);
  //pthread_create(&t1, NULL, dostuff, NULL);
}


