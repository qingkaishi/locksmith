#!/bin/bash
rm -f core.*
rm -f killed

gcc -c w.c >/dev/null 2>&1
if [ $? -ne 0 ]; then exit 1; fi

../timeout.sh 60 ../../locksmith w $@
if [ -f killed ]; then
  exit 1;
fi

../timeout.sh 300 ../../locksmith w $@ --use-worklist
if [ -f killed ]; then
  exit 0;
fi

exit 1
