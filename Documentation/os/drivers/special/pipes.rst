===========================
FIFO and named pipe drivers
===========================

A pipe is a byte stream with a writer at one end and a reader at the other.
NuttX implements them as character drivers, so a pipe is read and written
with the same ``read()`` and ``write()`` any other file uses, and a thread
blocked on an empty pipe is in the same ``WAIT_SEM`` state as any other
blocked thread.

The code is in ``drivers/pipes/``.

Two kinds
=========

``pipe()``
   An anonymous pipe.  It returns two file descriptors and has no name in
   the file system, so only the process that created it -- and anything that
   inherits its descriptors -- can reach it.

``mkfifo()``
   A named pipe.  It creates an entry under ``/dev/`` that any task can
   open, which is how two unrelated programs use one.

Both are POSIX interfaces and behave as POSIX describes them; see
:doc:`/reference/user/10_filesystem` for the calls themselves.

Buffering and blocking
======================

A pipe holds a fixed ring buffer.  ``CONFIG_DEV_PIPE_SIZE`` sets the default
size in bytes, and ``CONFIG_DEV_PIPE_MAXSIZE`` caps what a program may ask
for at runtime.  Setting ``CONFIG_DEV_PIPE_SIZE`` to zero removes pipe
support altogether.

The size is worth choosing rather than accepting, because it decides when
each side blocks:

* a reader blocks while the buffer is empty, unless the pipe was opened with
  ``O_NONBLOCK``;
* a writer blocks while the buffer is full, for the same reason.

A buffer that is too small turns a producer and a consumer into a pair of
threads that hand the CPU back and forth on every message.  A buffer that is
too large is memory that sits idle in a system that usually does not have
much of it.
