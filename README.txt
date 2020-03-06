* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
*                                  MARPHIL                                    *
*              Micro ARchitectural Profiler for HPC Integer Loops             *
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *

Copyright (c) 2019-2020 the Colorado State Univesity.

Contact:
    Marcos Horro Varela <marcos.horro@udc.es> (mantainer)
    Louis-Noël Pouchet <pouchet@colostate.edu>

MARPHIL is a framework for reverse-engineering features of the
architecture. Some information regarding a concrete architecture may not be
fully disclosed by the manufacturer.

For this reason, we designed a tool which is able to extract information by
executing mini-kernels with different configurations in order to determine on
which conditions the performance varies. E.g. if a kernel with the same number
of floating point operations (FLOPs) for two different configurations (e.g.
two different strides, same compilation flags) delivers different performance,
the system will be able to discover the reason of this difference.

* Getting started:
------------------


* Versioning:
-------------

The version number of this compiler follows the Semantic Versioning
Specification (https://semver.org/spec/v2.0.0.html)

* License:
----------

(C) Copyright 2019-2020 the Colorado State University.

No warranties. Under development, code disclosed under request.
