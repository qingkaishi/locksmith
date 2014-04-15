// Last check: four races

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
};

static qsd_pool *pool_list_head = NULL;

/* Pool list mutex */
static pthread_mutex_t pool_list_lock;

qsd_pool *get_new_pool ()
{
	qsd_pool *new_pool;

	new_pool = (qsd_pool *) malloc(sizeof(qsd_pool));
	new_pool->prev = NULL;
	pthread_mutex_lock (&pool_list_lock);
	if (!pool_list_head) {
		pool_list_head = new_pool;
		new_pool->next = NULL;
	} else {
		pool_list_head->prev = new_pool;
		// Since pool_list_head is an analis for malloc()
		// above, this should cause malloc().prev to be
		// added to the write effect.
		new_pool->next = pool_list_head;
		pool_list_head = new_pool;
	}
	pthread_mutex_unlock (&pool_list_lock);
	return new_pool;
}


void *go1(void *x) {
  qsd_pool *p = get_new_pool();
}

int main() {
  pthread_t t1,t2;

  pthread_mutex_init(&pool_list_lock,NULL);
  pthread_create(&t1, NULL, go1, NULL);
  pthread_create(&t1, NULL, go1, NULL);
}
