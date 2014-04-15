struct foo {
  int a;
  int b;
};

int main() {
  struct foo *f, *bar;
  f = (struct foo *) malloc(sizeof(struct foo));
  f = bar;
  f->a = 1;
  bar->b = 0;
}
