===========================
``/dev/null`` and friends
===========================

The small pseudo-devices that behave like files but are not backed by
anything.  They exist because a program should be able to write output
nowhere, or read an endless supply of zeros, without that being a special
case in the program.

The code is in ``drivers/misc/``.

.. list-table::
   :header-rows: 1
   :widths: 18 22 60

   * - Device
     - Enabled by
     - Behaviour
   * - ``/dev/null``
     - ``CONFIG_DEV_NULL``
     - Reads return end of file immediately; writes succeed and discard
       everything.  The usual way to silence output that you cannot turn off
       at the source.
   * - ``/dev/zero``
     - ``CONFIG_DEV_ZERO``
     - Reads return as many zero bytes as asked for and never end; writes are
       discarded.  Useful for filling a buffer or a file with a known value,
       and for measuring how fast something can read.
   * - ``/dev/mem``
     - ``CONFIG_DEV_MEM``
     - Physical memory as a file, so it can be read and written by offset.
       Powerful and unguarded: it is a debugging tool, not a production
       interface.
   * - ``/dev/ascii``
     - ``CONFIG_DEV_ASCII``
     - Reads return the printable ASCII characters, repeating.  A test
       pattern with the useful property of being readable in a hex dump.

Each costs almost nothing to enable, which is why ``/dev/zero`` defaults to
on unless ``CONFIG_DEFAULT_SMALL`` is set.  On a system that is genuinely
tight, they are among the first things to turn off, because a program that
really needs them is rare.
