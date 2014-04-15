#include <stdlib.h>
#include <pthread.h>

// the lock label
#pragma existential(t,"t.lock","&t.data")
// the address of the field
#pragma existential(t,"t.data")

typedef struct t {
  pthread_mutex_t lock;
  int* data;
} t;

t a;

void* f(t* in) {
  start_unpack(in);
  pthread_mutex_lock(&(in->lock));
  in->data++;
  pthread_mutex_unlock(&(in->lock));
  end_unpack(in);
  return 0;
}
int main() {
  t __attribute__((packed)) *s1;
  t __attribute__((packed)) *s2;
  t *p;
  pthread_t t1, t2;

  s1 = (t __attribute((packed)) *) malloc(sizeof (struct t));
  pthread_mutex_init(&s1->lock, NULL);
  p = pack(s1);
  if(rnd()) {
    s2 = (t __attribute((packed)) *) malloc(sizeof (struct t));
    pthread_mutex_init(&s2->lock, NULL);
    p = pack(s2);
  }

  pthread_create(&t1, NULL, f, p);
  pthread_create(&t2, NULL, f, p);
  return 1;
}
