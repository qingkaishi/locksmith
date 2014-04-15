// This test is likely not to work, and suggests similar problems for
// any multi-threaded container in which the elements in the container
// can transfer threads.  See the comments below.  I'm wondering if
// existentials can help us in this case too, using an "ownership"
// model.  Basically whenever we store an element in a container, the
// owning thread relinquishes control to the container, and when we
// remove an element, the container relinquishes control to the
// calling thread.

// Probably we could modify this code to at least test the global
// vs. local lock stuff.  I.e., just don't return anything from
// malloc().

#include <pthread.h>

typedef struct _qsd_pool qsd_pool;

struct _qsd_pool {
	qsd_pool *next;
	qsd_pool *prev;
        void *data;
        void *cur;
        size_t data_sz;
        pthread_mutex_t pool_lock; // protects data and data_sz
};

/* Head and tail of the pool list */
static qsd_pool *pool_list_head = NULL;
static qsd_pool *pool_list_tail = NULL;

/* Pool list mutex */
static pthread_mutex_t pool_list_lock = PTHREAD_MUTEX_INITIALIZER; // protects qsd_pool->next and prev

qsd_pool *get_new_pool ()
{
	qsd_pool *new_pool;

	new_pool = (qsd_pool *) malloc(sizeof(qsd_pool));
	new_pool->data = new_pool->cur = (void *)malloc(1000);
	new_pool->data_sz = 1000;
	new_pool->prev = NULL;
	pthread_mutex_init (&(new_pool->pool_lock),NULL);
	pthread_mutex_lock (&pool_list_lock);
	if (!pool_list_head) {
		pool_list_head = pool_list_tail = new_pool;
		new_pool->next = NULL;
	} else {
		pool_list_head->prev = new_pool;
		new_pool->next = pool_list_head;
		pool_list_head = new_pool;
	}
	pthread_mutex_unlock (&pool_list_lock);
	return new_pool;
}

void
qsd_delete_pool (qsd_pool *p)
{
	if (!p) return;

	pthread_mutex_lock (&pool_list_lock);
	if (!p->next && !p->prev) {
		pool_list_head = pool_list_tail = NULL;
	} else if (p == pool_list_head) {
		p->next->prev = NULL;
		pool_list_head = p->next;
	} else if (p == pool_list_tail) {
		p->prev->next = NULL;
		pool_list_tail = p->prev;
	} else {
		p->prev->next = p->next;
		p->next->prev = p->prev;
	}
	pthread_mutex_unlock (&pool_list_lock);
	free(p->data);
	free(p);
	// this could be bad: benign race condition for above two
	// free() calls
}

void *qsd_pmalloc (qsd_pool *p, size_t size)
{
	pthread_mutex_lock (&(p->pool_lock));
	if (p->cur + size < p->data + p->data_sz) {
		void *ret = p->cur;
		p->cur += size;
		pthread_mutex_unlock (&(p->pool_lock));
		return ret; 
		// this could be bad: analysis will think it's
		// protected by p->pool_lock in the caller, but
		// instead we've "declassified" it
	}
	pthread_mutex_unlock (&(p->pool_lock));
	return (void *) NULL;
}

/* didn't bother with free() */

void *go2(qsd_pool *p) {
  void *buf1 = qsd_pmalloc(p,10);
  void *buf2 = qsd_pmalloc(p,10);
  void *buf3 = qsd_pmalloc(p,10);
  return NULL;
}

void *go1(void *x) {
  qsd_pool *p = get_new_pool();
  void *buf1 = qsd_pmalloc(p,10);
  pthread_t t1;

  pthread_create(&t1, NULL, go2, p);
  
  buf1 = qsd_pmalloc(p,10);
  buf1 = qsd_pmalloc(p,10);
}

int main() {
  pthread_t t1,t2;

  pthread_create(&t1, NULL, go1, NULL);
  pthread_create(&t1, NULL, go1, NULL);
}
