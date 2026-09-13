==========
Interrupts
==========

How NuttX takes an interrupt, what an interrupt handler may and may not do,
and how code protects itself from one.  The code lives in ``sched/irq/``,
with the vector table and the entry sequence in
``arch/<arch>/src/``.

An interrupt handler in NuttX runs with interrupts disabled and cannot
block.  That is the whole reason the rest of this section exists: anything
that has to wait, allocate or take a lock has to be handed off, which is
what :doc:`bottom halves <bottomhalf_interrupt>` and the work queues are
for.

For protecting a section of code, note that disabling interrupts and
locking pre-emption are not the same choice and do not cost the same.  See
:doc:`critical_sections` for the difference, and
:doc:`/os/scheduling/preemption_latency` for what each one does to response
time.

.. toctree::
   :maxdepth: 1

   interrupt_controls.rst
   critical_sections.rst
   bottomhalf_interrupt.rst
