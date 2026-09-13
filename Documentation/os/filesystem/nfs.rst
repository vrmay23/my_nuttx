===
NFS
===

A client for the Network File System: a directory served by another machine,
mounted so that programs read and write it as if it were local.  There is no
server side in NuttX -- the board is always the client.

Enabled with ``CONFIG_NFS``.  The code is in ``fs/nfs/``.

What is implemented
===================

**NFS version 3, over UDP.**  The protocol is in ``nfs_proto.h``, the RPC
layer that carries it in ``rpc_clnt.c``, and the VFS side -- the part that
makes it look like a file system -- in ``nfs_vfsops.c``.

``CONFIG_NFS`` depends on ``CONFIG_ALLOW_BSD_COMPONENTS``, because this code
came from BSD and carries that licence.  A build that must avoid BSD
licensed code cannot use it.  It also selects ``CONFIG_FS_LARGEFILE``, since
the protocol works in 64-bit offsets.

What it is good for
===================

The thing NFS gives an embedded system is **storage the board does not have
to own**:

* logs and captured data that would not fit in flash, and that somebody will
  want to look at from a desktop anyway;
* a root file system served from a workstation during development, so that
  changing a program does not mean reflashing.

The cost is the obvious one, and it is worth being explicit about it: every
read and write is a network round trip.  A program that opens a file over
NFS and reads it a byte at a time will be very slow, and the fix is
buffering in the application rather than anything in the driver.  UDP also
means the client is responsible for retries; a lossy link shows up as
latency, not as errors.

Setting one up
==============

:doc:`/guides/networking/nfs` covers the practical side: what to put in the
configuration, how to mount from NSH, and how to configure the server on the
other end.
