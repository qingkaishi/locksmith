#!/bin/bash
rm -f core.*
rm -f killed

gcc -c eql.c >/dev/null 2>&1
if [ $? -ne 0 ]; then exit 1; fi

../../locksmith eql.c --list-shared --stop-after=shared > cs.txt 2>&1
x=`./getshared.sh cs.txt |grep dummydev | wc -l`
if [ $x -ne 1 ]; then exit 1; fi

../../locksmith eql.c --list-shared --stop-after=shared --context-insensitive > ci.txt 2>&1
x=`./getshared.sh ci.txt |grep dummydev | wc -l`
if [ $x -ne 0 ]; then exit 1; fi

exit 0
