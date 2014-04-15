typedef struct spinlock_t{} spinlock_t;
struct net_device
{
  long trans_start;
  spinlock_t xmit_lock;
  int (*open) (struct net_device * dev);
  //int * open;
  int (*hard_start_xmit) (int * i, struct net_device * dev);
};
char read_status (struct net_device *dev) {
  dev->hard_start_xmit = 0;
  dev->open = 0;
}
short plip_type_trans (int *i, struct net_device *dev) {
  *i = 0;
}
int plip_receive_packet (struct net_device *dev, int *i) {
  read_status(dev);
  plip_type_trans (i, dev);
  *i = 0;
}
void plip_interrupt (void *dev_id) {
  read_status (dev_id);
}
int plip_tx_packet (int *i, struct net_device *dev) {
  dev->trans_start = 0;
};
struct net_device dummydev;
void xmit_packet () {
  int *i = malloc (sizeof (int));
  plip_tx_packet (i, &dummydev);
}
int i;
int module_activity (void * ign) {
  _spin_lock (&dummydev.xmit_lock);
  xmit_packet ();
  _spin_unlock (&dummydev.xmit_lock);
  plip_receive_packet(&dummydev, &i);
  return 0;
}
typedef int pthread_t;
int main () {
  pthread_t t;
  spin_lock_init (&dummydev.xmit_lock);
  pthread_create (&t, (void *) 0, module_activity, (void *) 0);
  pthread_create (&t, (void *) 0, plip_interrupt, (void *) &dummydev);
}
