typedef struct {} spinlock_t;

int x;

static spinlock_t registration_lock;

void module_loaded(void) {
  spin_lock_init(&registration_lock);
}
static void module_activity() {
  _spin_lock(&registration_lock);
  x = 3;
  _spin_unlock(&registration_lock);
}

typedef int pthread_t;

int main() {
  pthread_t t;
  module_loaded();
  pthread_create(&t, (void*)0, module_activity, (void*)0);
  pthread_create(&t, (void*)0, module_activity, (void*)0);
}
