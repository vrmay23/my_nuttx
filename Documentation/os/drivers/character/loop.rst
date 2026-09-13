=================
Loop device
=================

Makes a **file** look like a **block device**, so that something which
expects a disk can be given a file instead.  The usual reason is to mount a
file system image without having a partition to put it on.

Enabled with ``CONFIG_DEV_LOOP``.  The code is in ``drivers/loop/``, and the
control device is ``/dev/loop``.

How it is used
==============

Two ioctls on ``/dev/loop``, defined in ``include/nuttx/fs/loop.h``:

``LOOPIOC_SETUP``
   Takes a ``struct losetup_s`` naming the file to wrap and the block device
   node to create.  After this, that node can be mounted.

``LOOPIOC_TEARDOWN``
   Takes the path of a node created by ``LOOPIOC_SETUP`` and removes it.

In practice this is done from the shell rather than from C, with the
``losetup`` command in NSH.

Why it is useful on an embedded system
======================================

It is easy to dismiss as a desktop convenience, but it earns its place:

* A file system image built on the host can be dropped onto whatever storage
  the board has -- even a ROMFS in flash -- and mounted from there, without
  the image having to own a partition.
* It makes file system code testable in the simulator, where there is no
  block device at all but there are plenty of files.

What to watch for
=================

The loop device adds a layer: every block access becomes a file access,
which becomes whatever the file's own file system does.  Two file systems
are now in the path, and so are two sets of buffers.  Fine for images and
for testing; a poor idea for anything on a hot path.
