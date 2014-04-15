struct net_device {
   void *priv ;
};
struct slave {
   struct net_device *dev ;
};
typedef int pthread_t;
struct net_device dummydev  ;
void f1(void *param ) { 
  return;
}

struct slave *f2(void) {
  struct slave *slave ;
  slave = (struct slave *)((struct slave *)0)->dev;
  slave->dev = (struct net_device *)0;
  return (slave);
}

void xmit_packet(void) {
  struct slave skb ;
  struct slave *slave ;
  struct slave *tmp ;
  tmp = f2();
  slave = tmp;
  skb.dev = slave->dev;
  skb.dev = & dummydev;
  dummydev.priv = (void *)0;
  f1((void *)(& dummydev));
  return;
}
void (*f3)()  =    & xmit_packet;
extern int ( /* missing proto */  pthread_create)() ;
int main(void) {
  pthread_t t ;
  pthread_create(& t, (void *)0, f3, (void *)0);
  (*f3)();
  return (0);
}
