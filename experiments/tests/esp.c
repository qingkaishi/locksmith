typedef int pthread_t;
struct tty_struct {
  void (*flush_buffer) (struct tty_struct * tty);
  struct tty_struct *tty;
  int flags;
};

void set_bit (int *addr) {
  *addr = 1;
};
void shutdown (struct tty_struct *tty) {
  set_bit (&tty->flags);
}
void rs_close (struct tty_struct *tty) {
  //tty->flags++;
  shutdown(tty);
  tty->flush_buffer(tty);
}
int esp_open (struct tty_struct *tty) {
  set_bit(&tty->tty->flags);
}
void (*close) (struct tty_struct * tty) = &rs_close;

struct tty_struct tty;
void * f (void *ign) {
  struct tty_struct *t = &tty;
  esp_open(&tty);
}
int main () {
  pthread_t t;
  pthread_create (&t, (void *) 0, f, (void *) 0);
  f(0);
}
