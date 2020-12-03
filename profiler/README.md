# MARTA - Profiler

Machine characterization is a tedious task that can require a lot of profiling
by executing many programs or kernels and analyzing their performance. This
tool has been created to automate this task.

This part of MARTA is meant for:

- Compiling kernels with different configurations, regarding: loop stride,
  datasizes, etc.
- Execute and time those kernels. There is also the possibility of measuring
  hardware counters using PAPI/C interface.
- Create a CSV/pandas (python) DataFrame with all the configurations and results
  obtained in the execution.

## Requirements

Need to have Python 3 (no, there is no Python 2 version nor will be one).
Profiler works with a configuration file in YAML format. Therefore:

```
chmod +x profiler
./profiler -i file.yml
```

## Author

- Marcos Horro Varela: marcos.horro@udc.gal (mantainer)
- Dr.Louis-Noël Pouchet: pouchet@colostate.edu

## License

(c) Copyright 2019-2020 the Colorado State University.
(c) Copyright 2020 Universidade da Coruña.

MIT license.

No warranties. Under development, code disclosed under request.
