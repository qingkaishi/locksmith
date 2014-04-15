#include <pthread.h>
#include <stdio.h>

int *j;
pthread_mutex_t l;

int f() {
  *j = 3;
}

int (*ptr)(void);

void * dostuff(void * a) {
  int k;
  
  pthread_mutex_lock(&l);
  j = &k;
  pthread_mutex_unlock(&l);
  return NULL;
}

int main() {
  pthread_t t1;
  pthread_mutex_init(&l, NULL);
  int i = 1;

  ptr = f;
  pthread_create(&t1, NULL, dostuff, NULL);
//  pthread_create(&t1, NULL, dostuff, NULL);
  switch(i) {
    case 1:
      break;
    default:
      i = 2;
      ptr(); //a race
      break;
      j=&i; //this should not be in the guard set
  }
}


