===========
Concurrency
===========

The primitives that keep data consistent when more than one thread -- or
more than one CPU -- touches it.  They are lower level than the things in
:doc:`/os/ipc/index`: those are for threads that want to *communicate*,
these are for threads that merely want not to corrupt each other.

Choosing one
============

.. list-table::
   :header-rows: 1
   :widths: 26 74

   * - Primitive
     - Use it when
   * - Atomic operations
     - The shared data is one word and the operation is a single read,
       write, add or compare-and-swap.  No lock is involved, so none can be
       held too long.  ``include/nuttx/atomic.h``
   * - Mutex
     - A thread may need to wait, and holding the lock while blocked is
       acceptable.  A mutex has an owner, which is what makes priority
       inheritance possible.  See :doc:`/os/ipc/mutex`.
   * - Spinlock
     - Under ``CONFIG_SMP``, protecting something so short that sleeping
       would cost more than spinning -- and where the holder genuinely
       cannot sleep, such as inside an interrupt handler.
       ``include/nuttx/spinlock.h``
   * - Reader/writer semaphore
     - Many readers, few writers, and the read side is long enough that
       serialising it would hurt.  ``include/nuttx/rwsem.h``
   * - Sequence lock
     - Readers must never block writers.  A reader takes a snapshot and
       checks afterwards whether a writer interfered; if so, it reads again.
       ``include/nuttx/seqlock.h``

The one that surprises people is the spinlock.  On a single-CPU build there
is nobody to spin against, so a spinlock degenerates into disabling
pre-emption -- which means using one on a uniprocessor system is a way of
writing ``sched_lock()`` that will behave differently the day the code is
built for SMP.  See :doc:`/os/interrupts/critical_sections` for what that
choice costs.

.. toctree::
   :maxdepth: 2
   :caption: Contents:

   seqcount/index.rst
