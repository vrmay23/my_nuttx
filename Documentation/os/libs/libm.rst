=================
Math library
=================

Which implementation of ``<math.h>`` gets linked in.  NuttX does not provide
one by default, and the choice matters more than it looks: floating point
code pulls in a surprising amount of object code, and these implementations
trade size against accuracy and speed differently.

The configuration lives in ``libs/libm/``.

The choices
===========

.. list-table::
   :header-rows: 1
   :widths: 26 74

   * - Option
     - What it selects
   * - ``CONFIG_LIBM``
     - The implementation that ships with NuttX.  Available when the
       architecture does not provide its own ``math.h``.
   * - ``CONFIG_LIBM_NEWLIB``
     - Newlib's math library.
   * - ``CONFIG_LIBM_LIBMCS``
     - LibmCS, written for safety-critical use.
   * - ``CONFIG_LIBM_OPENLIBM``
     - OpenLibm.
   * - ``CONFIG_LIBM_TOOLCHAIN``
     - Whatever the toolchain already ships.  Nothing is built; the
       toolchain's own library is linked.
   * - ``CONFIG_LIBM_NONE``
     - No math library at all.  Code that calls ``sin()`` will fail to link,
       which is the point: on a system that should not be doing floating
       point, this makes it impossible rather than merely unwise.

Choosing
========

``CONFIG_LIBM_TOOLCHAIN`` is the least surprising choice when the toolchain
has a usable library, since nothing is compiled and nothing can disagree
about representations.  ``CONFIG_LIBM`` is the portable fallback.  The other
three are there because a project may already have made this decision for
reasons of certification, licence or accuracy, and NuttX should not force a
second one.
