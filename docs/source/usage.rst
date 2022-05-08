Usage
=====

After installing the toolkit, there will be two executables available in the
system: ``marta_profiler`` and ``marta_analyzer``, for the `profiler` and
`analyzer` components respectively. CLI options and their usage are described
below.

Profiler
--------

``marta_profiler --help`` will display: 

.. code-block::

    subcommands:
        {project,po,profile,perf}
        
            project (po)        project help
            profile (perf)      profile help

The ``project`` command allow us to generate project and benchmark templates:
the directory, the source code and the configuration file.

..  code-block::

    usage: marta_profiler project [-h] [-n NAME] [-u] [-c CHECK_CONFIG_FILE] [-dump]

    project subcommand is meant to help with the configuration and generation of new projects MARTA-compliant.

    optional arguments:
        -h, --help            show this help message and exit
        -n NAME, --name NAME  name of the new project
        -u, --microbenchmark  set new project as micro-benchmark
        -c CHECK_CONFIG_FILE, --check-config-file CHECK_CONFIG_FILE
                                quit if there is an error checking the configuration file
        -dump, --dump-config-file
                                dump a sample configuration file with all needed files for profiler to work properly

The ``profiler`` command is meant for instrumenting applications based on a
configuration file:

.. code-block:: 

    usage: marta_profiler profile [-h] [-o OUTPUT] [-r] [-d] [-log {debug,info,warning,error,critical}] [-nsteps ITERATIONS] [-nexec EXECUTIONS] [-x]
                              [-q] [-v] [-s SUMMARY [SUMMARY ...]]
                              input

    MARTA requires an input file with the configuration parameters, but some of them can be overwritten at runtime, as described below.

    optional arguments:
    -h, --help            show this help message and exit

    required named arguments:
    input                 input configuration file

    optional named arguments:
    -o OUTPUT, --output OUTPUT
                            output results file name
    -r, --report          output report file name, with data regarding the machine, compilation flags, warnings, and errors
    -d, --debug           debug verbose
    -log {debug,info,warning,error,critical}, --loglevel {debug,info,warning,error,critical}
                            log level
    -nsteps ITERATIONS, --iterations ITERATIONS
                            number of iterations
    -nexec EXECUTIONS, --executions EXECUTIONS
                            number of executions
    -x, --no-quit-on-error
                            quit if there is an error during compilation or execution of the kernel
    -q, --quiet           quiet execution
    -v, --version         display version and quit
    -s SUMMARY [SUMMARY ...], --summary SUMMARY [SUMMARY ...]
                            print a summary at the end with the given dimensions of interest

Analyzer
--------

``marta_analyzer --help`` will display: 

.. code-block:: 

    usage: marta_analyzer [-h] [-q] [-v] [-dump] [input]

    wrapper for analyzing data given a csv

    optional arguments:
    -h, --help            show this help message and exit

    required named arguments:
    input                 input configuration file

    optional named arguments:
    -q, --quiet           quiet execution
    -v, --version         display version and quit
    -dump, --dump-config-file
                            dump a sample configuration file with all needed files for analyzer to work properly