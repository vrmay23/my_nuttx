===================
Device Tree support
===================

A device tree describes the hardware of a board as data -- what peripherals
exist, at which addresses, on which interrupts -- instead of as code.  The
same kernel image can then boot on several boards, reading the differences
at runtime rather than being compiled for one of them.

Enabled with ``CONFIG_DEVICE_TREE``, which selects ``CONFIG_LIBC_FDT``.  The
code is in ``drivers/devicetree/``.

Where NuttX uses it
===================

NuttX is not a device-tree-first system the way Linux is.  Most ports
describe their hardware in the board directory and in ``Kconfig``, which is
smaller and needs no parsing at boot.  Device tree is used where the
hardware genuinely is not known until run time:

.. list-table::
   :header-rows: 1
   :widths: 28 72

   * - Source file
     - What it reads out of the tree
   * - ``fdt.c``
     - The tree itself: finding nodes and reading properties.
   * - ``fdt_pci.c``
     - PCI host bridges and their address windows.
   * - ``fdt_virtio_mmio.c``
     - Virtio devices, which is how a virtual machine tells the guest what
       it has.
   * - ``fdt_cfi.c``
     - CFI flash, whose geometry the tree can describe.

The pattern is the same in each: a platform where the *set* of devices is
decided by something outside the firmware -- a hypervisor, a bootloader, a
board with sockets -- and where compiling the answer in would be wrong.

Getting one
===========

The bootloader normally passes the address of the tree to the kernel; on
QEMU and similar platforms it is generated for you from the command line
options. :doc:`/guides/drivers/devicetree` covers using one in practice.
