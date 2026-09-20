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
       acceptable.  A mutex records its holder, which is what priority
       inheritance needs in order to boost the right thread.  NuttX tracks
       holders for plain semaphores too, so ``CONFIG_PRIORITY_INHERITANCE``
       covers both.  See :doc:`/os/ipc/mutex`.
   * - Spinlock
     - Protecting something so short that sleeping would cost more than
       spinning, and where the holder genuinely cannot sleep -- inside an
       interrupt handler, for instance.  Needs ``CONFIG_SPINLOCK``, which
       ``CONFIG_SMP`` selects.  ``include/nuttx/spinlock.h``
   * - Reader/writer semaphore
     - Many readers, few writers, and the read side is long enough that
       serialising it would hurt.  ``include/nuttx/rwsem.h``
   * - Sequence lock
     - Readers must never block writers.  A reader takes a snapshot and
       checks afterwards whether a writer interfered; if so, it reads again.
       ``include/nuttx/seqlock.h``

The one worth reading twice is the spinlock, because its two variants
degrade in opposite directions when ``CONFIG_SPINLOCK`` is off.
``spin_lock()`` is then a macro that expands to nothing, so code written
against it is left with no protection at all.  ``spin_lock_irqsave()``
becomes ``up_irq_save()``, so it still shuts out interrupts on the one CPU
there is.  The second survives the build choice; the first does not.

Turning ``CONFIG_SPINLOCK`` on in a single-CPU build is worse than either:
the loop is real and no second CPU is running to end it.  The Kconfig help
says so outright -- *"Use in a single CPU configuration would most likely
be fatal."*  A spinlock is an SMP tool, not a portable stand-in for
``sched_lock()``.  See :doc:`/os/interrupts/critical_sections` for what
that choice costs.

.. toctree::
   :maxdepth: 2
   :caption: Contents:

   seqcount/index.rst
