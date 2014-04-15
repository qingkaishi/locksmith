#include <stdlib.h>
#include <pthread.h>

// the lock label
#pragma existential(t,"t.lock","&t.data")
// the address of the field
#pragma existential(t,"t.data")

struct t {
  pthread_mutex_t lock;
  int* data;
};

struct t a;

void* f(struct t* in) {
  start_unpack(in);
  pthread_mutex_lock(&(in->lock));
  in->data++;
  pthread_mutex_unlock(&(in->lock));
  end_unpack(in);
  return 0;
}
int main() {
  struct t __attribute__((packed)) *s;
  struct t *p;
  pthread_t t1, t2;

  while(1) {
    s = (struct t __attribute((packed)) *) malloc(sizeof (struct t));
    pthread_mutex_init(&s->lock, NULL);
    p = pack(s);
  }

  pthread_create(&t1, NULL, f, p);
  pthread_create(&t2, NULL, f, p);
  return 1;
}
