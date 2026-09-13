=================
UserFS
=================

A file system implemented by an ordinary application rather than by kernel
code.  The kernel side is a stub that forwards every VFS operation to a
server task, which answers however it likes.

Enabled with ``CONFIG_FS_USERFS``.  The code is in ``fs/userfs/``.

What it is for
==============

Anything where the file system logic does not belong in the kernel:

* a file system that talks to a remote service, where the implementation
  wants to make network calls and block freely;
* a bridge to storage a vendor library already knows how to reach;
* a file system being developed, where a crash in a task is much easier to
  live with than a crash in the kernel.

The application sees ``/mnt/whatever`` and calls ``open()`` on it like any
other path.  It does not know a task is answering.

How the operations get there
============================

The kernel side registers a factory driver at ``/dev/userfs``.  A server
task mounts the file system and then stays in a loop serving requests until
it is unmounted.

The transport is a **local UDP socket**, which is why ``CONFIG_FS_USERFS``
depends on ``CONFIG_NET_IPv4``, ``CONFIG_NET_UDP`` and
``CONFIG_NET_LOOPBACK``.  This surprises people: a file system that touches
no network still needs the network stack configured, because that is the
IPC it is built on.

What it costs
=============

Every operation is a round trip to another task: a context switch out, the
server's work, a context switch back.  For a file system whose backing store
is slow anyway -- a network, a bus, a device behind a vendor library -- that
overhead disappears into the noise.  For anything where latency matters, a
kernel file system is the right answer.
