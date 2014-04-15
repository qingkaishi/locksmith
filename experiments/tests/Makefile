ECHO=@

TESTS = \
	1-field-alloc.c \
	1-field-shared.c \
	addrof.c \
	alias.c \
	badlock.c \
	context-sensitive1.c \
	context-sensitive2.c \
	context-sensitive3.c \
	context-sensitive4.c \
	downfork.c \
	downfork2.c \
	ds0.c \
	ds1b.c \
	ds1.c \
	ds2.c \
	ds2b.c \
	ds3.c \
	ds4.c \
	ds4b.c \
	ds5.c \
	ds6.c \
	ds7.c \
	ds-gftp.c \
	ds-gftp2.c \
	effects.c \
	entrystate.c \
	exist.c \
	exist1.c \
	exist2.c \
	exist3-false-positive.c \
  exist4.c \
	flowshare1.c \
	flowshare2.c \
	forkloop.c \
	forkloop2.c \
	forkloop3.c \
	function-pointer1.c \
	function-pointer2.c \
	function-pointer3.c \
	function-pointer4.c \
	function-pointer5.c \
	goto.c \
	goto1.c \
	lock.c \
	loop.c \
	malloc.c \
	malloc2.c \
	malloc2a.c \
	no-field-alloc.c \
	nonlex.c \
	norace1.c \
	norace2.c \
	paper-example.c \
	pool.c \
	race1.c \
	race2.c \
	recursive1.c \
	recursive2.c \
	simple00.c \
	simple01.c \
	simple02.c \
	simple1b.c \
	simple1.c \
	simple1c.c \
	simple2b.c \
	simple2.c \
	simple3.c \
	simple4.c \
	simple5.c \
	simple6.c \
	simple7.c \
	simple8.c \
	split-fp.c \
	state.c \
	structs1.c \
  switch.c \
  switch1.c \
  switch2.c \
	test1.c \
	test2.c \
	test3b.c \
	test3.c \
	test4.c \
	test5.c \
	test6.c \
	thread-ex.c \
	uniq.c \
	uniq1.c \
	uniq1a.c \
	uniq2.c \
	uniq3.c \
	uniq4.c \
	uniq5.c \
	uniq6.c \
	uniq-fn.c \
	va_list1.c \
	voidptr1.c \
	voidptr2.c \
	voidptr3.c \
	voidptr4.c \
  wrapper1.c
# $(wildcard *.c)

# Why are we doing bytecode?  We run the real thing with native, that's what should be here!
#CILLY=../../cil/bin/cilly --bytecode --save-graph --list-shared --list-guardedby -lpthread
CILLY=../../cil/bin/cilly --save-graph --list-shared --list-guardedby -lpthread
OPTS=

all: init runall

runall: runintro $(TESTS:%.c=out/%.out)
	$(ECHO) echo "</table></html>" >> out/report.html

runintro:
	$(ECHO) echo "running all tests"

init:
	$(ECHO)$(RM) -r out
	$(ECHO)mkdir out
	$(ECHO) echo "<html><table border=1pt>" > out/report.html
	$(ECHO)test -f core && $(RM) -f core || true

cleanok:
	$(ECHO)$(RM) ok/*.out

clean:
	$(ECHO)$(RM) core a.out graph*.dot cf-graph.dot su?.dot *graph.ps a.out graph.txt *~
	$(ECHO)$(RM) out/* diffs/*

out/%.out: %.c
	$(ECHO) echo -n $<
	$(ECHO) echo -n "<tr> <td> $< <td> " >> out/report.html
	$(ECHO)$(CILLY) --save-profile-data=out/$(basename $<).txt $(OPTS) $< 2>&1 | \
		awk -f filter.awk | \
		sed -e 's/#[0-9]*\\n//g' > $@; \
	if test -f core || test 0 -ne `ls core.* 2>/dev/null|wc -l`; \
	then \
		/bin/echo -e "\\033[30G \\033[1;31m core dump \\033[0;39m"; \
		echo " core dump" >> out/report.html; \
		$(RM) core core.*; false; \
	fi
	$(ECHO) \
	if test -f ok/$(basename $<).dot;\
	then \
		cat graph.dot | sed -e 's/#[0-9]*\\n//g' > out/$(basename $<).dot; \
		sort out/$(basename $<).dot > out/$(basename $<).dot.sorted; \
		sort ok/$(basename $<).dot > ok/$(basename $<).dot.sorted; \
		if diff -Bb \
			ok/$(basename $<).dot.sorted out/$(basename $<).dot.sorted > /dev/null; \
			then true; \
			else \
				/bin/echo -e "\\033[30G \\033[1;31m graphs differ \\033[0;39m"; \
				echo " graphs differ" >> out/report.html; \
				true; \
		fi; \
	fi && \
	if diff -Bb ok/$(basename $<).out $@ > /tmp/out$$ 2>&1; \
		then $(RM) /tmp/out$$; true; \
		else \
			/bin/echo -e "\\033[30G \\033[1;31m output differs \\033[0;39m";  \
			/bin/echo -e "\\033[30G \\033[1;31m old: " `grep "Possible data race" ok/$(basename $<).out | wc -l`"  new: " `grep "Possible data race" out/$(basename $<).out | wc -l`" \\033[0;39m"; \
			/bin/echo -e " output differs <br>" >> out/report.html; \
			echo "old: " `grep "Possible data race" ok/$(basename $<).out | wc -l`"  new: " `grep "Possible data race" out/$(basename $<).out | wc -l`" <br> " >> out/report.html; \
			mkdir -p diffs; mv /tmp/out$$ diffs/$(basename $<).diff; true; \
	fi && \
	/bin/echo -e "\\033[30G \\033[1;32m ok \\033[0;39m"; \
	echo "ok" >> out/report.html; \
