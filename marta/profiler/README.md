# MARTA - Profiler

Machine characterization is a tedious task that can require a lot of profiling
by executing many programs or kernels and analyzing their performance. This
tool has been created to automate this task.

This module of MARTA toolkit is meant for:

- Compiling kernels with different configurations, regarding: loop stride,
  datasizes, etc.
- Execute and time those kernels. There is also the possibility of measuring
  hardware counters using PAPI/C interface.
- Create a CSV file with all the configurations and results obtained from the execution.

## Requirements

Need to have Python 3 (no, there is no Python 2 version nor will be one).
Profiler works with a configuration file in YAML format. Therefore:

```
chmod +x profiler
./profiler.py -i file.yml
```

## Kernel structure

In order to operate properly with MARTA's profiler, kernels should follow the
following structure, in order to guarantee an automated compilation, execution
and gathering process.
