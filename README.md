# Loop-printing-pass

> Here we go again...

A completely useless LLVM pass.
It's for LLVM 17.
Based on Adrian Sampson's amazing skeleton LLVM pass.

Build:

    $ cd llvm-pass-skeleton
    $ mkdir build
    $ cd build
    $ cmake ..
    $ make
    $ cd ..

Run:

    $ clang -O -fpass-plugin=`echo build/pass/LoopPrintingPass.*` runtime/runtime.c something.c

Example:

    $ clang -O -fpass-plugin=`echo build/pass/LoopPrintingPass.*` runtime/runtime.c example.c
    $ ./a.out
    Here we go again...
    1^2 = 1
    Here we go again...
    2^2 = 4
    Here we go again...
    3^2 = 9
    Here we go again...
    4^2 = 16
    Here we go again...
    5^2 = 25
    Here we go again...
    6^2 = 36
    Here we go again...
    7^2 = 49
    Here we go again...
    8^2 = 64
    Here we go again...
    9^2 = 81
    Here we go again...
    10^2 = 100
    Here we go again...

