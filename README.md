# cse101 pa4

**The following are the files required for programming assignment #4**

# files and how they work

`Sparce.c`: main program that reads an input file, initializes and builds the matrices A and B then calculates and prints the following matrices to the output file: A, B, (1.5)A, A+B, A+A, B-A, A-A, transpose(A), AB, BB.

`Matrix.c`: source code for Matrix ADT's functions

`Matrix.h`: header file that declares the interface and functions for Matrix ADT

`MatrixTest.c`: test client file for checking the usability of the Matrix ADT

`List.c`: source code for List ADT's functions

`List.h`: header file that declares the interface and functions for List ADT

`ListTest.c`: test client file for checking the usability of the List ADT

`Makefile`: file that runs a set of commands that build the program and create the executable file

# build/run/clean

In order to compile and run this program, you will need the Makefile, c source code files, and the header file.

To build the Sparce program:
```
$ make
```
and to run Sparce:

```
$ ./Sparce <infile> <outfile>
```

To build the Matrix ADT test program:
```
$ make MatrixTest

```
and to run MatrixTest:

```
$ ./MatrixTest
```

To remove all binary files, run:
```
$ make clean
```

