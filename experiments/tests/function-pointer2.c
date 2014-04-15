#include <pthread.h>
struct foo {
   void (*f)(void) ;
};

void f(void) { }

struct foo x = 0;

void g(struct foo *ht) {
  ht->f();
}

int i = 0;

void *thread_main(void *arg ) 
{
  g(&x);
  i = 0;//race
  return 0;
}
int main(int argc , char **argv ) 
{
  pthread_t t1;
  x.f = f;
  pthread_create(&t1, 0, & thread_main, 0);
  i = 0;//race
  return 0;
}
