typedef struct {} spinlock_t;
struct net_device {
   unsigned int irq ;
};

struct net_device *dummydev;

static void plip_attach(void)
{
  dummydev = (struct net_device *) malloc(sizeof(struct net_device));
}

static spinlock_t registration_lock;

static void module_activity() {
  struct net_device *dev;

  _spin_lock(&registration_lock);
  /* If you uncomment the next line and comment out the call
     to plip_attach (i.e., you inline plip_attach), then the race
     at dummydev->irq = 5 is detected */
  //  dummydev = (struct net_device *) malloc(sizeof(struct net_device));
  plip_attach();
  _spin_unlock(&registration_lock);

  dummydev->irq = 5;
}

typedef int pthread_t;

int main() {
  pthread_t t;
  spin_lock_init(&registration_lock);
  pthread_create(&t, (void*)0, module_activity, (void*)0);
  pthread_create(&t, (void*)0, module_activity, (void*)0);
}
