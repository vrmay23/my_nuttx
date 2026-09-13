============================================
Inter-Processor Communication Channel (IPCC)
============================================

A character device for talking to another processor on the same chip.  The
application opens ``/dev/ipccN``, writes to send and reads to receive; what
carries the bytes is hardware specific and hidden behind the driver.

The code is in ``drivers/ipcc/``.

Why a character device
======================

Because it means no new interface to learn.  A program that already knows
how to read and write a file can talk to the other core, and everything that
already works on file descriptors -- ``poll()``, blocking and non-blocking
mode, redirection -- works here too without anything being added for it.

A board port provides the lower half: a driver that knows how the two
processors actually signal each other, usually a mailbox register and an
interrupt.  What the upper half adds is the buffering and the file
descriptor semantics.

When to use something else
==========================

IPCC is a byte pipe between two processors.  If what you need is a *service*
on the other processor -- a file system, a network stack, a clock
controller -- then :doc:`RPMSG </os/drivers/special/rpmsg/index>` is the
better answer: it has named channels and a request/response shape, and
several subsystems already speak it.
