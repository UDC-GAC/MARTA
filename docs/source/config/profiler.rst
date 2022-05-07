Profiler configuration
======================


The configuration file for the profiler is structured in a YAML file.
Parameters available for the **profiler** kernel dictionary:

.. list-table::
   :header-rows: 1

   * - Parameter
     - Description
     - Type
     - Default
   * - ``name``
     - Name of the kernel or program.
     - ``str``
     - -
   * - ``path``
     - Folder containing the sources.
     - ``str``
     - -
   * - ``preamble``
     - Commands to execute before compilation. Tuning CPUs, allocating huge pages, etc.
     - ``str``
     - ``''``
   * - ``finalize``
     - Tasks to execute after the experiments.
     - ``dict``
     - -
   * - ``configuration``
     - Cartesian product of the list of parameters. This includes the list Makefile options, ``-D`` definitions, etc.
     - ``dict``
     - -
   * - ``compilation``
     - Compiler configurations (\ ``compiler`` table).
     - ``dict``
     - -
   * - ``execution``
     - Execution parameters (\ ``execution`` table).
     - ``dict``
     - -
   * - ``output``
     - Output options, such as name and format (\ ``output`` table).
     - ``dict``
     - -


``finalize`` parameters:

.. list-table::
   :header-rows: 1

   * - Parameter
     - Description
     - Type
     - Default
   * - ``clean_tmp_files``
     - Clean temporal files.
     - ``bool``
     - ``True``
   * - ``clean_asm_files``
     - Clean assembly files generated.
     - ``bool``
     - ``True``
   * - ``clean_asm_files``
     - Clean binary files.
     - ``bool``
     - ``False``
   * - ``command``
     - Execute a command after the execution of the set of experiments.
     - ``str``
     - ``''``


``configuration`` parameters:

.. list-table::
   :header-rows: 1

   * - Parameter
     - Description
     - Type
     - Default
   * - ``kernel_cfg``
     - Options to Makefile.
     - ``str list``
     - [``''``]
   * - ``d_features``
     - \texttt{-D} flags. Each of them can be described as in table ``d_features``.
     - ``dict``
     - -
   * - ``flops``
     - Expression for computing FLOPS count. This can be expressed dynamically using ``d_features`` values.
     - ``str``
     - -


``compiler`` parameters:

.. list-table::
   :header-rows: 1

   * - Parameter
     - Description
     - Type
     - Default
   * - ``enabled``
     - Enable/disable compilation. Useful for pre-generated binaries.
     - ``bool``
     - ``True``
   * - ``processes``
     - Number of processes to use for compilation.
     - ``int``
     - 1
   * - ``compiler_flags``
     - Dictionary of compilers with a list of specific flags each.
     - ``dict of lists``
     - -
   * - ``main_src``
     - Main source file to be compiled
     - ``str``
     - ``main.c``
   * - ``kernel_inlined``
     - If kernel not inlined, then it need to be compiled from a different source.
     - ``bool``
     - ``False``
   * - ``loop_type``
     - "asm" or "C". Determines the language for MARTA instrumentation insertion.
     - ``str``
     - "asm"
   * - ``asm_analysis``
     - `syntax`: ASM syntax, `count_ins`: count the number and type of ASM instructions in the region of interest, ``static_analysis``\ : perform code analysis using LLVM-MCA
     - ``dict``
     - {}


``d_features`` parameters:

.. list-table::
   :header-rows: 1

   * - Parameter
     - Description
     - Type
     - Default
   * - ``type``
     - Type of expression: static, dynamic. static for ``list`` arguments, ``dynamic`` for iterators, e.g. itertools.
     - ``str``
     - ``''``
   * - ``val_type``
     - Value of the expression: "numeric", "string".
     - ``str``
     - "numeric"
   * - ``value``
     - Expression generating the list of values, e.g. ``[0,1,2,3]``\ , ``itertools.product([0,1], [10,20])``\ , etc.
     - ``Object``
     - -


``execution`` parameters:

.. list-table::
   :header-rows: 1

   * - Parameter
     - Description
     - Type
     - Default
   * - ``enabled``
     - Enable execution
     - ``bool``
     - ``True``
   * - ``papi_counter``
     - List of PAPI counters to read.
     - ``str list``
     - -
   * - ``time``
     - Measure execution time with ``gettimeofday``.
     - ``bool``
     - ``False``
   * - ``tsc``
     - Measure TSC cycles using ``rdtsc``.
     - ``bool``
     - ``False``
   * - ``nexec``
     - Repetitions per each configuration.
     - ``int``
     - 7
   * - ``threshold_outliers``
     - Threshold for outlier detection.
     - ``int``
     - .1
   * - ``mean_and_discard``
     - Compute average values after discarding outliers.
     - ``bool``
     - ``False``
   * - ``nsteps``
     - Number of iterations of the loop containing the ROI if specified.
     - ``int``
     - 1
   * - ``intel_turbo``
     - Enable or disable turbo boost on Intel processors via MSR.
     - ``bool``
     - ``False``
   * - ``max_freq``
     - Set maximum CPU frequency via MSR.
     - ``bool``
     - ``False``
   * - ``cpu_affinity``
     - Logical CPU ID for pinning single-thread measurements.
     - ``int``
     - 0
   * - ``cache_flush``
     - Cache flush enabled for architectures supporting ``CLFSH``.
     - ``bool``
     - ``False``


``output`` parameters:

.. list-table::
   :header-rows: 1

   * - Parameter
     - Description
     - Type
     - Default
   * - ``name``
     - Name of output file.
     - ``str``
     - -
   * - ``columns``
     - Output columns. If "all", then all dimensions used in the configuration: compiler, d_features, kernel_config, papi_counters, etc.
     - ``str``
     - -
   * - ``report``
     - Generate a log file with all information related to the experiment: host machine, elapsed time, standard output, standard error, etc.
     - ``bool``
     - -