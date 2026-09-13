==========================
Inter-Thread Communication
==========================

How threads wait for each other and pass data.  The code lives under
``sched/``: ``sched/mqueue/`` for message queues, ``sched/semaphore/`` for
semaphores and mutexes, ``sched/signal/`` for signals and
``sched/event/`` for events.

Which one to reach for:

.. list-table::
   :header-rows: 1
   :widths: 24 76

   * - Mechanism
     - Use it when
   * - Semaphore
     - Counting something: a resource with N instances, or one thread
       telling another that work is ready.
   * - Mutex
     - Protecting data.  Unlike a semaphore it has an owner, which is what
       lets priority inheritance work.
   * - Message queue
     - Passing data, not just a signal, and the sender should not block on a
       slow receiver.
   * - Signal
     - Interrupting a thread that is doing something else, or reacting to an
       asynchronous event.
   * - Event
     - Waiting on a combination of conditions rather than a single one.

.. toctree::
   :maxdepth: 1

   mutex.rst
   events.rst
   signal_handlers.rst
