#include <pthread.h>

void *dostuff(void *x) {
  int *z = (int *) x;
  *z = 3;
}

int main(int argc, char **argv) {
  int a, b;
  pthread_t t1;
  pthread_create(&t1, NULL, dostuff, &a);
  pthread_create(&t1, NULL, dostuff, &b);
}
