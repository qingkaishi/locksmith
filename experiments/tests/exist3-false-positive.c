#include <stdlib.h>
#include <pthread.h>

// the lock label
#pragma existential(t,"&t.data")

pthread_mutex_t g;

struct t {

  int data;  // guarded by lock
  int gdata; // guarded by g
};

struct t a;

void doit(struct t* in) {
  start_unpack(in);
  //pthread_mutex_lock(&(in->lock));
  //in->data++;
  //pthread_mutex_unlock(&(in->lock));
  in->gdata++;
  end_unpack(in);
}

void* f(struct t* in) {
  pthread_mutex_lock(&g);
  doit(in);
  pthread_mutex_unlock(&g);
  return 0;
}

int main() {
  struct t __attribute__((packed)) *s;
  struct t *p;
  pthread_t t1, t2;

  pthread_mutex_init(&g, NULL);
  while(p) {
    s = (struct t __attribute((packed)) *) malloc(sizeof (struct t));
    //pthread_mutex_init(&s->lock, NULL);
    p = pack(s);
  }

  pthread_create(&t1, NULL, f, p);
  pthread_create(&t2, NULL, f, p);
  return 1;
}
