#include <pthread.h>

struct pair {
  int data;  //this should be shared, and report a race
  int data2; //this shouldn't be shared nor exist in the .dot file
};

void *f(struct pair *p) {
  p->data++;
  return NULL;
}

int main() {
  pthread_t t1, t2;
  struct pair *p = (struct pair*) malloc(sizeof (struct pair));

  pthread_create(&t1, NULL, f, p);
  pthread_create(&t2, NULL, f, p);
  return 1;
}
