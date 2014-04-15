/*
 * There is a problem with this example.
 * When typing it context sensitively, we add hard_start_xmit to el1_prove.dev,
 * which instantiates to the return value of alloc_etherdev.  When propagating
 * the field accross the instantiation, we call annotate on its hard_start_xmit
 * field, which (via the known list) will assign the same struct type of
 * alloc_etherdev.ret to the function argument of
 * alloc_etherdev.ret->hard_start_xmit.  This conflates things.
 */
struct net_device
{
  unsigned long trans_start;
  int (*hard_start_xmit) (struct net_device * dev);
};

struct net_device dummydev;

int el_start_xmit (struct net_device *dev) {
  dev->trans_start = 0;
}

int el1_probe () {
  struct net_device *dev;
  dev = alloc_etherdev();
  dev->hard_start_xmit = &el_start_xmit;
}

struct net_device * alloc_etherdev () {
  return &dummydev;
}
