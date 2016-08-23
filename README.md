The user_rdpmc Linux Kernel Module
==================================

A simple Linux kernel module which, when loaded, allows ring 3 (userspace)
programs to use the `RDPMC` assembler instruction by flipping the `PMC` flag in
the `CR4` register.

This module only makes sense on an x86 machine.

Building
--------

Install Linux kernel headers and run `make`.

The build currently assumes a Debian Linux system. You may have to tweak some
paths in the Makefile for other distributions.

Using
-----

First run the `test_rdpmc` program and check that the program crashes, thus
confirming that the userspace cannot invoke `RDPMC`.

Insert the module with `sudo insmod user_rdpmc.ko`. The dmesg buffer should
then display a message similar to:

```
[ 5016.743382] Enabling RDPMC from ring 3 for 4 CPUs
```

Now if you re-run the test program, it should not crash. Userspace can now
invoke `RDPMC`.

If you remove the `user_rdpmc` module, userspace is then denied use of `RDPMC`.
