typedef long spinlock_t;
struct net_device
{
  long trans_start;
  spinlock_t xmit_lock;
  int (*open) (struct net_device * dev);
  int (*hard_start_xmit) (int * i, struct net_device * dev);
};
typedef int (*plip_func) (struct net_device * dev, int *i);
char read_status (struct net_device *dev) {
  dev->hard_start_xmit = 0;
  dev->open = 0;
}
int plip_receive_packet (struct net_device *dev, int *i);
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
  dev->trans_start = (long) 0;
};
struct net_device dummydev;
void xmit_packet () {
  struct net_device * d = &dummydev;
  int *i = kmalloc (sizeof (int), 0);
  plip_tx_packet (i, d);
}
void module_activity () {
  _spin_lock (&dummydev.xmit_lock);
  xmit_packet ();
  _spin_unlock (&dummydev.xmit_lock);
  plip_receive_packet(&dummydev, 0);
}
typedef int pthread_t;
int main () {
  pthread_t t;
  spin_lock_init (&dummydev.xmit_lock);
  pthread_create (&t, (void *) 0, module_activity, (void *) 0);
  pthread_create (&t, (void *) 0, plip_interrupt, (void *) &dummydev);
}
