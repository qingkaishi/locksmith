typedef int __ssize_t;
struct __anonstruct_pthread_mutex_t_6 { };
typedef struct __anonstruct_pthread_mutex_t_6 pthread_mutex_t;
typedef struct __anonstruct_pthread_mutexattr_t_7 pthread_mutexattr_t;
typedef __ssize_t ssize_t;
typedef struct cache_entry cache_entry;
#pragma existential(cache_entry, "cache_entry.refs_mutex", "&cache_entry.refs")
struct cache_entry {
  int refs;
  pthread_mutex_t refs_mutex;
  cache_entry *prev;
};
struct __pthread_attr_s { };
typedef struct __pthread_attr_s pthread_attr_t;
typedef unsigned long pthread_t;
pthread_mutex_t g_cache_mutex;
static int g_cache_cur = 0;
static void cache_remove (){
  cache_entry * entry;
  start_unpack (entry);
	g_cache_cur++;
  end_unpack(entry);
}

pthread_mutex_t g_cache_mutex;

cache_entry * get_request_entry (void) {
  cache_entry *tmp___0;
	pthread_mutex_lock (&g_cache_mutex);
	cache_remove();
	pthread_mutex_unlock (&g_cache_mutex);
  return (tmp___0);
}

void * thread_process_client (void *client) {
    get_request_entry ();
}

pthread_t thread;

void main() {
  while (1) {
     pthread_create (&thread, 0, &thread_process_client, 0);
  }
  pthread_mutex_init (&g_cache_mutex, 0);
}
