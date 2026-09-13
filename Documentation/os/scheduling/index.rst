==========
Scheduling
==========

NuttX decides which thread runs, and when.  This page describes that
decision: the states a thread moves through, the policies that order threads
of equal priority, and the interface an application uses to choose between
them.

The code lives under ``sched/``.

Priority comes first
====================

NuttX is a **strict priority** scheduler.  The thread that runs is always
the ready-to-run thread with the highest priority.  A lower-priority thread
runs only while no higher-priority thread is ready; the moment a
higher-priority one becomes ready, it takes the CPU.  NuttX is fully
pre-emptible, so that happens immediately, including from inside an
interrupt handler.

Priority alone does not say what happens when two ready threads share the
same priority.  That is what the scheduling policies decide, and it is the
only thing they decide.

Thread states
=============

Every thread is in exactly one state, held in its task control block.  The
states are defined by ``enum tstate_e`` in ``include/nuttx/sched.h`` and
fall into three groups:

::

   task_create()
        |
        v
   INACTIVE  --- task_activate() --->+
                                     |
   ready to run ---------------------+----------------------------
                                     |
        READYTORUN  --- highest priority --->  RUNNING
             ^                                    |
             +------------- pre-empted -----------+
        ASSIGNED     picked a CPU        (CONFIG_SMP only)
        PENDING      ready, but some thread holds sched_lock()

   ------------+--------------------------------+----------------
               |                                |
               | what it was waiting for        | waits for
               | happened                       | something
               |                                v
   blocked ----+---------------------------------------------------

        WAIT_SEM          a semaphore
        WAIT_SIG          a signal, or sleeping
        WAIT_EVENT        an event                 (CONFIG_SCHED_EVENTS)
        WAIT_MQNOTEMPTY   a message to arrive
        WAIT_MQNOTFULL    room in a message queue
        STOPPED           SIGCONT                  (CONFIG_SIG_SIGSTOP_ACTION)

A thread in any *ready-to-run* state is runnable; only one per CPU is
``RUNNING``.  A thread in any *blocked* state is waiting for something
specific, and the state says what: a semaphore, a signal, an event, room in
a message queue.  This is why a stack dump tells you not just that a thread
is stuck but what it is stuck on.

``ASSIGNED`` exists only under ``CONFIG_SMP``, and ``PENDING`` only matters
while some thread holds ``sched_lock()``: the thread is ready, and the
scheduler is not allowed to switch to it yet.

Scheduling policies
===================

The policy applies **between threads of equal priority**.  It never lets a
lower-priority thread run ahead of a higher-priority one.

``SCHED_FIFO`` -- run to completion
-----------------------------------

The default.  A thread runs until it blocks, exits, or is pre-empted by
something of higher priority.  Two threads of the same priority do not share
the CPU: the first one to start keeps it until it gives it up.

This is the most predictable policy and the cheapest one, which is why it is
the default in a real-time system.

``SCHED_RR`` -- take turns
--------------------------

Same as ``SCHED_FIFO``, except that a thread which has been running for
``CONFIG_RR_INTERVAL`` milliseconds is moved to the back of the queue of
threads at its own priority, and the next one runs.

Round robin is enabled by setting ``CONFIG_RR_INTERVAL`` to a positive
value; setting it to 0 disables the policy entirely.  Use it when several
threads of the same priority have to make progress together, and none of
them blocks often enough to give the others a chance on its own.

``SCHED_SPORADIC`` -- a budget per period
-----------------------------------------

Enabled by ``CONFIG_SCHED_SPORADIC``.  This one is worth understanding
before reaching for it, because it behaves unlike the other two.

A sporadic thread has **two** priorities and a **budget**:

.. list-table::
   :header-rows: 1
   :widths: 34 66

   * - ``struct sched_param`` field
     - Meaning
   * - ``sched_priority``
     - The high priority.  The thread runs at this priority while it still
       has budget left.
   * - ``sched_ss_low_priority``
     - The low priority.  The thread drops to this once the budget is spent.
   * - ``sched_ss_init_budget``
     - How much CPU time the thread may spend at the high priority.
   * - ``sched_ss_repl_period``
     - How often the budget is given back.
   * - ``sched_ss_max_repl``
     - How many replenishments may be pending at once
       (``CONFIG_SCHED_SPORADIC_MAXREPL``).

While the thread has budget it competes at ``sched_priority``.  When the
budget runs out it is demoted to ``sched_ss_low_priority``, so it keeps
running only if nothing else wants the CPU.  One replenishment period after
the time was consumed, that much budget comes back and the thread is
promoted again.

What this buys you is a **bounded** amount of high-priority CPU time for a
thread whose workload you do not fully trust: an event handler that is
usually short but occasionally is not.  It gets to respond quickly, and it
cannot starve the rest of the system if it misbehaves.  A thread that would
otherwise have to be given a low priority -- and therefore a poor response
time -- can be given a high one safely.

Choosing a policy
=================

.. list-table::
   :header-rows: 1
   :widths: 22 78

   * - Policy
     - Use it when
   * - ``SCHED_FIFO``
     - The normal case.  Threads are ordered by priority and each runs until
       it blocks.
   * - ``SCHED_RR``
     - Several threads sit at the same priority and all have to progress,
       for example a set of equivalent workers.
   * - ``SCHED_SPORADIC``
     - A thread needs a fast response but its running time is not bounded,
       and starving lower-priority work is not acceptable.

``SCHED_OTHER`` and ``SCHED_NORMAL`` are aliases that map to ``SCHED_FIFO``
or ``SCHED_RR`` depending on the configuration; they exist for portability.

Application interface
=====================

The POSIX interface to all of the above -- ``sched_setscheduler()``,
``sched_setparam()``, ``sched_yield()``, ``sched_rr_get_interval()`` and the
rest -- is documented in :doc:`/reference/user/02_task_scheduling`.

Two interfaces are specific to NuttX and worth naming here:

``sched_lock()`` / ``sched_unlock()``
   Hold off the scheduler without disabling interrupts.  Interrupts still
   run; what is suspended is the switch to another thread.  A thread that
   becomes ready while pre-emption is locked goes to ``PENDING``.  This is
   cheaper and far less disruptive than disabling interrupts, and it is
   almost always the right tool when the goal is "do not switch away from
   me" rather than "do not interrupt me".  See
   :doc:`preemption_latency` for what each choice costs.

``sched_setaffinity()`` / ``sched_getaffinity()``
   Restrict a thread to a set of CPUs under ``CONFIG_SMP``.  See
   :doc:`smp`.

In this section
===============

.. toctree::
   :maxdepth: 1

   nuttx_tasking.rst
   tasks_vs_threads.rst
   kernel_threads_vs_pthreads.rst
   processes_vs_tasks.rst
   context_switches.rst
   preemption_latency.rst
   cancellation_points.rst
   smp.rst
   wqueue.rst
   tls.rst
   user_identity.rst
