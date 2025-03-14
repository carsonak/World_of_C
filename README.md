# World_Of_C - C practice repo

Playing around with various C features.

## Structure

Most directories have Makefiles with recipes used to compile the files in that
directory.
To compile a file, change into a directory with both `.c` files and a Makefile
then run a [make](https://en.wikipedia.org/wiki/Make_(software)) command of the form below in a terminal:

```bash
make bin/example_file
```

Where `example_file` is the name of a file in the current directory with its
`.c` suffix strop off. The compiled program can then be run normally:

```bash
./bin/example_file
```
