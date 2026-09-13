============================
User-space sockets (usrsock)
============================

Usually a call to ``socket()`` ends up in the NuttX network stack.  Usrsock
redirects it instead to a daemon running as an ordinary task, which answers
the call however it likes.

The code is in ``drivers/usrsock/``.

What it is for
==============

The case it exists for is a modem or a Wi-Fi module that runs its own TCP/IP
stack and is spoken to over AT commands or a vendor protocol.  There is no
Ethernet frame to hand to the NuttX stack, and no point in having two
stacks.  With usrsock the application still calls ``socket()``, ``connect()``
and ``send()``, and a daemon translates each one into whatever the module
expects.

The application does not have to know.  That is the whole point: the same
program runs over a NuttX-stack Ethernet interface and over a modem, because
what changed is below the socket API.

How the request reaches the daemon
==================================

The kernel side turns each socket call into a request, and the daemon
answers it.  How the request travels is a configuration choice:

``CONFIG_NET_USRSOCK_DEVICE``
   Exports ``/dev/usrsock``.  The daemon opens that device, reads requests
   and writes responses.  This is the usual arrangement when the daemon runs
   on the same processor.

``CONFIG_NET_USRSOCK_RPMSG``
   Sends requests over an RPMSG channel instead, for a system where the
   stack lives on another processor.

``CONFIG_NET_USRSOCK_CUSTOM``
   Neither of the above: the board provides its own transport.

What it costs
=============

Every socket operation now crosses into another task and back.  For a modem
talking at serial speeds that is irrelevant -- the link is the bottleneck by
orders of magnitude.  For anything fast it is not, and the local stack is
the better answer.
