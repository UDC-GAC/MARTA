# Auto-vectorizing reductions

**RQ.- Does `-ffast-math` flag always enable vectorization of reductions of
floats in GCC, even for scalars?**

## Results: conclusions

## Experimental configuration:

* Intel(R) Xeon(R) Silver 4216 CPU @ 2.10GHz
* Compiler: GCC 11.2.0, Intel CC
* [MARTA Profiler Full Configuration file](config_profiler.yml)

## How to reproduce:

1. Profiling
    ```
    # place at the root of the project
    marta_profiler examples/autovectorization/config_profiler.yml
    # or
    python -m marta.profiler examples/autovectorization/config_profiler.yml
    ```

    This step should take many hours.