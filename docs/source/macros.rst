Macros
======

Here we present the list of macros available in the ``marta_wrapper.h`` header
file:

.. list-table::
   :header-rows: 1

   * - Macro
     - Description
   * - ``MARTA_BENCHMARK_BEGIN``
     - Init the source code.
   * - ``MARTA_BENCHMARK_END``
     - Indicates the end of the benchmark.
   * - ``MARTA_FLUSH_CACHE``
     - Flushes the last-level cache.
   * - ``PROFILE_FUNCTION(f)``
     - Instrument a concrete function ``f``.
   * - ``CLOBBER_MEM``
     - Acts as a memory barrier.
   * - ``DO_NOT_TOUCH(x)``
     - Avoid dead-code elimination for a concrete variable ``x``.
