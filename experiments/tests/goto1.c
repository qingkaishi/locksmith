#include <pthread.h>
#include <stdio.h>

int *j;
pthread_mutex_t l;

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
  pthread_create(&t1, NULL, dostuff, NULL);
  //spaghetti starts:
  label1:
  label2:
    goto label3;
  label4:
    j = &i; //unreachable --no race
  label3:
    return 1;
    j = &i; //unreachable --no race
  label5:
    goto label4;
}


