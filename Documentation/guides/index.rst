======
Guides
======

Task-shaped documentation: how to do a particular thing, as opposed to
how a subsystem works, which is in :doc:`/os/index`.

Building
========

Getting NuttX and your application to compile, including keeping your code outside the NuttX tree and using other language runtimes.

.. toctree::
   :maxdepth: 1

   build/building_nuttx_with_app_out_of_src_tree.rst
   build/building_uclibcpp.rst
   build/cpp_cmake.rst
   build/custom_app_directories.rst
   build/customapps.rst
   build/integrate_newlib.rst
   build/nix_flake.rst
   build/platform_directories.rst

Porting to New Hardware
=======================

Bringing NuttX up on a board or chip it has not run on before.

.. toctree::
   :maxdepth: 1

   porting/customboards.rst
   porting/include_files_board_h.rst
   porting/port.rst
   porting/port_bootsequence.rst
   porting/port_relatedkernelconfigrations.rst
   porting/specialstuff_in_nuttxheaderfiles.rst

Drivers and Devices
===================

Writing a driver, describing hardware to one, and watching what it does.

.. toctree::
   :maxdepth: 1

   drivers/devicetree.rst
   drivers/drivers.rst
   drivers/logging_rambuffer.rst
   drivers/lwl.rst
   drivers/ofloader.rst
   drivers/reading_can_msgs.rst
   drivers/rndis.rst
   drivers/usbtrace.rst

Threads and Interrupts
======================

Working with threads, interrupt handlers and the things that pass between them.

.. toctree::
   :maxdepth: 1

   concurrency/fork_vfork_migration.rst
   concurrency/kernel_threads_with_custom_stacks.rst
   concurrency/nestedinterrupts.rst
   concurrency/signal_events_interrupt_handlers.rst
   concurrency/signaling_sem_priority_inheritance.rst
   concurrency/thread_local_storage.rst
   concurrency/usingkernelthreads.rst
   concurrency/versioning_and_task_names.rst
   concurrency/zerolatencyinterrupts.rst

Running Programs
================

Loading programs at runtime rather than linking them into the image.

.. toctree::
   :maxdepth: 1

   programs/fully_linked_elf.rst
   programs/partially_linked_elf.rst
   programs/protected_build.rst
   programs/updating_release_system_elf.rst

Files and Storage
=================

Giving the system somewhere to read and write.

.. toctree::
   :maxdepth: 1

   filesystem/automounter.rst
   filesystem/etcromfs.rst
   filesystem/ram_rom_disks.rst

Networking
==========

Configuring, using and testing the network stack.

.. toctree::
   :maxdepth: 1

   networking/ipv6.rst
   networking/nfs.rst
   networking/nsh_network_link_management.rst
   networking/testingtcpip.rst

The Shell
=========

Working with NSH.

.. toctree::
   :maxdepth: 1

   nsh/multiple_nsh_sessions.rst
   nsh/remove_device_drivers_nsh.rst

Running Without Hardware
========================

The simulator and the emulators, for developing before a board exists.

.. toctree::
   :maxdepth: 1

   simulation/qemu_tips.rst
   simulation/renode.rst
   simulation/simulator.rst

Security
========

Hardening a build, and talking to a trusted execution environment.

.. toctree::
   :maxdepth: 1

   security/fortify.rst
   security/optee.rst

Other Languages
===============

Using NuttX from something other than C.

.. toctree::
   :maxdepth: 1

   languages/pysimcoder.rst
   languages/rust.rst

Chip-Specific Notes
===================

Guides that apply to one part or one core rather than to NuttX in general.  These are here because they have nowhere better yet; over time they belong under :doc:`/platforms/index` with the chip they describe.

.. toctree::
   :maxdepth: 1

   chip-specific/armv7m_runtimestackcheck.rst
   chip-specific/changing_systemclockconfig.rst
   chip-specific/port_drivers_to_stm32f7.rst
   chip-specific/semihosting.rst
   chip-specific/smaller_vector_tables.rst
   chip-specific/stm32_ports.rst
   chip-specific/stm32ccm.rst
   chip-specific/stm32nullpointer.rst
