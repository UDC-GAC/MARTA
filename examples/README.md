# MARTA - Examples

In order to illustrate the capabilities of MARTA, we have developed a set of
cases of study which answer different [research
questions](https://en.wikipedia.org/wiki/Research_question). For each case, we
provide the full experimental setup needed to reproduce these experiments.

## Case of study #1: [micro-benchmarking gather and scatter instructions](gather_scatter/)

RQ.- Can we build an analytical model of the performance of gather/scatter
based on number (and set it maps to?) of cache lines touched (_hot_ cache)?

## Case of study #2: [loop interchange/permutation cost model](loop_interchange)

RQ.- How to relate source code metrics (e.g., loop depth, nesting, trip count,
type of array access: affine vs. non-affine, reuse direction/distance, etc.)
with the application of loop interchange in GCC, when using the flag
`-floop-interchange`? In other words, can we reverse-engineer the cost model of
GCC to apply interchange?

## Case of study #3: [auto-vectorization of reductions](autovectorization)

RQ.- Does `-ffast-math` flag always enable vectorization of reductions of
floats in GCC, even for scalars?
