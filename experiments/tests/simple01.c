#include <pthread.h>
#include <stdio.h>

void * dostuff(void * a) {
  *(int *)a = 0;
}

int main() {
  int* i;
  i	= &dostuff;
  dostuff(NULL);
}
