===============
OpenAMP Support
===============

Asymmetric Multi Processing support in NuttX is implemented via the
`OpenAMP <https://www.openampproject.org/>`_ framework.

Asymmetric, as opposed to :doc:`SMP </os/scheduling/smp>`, means the cores
are not interchangeable and are not running one operating system between
them.  A typical part has a Cortex-A running Linux and a Cortex-M running
NuttX, each with its own memory and its own idea of what it is doing.  They
still have to talk, and OpenAMP is the agreement about how.

What NuttX provides
===================

OpenAMP itself is imported rather than written here; ``openamp/`` at the top
of the source tree holds the patches NuttX carries against it.  What NuttX
adds is the layer underneath and the users above:

:doc:`RPTUN </os/drivers/special/rptun/index>`
   The transport.  It owns the shared memory, the interrupts each side uses
   to poke the other, and the resource table that describes the arrangement.
   Porting AMP to a new part is mostly writing an RPTUN driver.

:doc:`RPMSG </os/drivers/special/rpmsg/index>`
   The messaging on top of it: named channels, so a service on one core can
   be found and spoken to from the other.

Almost everything else is built on RPMSG rather than on OpenAMP directly.
That is why the same idea keeps appearing across this documentation --
``rpmsgfs`` for a file system on the far side, ``CONFIG_CLK_RPMSG`` for
clocks owned by the other core, usrsock over RPMSG for a network stack that
lives elsewhere.  Each is the same pattern: the resource is on one core, the
caller is on the other, and RPMSG carries the request.
