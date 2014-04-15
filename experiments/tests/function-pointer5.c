/*
 * There is an extra dereference in ok/function-pointer5.out compared to
 * out/function-pointer5.out.  I've left that in, because it's not a duplicate.
 * Hashconsing on guards got rid of duplicates and this one dereference.  The
 * soundness does not change, but when this scenario occurs (no instantiation
 * in a cycle) we might lose one dereference and only keep the one with the
 * longest call-path.
 * This is because adding one element to the path at the function-pointer
 * callsite, will give a guard with everything else being the same, and the
 * call path extended by one.  This will hide the preexisting guard that has a
 * sub-path for its callpath.  In all other cases it's fine to do so (and even
 * preferrable) but here we might miss a real dereference with an actually
 * shorter path.  Reporting the longer path is still correct but might not be
 * as readable.
 */

#include <pthread.h>
#include <stdio.h>

typedef void (*fptr)(void*);

int i;

void bar(void* arg) {
  fptr x = (fptr) arg;
  i++;//race
  x(arg);
}

fptr foo = &bar;

int main() {
  pthread_t t1;
  pthread_create(&t1, NULL, foo, foo);
  foo(foo);
}


