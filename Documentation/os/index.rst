=========
OS Design
=========

How NuttX is built, subsystem by subsystem.  The sections follow the source
tree: what lives under ``sched/`` is described in :doc:`scheduling/index`,
what lives under ``fs/`` in :doc:`filesystem/index`, under ``drivers/`` in
:doc:`drivers/index`, and so on.  Each subsystem is described once, going
from what it is, to how it works, to the interfaces it offers.

For the POSIX interface an application sees, go to
:doc:`/reference/user/index` instead.  That is a different question -- what
you may call -- and it has its own section.

The kernel
==========

.. toctree::
   :maxdepth: 1

   scheduling/index.rst
   ipc/index.rst
   time/index.rst
   interrupts/index.rst
   memory/index.rst

Storage and I/O
===============

.. toctree::
   :maxdepth: 1

   filesystem/index.rst
   drivers/index.rst
   networking/index.rst

Running programs
================

.. toctree::
   :maxdepth: 1

   binfmt/index.rst
   syscall.rst
   libs/index.rst

Media and security
==================

.. toctree::
   :maxdepth: 1

   graphics/index.rst
   audio/index.rst
   video.rst
   crypto.rst
   wireless.rst

Portability
===========

.. toctree::
   :maxdepth: 1

   arch/index.rst
   openamp.rst
   concurrency/index.rst

Reference
=========

.. toctree::
   :maxdepth: 1

   nuttx.rst
   app_vs_os.rst
   conventions.rst
   notifier.rst
