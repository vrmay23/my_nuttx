=====
eFuse
=====

An eFuse is memory that can be written **once**.  A bit that has been burned
stays burned: there is no erase, and no way back.  Chips use them for the
things that must not change after manufacture -- a serial number, a MAC
address, a secure boot key, a flag that permanently disables the debug port.

Enabled with ``CONFIG_EFUSE``.  The code is in ``drivers/efuse/``, and the
interface is in ``include/nuttx/efuse/efuse.h``.

Interface
=========

A chip port registers a device with

.. code-block:: c

   FAR void *efuse_register(FAR const char *path,
                            FAR struct efuse_lowerhalf_s *lower);

after which the fuses are read and written through ioctls on that path.  The
upper half is thin on purpose: what a fuse *means* is entirely chip
specific, so the driver maps field names to bit positions and does not try
to interpret them.

Handle with care
================

A fuse is one-time programmable: writing the wrong value is permanent, and
no reboot undoes it.  On many parts one of the available fuses disables the
debug interface, so a mistake there costs you the board, not just the boot.

Two consequences worth designing around:

* Read fuses freely; write them from as little code as possible, ideally
  from a dedicated provisioning program that is not part of the shipping
  firmware.
* Check what a field means in the chip's own documentation before writing
  it.  The NuttX driver will happily burn whatever it is told to.
