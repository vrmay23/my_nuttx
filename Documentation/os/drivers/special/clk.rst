========================
Clock management (CLK)
========================

Most SoCs do not have one clock.  They have a tree: an oscillator feeding
PLLs, PLLs feeding dividers and multiplexers, and gates at the leaves that
turn the clock to each peripheral on and off.  The CLK subsystem models that
tree so a driver can say "I need my clock running" without knowing which
PLL it came from.

The code is in ``drivers/clk/``.

Why a driver needs it
=====================

Two things a peripheral driver cannot do for itself:

* **Turn its own clock on.**  A gated peripheral does not answer register
  reads at all, which is a confusing way to discover the clock is off.
* **Know its own frequency.**  A UART computing a baud rate divisor, or a
  timer computing a tick, needs the frequency it is actually being fed --
  and that changes when a PLL upstream is reconfigured.

The clock tree
==============

Each node is one of a small set of element types, and a board or chip port
builds the tree out of them:

.. list-table::
   :header-rows: 1
   :widths: 30 70

   * - Element
     - What it does
   * - ``clk_fixed_rate``
     - A source of a known, unchanging frequency.  A crystal.
   * - ``clk_fixed_factor``
     - Multiplies and divides by constants.
   * - ``clk_divider``
     - A programmable divider.
   * - ``clk_multiplier``
     - A programmable multiplier.
   * - ``clk_fractional_divider``
     - A divider with a fractional part, for rates a whole divider cannot
       reach.
   * - ``clk_mux``
     - Selects one of several parents.
   * - ``clk_gate``
     - Turns a branch on and off.
   * - ``clk_phase``
     - Adjusts phase, for interfaces that need it.

Because the parent of each node is known, asking a leaf for its rate walks
up the tree, and enabling a leaf enables everything above it that was off.

Across processors
=================

``CONFIG_CLK_RPMSG`` adds a proxy pair, so a processor that does not own the
clock hardware can still ask for a rate.  The request travels over RPMSG to
the processor that does.  This is how an asymmetric system -- one core
running Linux and holding the clock controller, another running NuttX --
keeps a single view of the tree.
