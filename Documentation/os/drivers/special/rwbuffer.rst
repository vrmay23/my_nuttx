==============================
Read-ahead and write buffering
==============================

A layer that sits between a driver and the block device under it, so that a
stream of small accesses becomes a smaller number of large ones.  The driver
does not implement any of it; it hands its sector read and write functions
to this layer and lets it decide when to talk to the hardware.

The code is in ``drivers/misc/rwbuffer.c``, and the interface is in
``include/nuttx/drivers/rwbuffer.h``.

What it does
============

``CONFIG_DRVR_WRITEBUFFER``
   Collects writes in memory and flushes them as one larger write.  This
   matters most on flash, where a write is preceded by an erase: turning
   four sector writes into one can be the difference between usable and
   unusable.

``CONFIG_DRVR_READAHEAD``
   When a sector is read, reads the ones after it too, on the assumption
   that a file being read sequentially will want them.  A hit is answered
   from memory; a miss cost one larger read instead of one small one.

Both are opt-in, and both trade RAM for throughput.

What it costs
=============

Write buffering means **data that the application believes is written may
still be in RAM**.  ``CONFIG_DRVR_WRDELAY`` sets how long the layer is
allowed to wait before flushing, and until that flush happens a power loss
loses the data.  This is the same bargain every operating system makes, and
the same answer applies: if it matters, flush it, and understand that
flushing is what costs the time buffering saved.

Read-ahead is cheaper to reason about -- a wrong guess wastes a little time
and some RAM, and nothing is lost -- but it is still RAM that a small system
may not have.
