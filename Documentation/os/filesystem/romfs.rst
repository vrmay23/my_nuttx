=====
ROMFS
=====

A read-only file system laid out so that files can be used **in place**:
mapped and executed straight from where they are stored, without being
copied into RAM first.  That is what it exists for, and why it is the usual
choice for the files a system ships with rather than the files it writes.

Enabled with ``CONFIG_FS_ROMFS``.  The code is in ``fs/romfs/``.

Why read-only is the point
==========================

Nothing in a ROMFS image can be changed after it is built, and that buys
several things at once:

* **No RAM for the files themselves.**  On a chip with memory-mapped flash,
  reading a ROMFS file is reading flash.  A 200 KB file costs no RAM.
* **Execute in place.**  A program in ROMFS can be run without loading it,
  which is what makes it a sensible home for built-in applications.
* **Nothing to corrupt.**  A read-only file system cannot be left
  inconsistent by a power cut, so it needs no journal, no checking at mount
  time and no wear levelling.

Where it is used
================

Two arrangements are common, and both appear throughout the board ports:

* Mounted at ``/etc`` to hold a startup script, so the shell has something
  to run at boot without a writable file system existing at all.  See
  :doc:`/guides/filesystem/etcromfs`.
* Holding the binaries that :doc:`/os/binfmt/index` loads, so programs live
  in flash rather than being linked into the kernel image.

If the files have to change at runtime, ROMFS is the wrong file system;
:doc:`/os/filesystem/index` lists the writable ones.
