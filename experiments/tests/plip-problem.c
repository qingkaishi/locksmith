struct net_device {
	void           *priv;
	int             (*open) (struct net_device * dev);
	int             (*hard_header_cache) (struct neighbour * neigh);
};
struct parport_driver {
	void            (*attach) (struct parport *);
};
struct neighbour {
	struct net_device *dev;
};
struct net_local {
	void            (*func) (void *);
};
typedef int     (*plip_func) (struct net_device * dev);
static void    *
netdev_priv(struct net_device * dev)
{
	return dev->priv;
}
static void     plip_bh(struct net_device * dev);
static int      plip_hard_header_cache(struct neighbour * neigh);
static int plip_open(struct net_device * dev)
{
	struct net_local *nl;
	struct net_local *tmp;
	tmp = (struct net_local *) netdev_priv(dev);
	nl = tmp;
	dev->open = &plip_open;
	dev->hard_header_cache = &plip_hard_header_cache;
	nl->func = (void (*) (void *)) (&plip_bh);
}
static plip_func connection_state_table;
static void plip_bh(struct net_device * dev)
{
		netdev_priv(dev);
		((*connection_state_table)) (dev);
}
static int plip_hard_header_cache(struct neighbour * neigh)
{
	void *nl;
	nl = (void *) (neigh->dev)->priv;
}
static struct net_device *dev_plip[8] = {
};
struct net_device *alloc_etherdev(int ign);
static void 
plip_attach(struct parport * port)
{
	struct net_device *dev;
	int             tmp;
	int             tmp___0;
	dev = alloc_etherdev((int) sizeof(struct net_local));
	tmp = register_netdev(dev);
	dev_plip[tmp___0] = dev;
}
static struct parport_driver plip_driver = { &plip_attach};
static void 
plip_cleanup_module(void)
{
	struct net_device *dev;
	int             i;
	struct net_local *tmp;
	parport_unregister_driver(&plip_driver);
	dev = dev_plip[i];
	tmp = (struct net_local *) netdev_priv(dev);
}
struct net_device dummydev;
int 
register_netdev(struct net_device * dev)
{
}
struct net_device *
alloc_etherdev(int ign)
{
	struct net_device *dev = &dummydev;
	struct net_local *priv = kmalloc(sizeof(struct net_local), 0);
	dev->priv = (void *) priv;
	return dev;
}
static void 
module_activity()
{
	plip_open(&dummydev);
}
typedef int     pthread_t;
int 
main()
{
	pthread_t       t;
	pthread_create(&t, (void *) 0, module_activity, (void *) 0);
	plip_cleanup_module();
}
