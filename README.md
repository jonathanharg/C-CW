# C Continuous Assessment

## Compilation

Compile this code in the root project directory with

```shell
~ make
```

This should default to making all targets for all questions (if this doesn't work try `make all`).

Additionally, each question in each subfolder can be compiled separately with `make all`. Or
a specific target can be built e.g. `make piglatin` (run in `./1-Pig-latin`).

## Valgrind Errors

This project should have no memory leaks. However there is (what I believe to be) a Valgrind false
positive in `beggar.c` (see lines 127 - 132 for more details). Because this single false positive is
in a frequently called function, `byn` easily report 150,00 (probably unjustified) errors.
