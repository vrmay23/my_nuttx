================
Time and Timers
================

The system clock, the timers built on it, and what happens when a delay is
shorter than a clock tick.  The code lives in ``sched/clock/``,
``sched/timer/``, ``sched/wdog/`` and ``sched/hrtimer/``.

Two decisions shape everything on this page.  The first is whether the
system runs on a periodic tick or :doc:`tickless <tickless_os>`: tickless
trades a little complexity for the ability to sleep between events instead
of waking on every tick.  The second is the tick rate itself, which sets the
resolution of every delay that is not tickless -- and the reason
:doc:`short delays <short_time_delays>` need their own treatment.

.. toctree::
   :maxdepth: 1

   time_clock.rst
   tickless_os.rst
   short_time_delays.rst
   oneshot_timers_and_cpu_load.rst
   sleep.rst
