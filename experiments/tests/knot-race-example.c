typedef struct {} pthread_mutex_t;
typedef struct {} pthread_mutexattr_t;
typedef unsigned int PRUint32;
struct PLHashTable;
typedef struct PLHashTable PLHashTable;
typedef PRUint32 PLHashNumber;
struct PLHashTable {
   PLHashNumber (*keyHash)(void const   *key ) ;
};
typedef struct {} pthread_attr_t;
typedef unsigned long pthread_t;
extern int pthread_mutex_init(pthread_mutex_t *   __mutex , pthread_mutexattr_t const   *   __mutex_attr ) ;
extern int pthread_mutex_lock(pthread_mutex_t *__mutex ) ;
extern int pthread_mutex_unlock(pthread_mutex_t *__mutex ) ;
void *PL_HashTableLookup(PLHashTable *ht , void const   *key ) ;
int PL_CompareStrings(void const   *v1 , void const   *v2 ) ;
pthread_mutex_t g_cache_mutex  ;
static PLHashTable *g_hash  =    (PLHashTable *)((void *)0);
extern int pthread_create(pthread_t *   __threadp , pthread_attr_t const   *   __attr ,
                          void *(*__start_routine)(void * ) , void *   __arg ) ;



int g_cache_misses  =    0;
void *thread_main(void *arg ) 
{
  /* BUG!  If the following line is uncommented, a race is NOT detected */
  PL_HashTableLookup(g_hash, "");
  g_cache_misses ++;
  return 0;
}
int main(int argc , char **argv ) 
{
pthread_t t1;
  pthread_mutex_init(& g_cache_mutex, 0);
  g_hash = (PLHashTable *) malloc(1);
  g_hash->keyHash = PL_CompareStrings;
  pthread_create(&t1, 0, & thread_main, 0);
  g_cache_misses = 0;
}
void *PL_HashTableLookup(PLHashTable *ht , void const   *key ) 
{
  PLHashNumber keyHash ;
  keyHash = ((*(ht->keyHash)))(key);
  return 0;
}
int PL_CompareStrings(void const   *v1 , void const   *v2 ) 
{
  return 0;
}
