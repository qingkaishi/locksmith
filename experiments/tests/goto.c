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
    if (i) goto label5;
    if (!i) goto label6;
  label2:
    goto label3;
  label4:
  label3:
    return 1;
  label5:
    goto label4;
  label6:
  j = &i;  //  race
  goto label5;
}


