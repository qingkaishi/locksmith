struct s {
  struct s *next;
  void (*f) (struct s * dev);
};

void g(struct s *dev) {
  dev->f = &g;
};

void el1_probe (struct s *dev) {
  g(dev);
}

void h (void *dev_id) {
  struct s *dev;
  dev = (struct s *) dev_id;
  dev->next = 0;
}

int main () {
  int t;
  struct s dummydev;

  el1_probe(&dummydev);
  pthread_create (&t, (void *) 0, h, (void *) &dummydev);
  g(&dummydev);
}
