#include <stdarg.h>
#include <pthread.h>

struct hist_data {
   int req ;
};
void Log(char *fmt  , ...) ;
void resume_get() ;
void *signal_waiter(void *arg ) ;
int *req  ;
pthread_t hthread  ;
struct thread_data *wthread  ;
int main(int argc , char **argv ) {
  struct hist_data h ;

  req = (int *)calloc(1U, sizeof(int ));
  pthread_create(&hthread, 0, & signal_waiter, 0);
  Log((char *)"Attempting to read log file %s for resuming download job...", "A");
  resume_get();
  return (0);
}
void resume_get() {
  int i;
  memcpy(req, &i, 0);
}
void Log(char *fmt  , ...) 
{ va_list ap ;
  va_start(ap, fmt);
  va_end(ap);
}
void *signal_waiter(void *arg ) 
{ 
  int i;
  memcpy(&i, req, 0);
  return ((void *)0);
}
