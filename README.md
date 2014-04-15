LOCKSMITH
=========
This is a modified version of LOCKSMITH, please refer to its homepage
for details.

The contributors are

*Polyvios Pratikakis
*Jeffrey S. Foster
*Michael Hicks

This file is partially edited by Qingkai Shi (qingkaishi@gmail.com)

Homepage
------
http://www.cs.umd.edu/projects/PL/locksmith/index.html

If you are using Locksmith, please drop me (polyvios-at-cs.umd.edu) an 
email (substitute @ for -at- in the address) to let me know.

Building Locksmith
------------------

```bash
tar -xzvf locksmith-xxx.tar.gz
cd locksmith-xxx
./configure 
make
```
 
If all goes well, this is enough to build Locksmith. Locksmith is implemented 
in OCaml and uses CIL (written in Ocaml) and Banshee (written in C). We have 
builted and tested it on *32-bit* x86 linux, and Darwin PowerPC architectures using 
gcc versions 3.2.3, 4.0.0, 4.1.2 and 4.8.1 and OCaml versions 3.08.1, 3.09.1 and 
3.09.2. When changing ocaml compilers the ordering of the output might change.

Running Locksmith
-----------------
Locksmith is run using the cilly CIL driver, which is stored in locksmith/cil/bin/cilly. 
Since Locksmith performs a whole program analysis, it needs to be supplied with 
all the source files in the program. For simple applications, running the following 
command is enough to cause CIL to merge all input C files before invoking Locksmith. 
We provide stub definitions for several library functions in locksmith/experiments/lib.c. 
All undefined functions in the final merged program will be listed as warnings.

```bash
/path/to/locksmith/cil/bin/cilly --merge *.c
```

Please refer to its homepage for detailed usage.



