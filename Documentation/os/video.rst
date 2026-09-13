===============
Video Subsystem
===============

Everything to do with moving images: cameras that produce frames, frame
buffers that display them, and the interfaces in between.

Where the code is
=================

Unlike most sections of this documentation, "video" is not one directory.
``video/`` at the top of the source tree holds only the Kconfig entry that
switches the subsystem on (``CONFIG_VIDEO``); the working code lives in
``drivers/video/``, and the interfaces every part of it agrees on are in
``include/nuttx/video/``.

The interfaces
==============

.. list-table::
   :header-rows: 1
   :widths: 30 70

   * - Header
     - What it defines
   * - ``v4l2_cap.h``, ``v4l2_m2m.h``
     - The V4L2 interface: capture, and memory-to-memory transforms.  This
       is the Linux API, which means an application that already speaks V4L2
       needs little changing.
   * - ``imgsensor.h``, ``imgdata.h``
     - The two halves a camera port implements: the sensor being configured,
       and the path the pixels take out of it.
   * - ``fb.h``
     - The frame buffer interface, for the display side.
   * - ``mipi_dsi.h``, ``mipi_display.h``
     - MIPI DSI, for displays attached over that link.
   * - ``videomode.h``, ``edid.h``, ``vesagtf.h``
     - Timings and mode descriptions, including reading a mode out of a
       monitor's EDID.
   * - ``rfb.h``, ``vnc.h``
     - The remote frame buffer protocol, for a display that is somewhere
       else entirely.

Drivers
=======

The device drivers themselves -- the sensors, the frame buffers, the
display controllers -- are documented with the rest of the drivers:

* :doc:`/os/drivers/special/video` for video device drivers;
* :doc:`/os/graphics/index` for what draws into a frame buffer once it
  exists.
