===================================
Block-to-character (BCH) conversion
===================================

Block drivers are read and written a sector at a time; character drivers
are read and written a byte at a time.  BCH sits between the two, so a block
device can be opened, read and written as if it were a character device.

The code is in ``drivers/bch/``.

What it is for
==============

Two situations, both common:

* A program wants to read a few bytes from the middle of a partition --
  a header, a serial number, a configuration blob -- and does not want to
  know the sector size.
* A file system image has to be written to a partition from user space, with
  an ordinary ``write()``, rather than a sector at a time.

Interface
=========

.. c:function:: int bchdev_register(FAR const char *blkdev, FAR const char *chardev, int oflags)

   Exports the block driver at ``blkdev`` as the character device
   ``chardev``.

   :param blkdev: The block device that already exists, for example
     ``/dev/mtdblock0``.
   :param chardev: The character device to create, for example
     ``/dev/mtd0``.
   :param oflags: Open flags.  Read-only unless write access is asked for.
   :return: Zero on success; a negated ``errno`` on failure.

.. c:function:: int bchdev_unregister(FAR const char *chardev)

   Removes a character device created by ``bchdev_register()``.

   :param chardev: The character device to remove.
   :return: Zero on success; a negated ``errno`` on failure.

How it works, and what it costs
===============================

BCH keeps one sector-sized cache.  A read that falls inside the cached
sector is answered from memory.  A read that does not causes the sector to
be fetched first.  A write is a read-modify-write: the sector is read,
the bytes are changed in the cache, and the sector is written back.

That last point is the cost worth knowing.  Writing one byte through BCH
rewrites a whole sector.  On flash, where a sector rewrite may mean an
erase, a program that writes bytes one at a time through BCH will be slow
and will wear the device -- which is an argument for buffering in the
application, or for using the block interface directly when the access
pattern is already sector-shaped.

``CONFIG_BCH_BUFFER_ALIGNMENT`` sets the alignment of that cache, for
hardware that needs its DMA buffers aligned.

Encryption
==========

``CONFIG_BCH_ENCRYPTION`` encrypts sectors with AES as they pass through,
using a key of ``CONFIG_BCH_ENCRYPTION_KEY_SIZE`` bytes.  It requires
``CONFIG_CRYPTO_AES``.
