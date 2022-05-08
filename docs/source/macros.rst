Macros
======

Here we present the list of macros available in the ``marta_wrapper.h`` header
file:

.. list-table::
   :header-rows: 1

   * - Macro
     - Description
   * - ``MARTA_BENCHMARK_BEGIN``
     - Sets benchmark's start. It also sets CPU affinity for the execution using Linux system calls.
   * - ``MARTA_BENCHMARK_END``
     - Sets the end of the main function in the program.
   * - ``MARTA_FLUSH_CACHE``
     - Performs ``clflush`` of size ``s`` at memory address ``p``. Flush is performed at cache line level, typically 64 bytes.
   * - ``PROFILE_FUNCTION(f)``
     - Instruments function ``f`` in a loop with ``TSTEPS`` iterations without
       performing any loop optimization. This is useful for collecting stable
       measurements, even though it provokes the hot cache effect for small
       functions without saturating memory caches. It avoids the loop if
       ``TSTEPS`` is not greater than 1.
   * - ``CLOBBER_MEM``
     - Acts as a read/write barrier. Useful for micro-benchmarking, avoiding the reuse of values in register bringing values from memory.
   * - ``DO_NOT_TOUCH(x)``
     - Useful for avoiding any compiler optimization over variable ``x`` materialized in a register.
