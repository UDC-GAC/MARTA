* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
*                                  MARPLOT                                    *
*              Micro ARchitectural Profiler for LOop-based Tensors            *
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *

Copyright (c) 2019-2020 the Colorado State Univesity.

Contact:
    Marcos Horro Varela <marcos.horro@udc.es> (mantainer)
    Louis-Noël Pouchet <pouchet@colostate.edu>

Machine characterization is a tedious task that can require a lot of profiling
by executing many programs or kernels and analyzing their performance. This
tool has been created to automate this task.

This part of MARPLOT is meant for:

* Compiling kernels with different configurations, regarding: loop stride,
  datasizes, etc.
* Execute and time those kernels. There is also the possibility of measuring
  hardware counters using PAPI/C interface.
* Create a CSV/pandas (python) DataFrame with all the configurations and results
  obtained in the execution.


