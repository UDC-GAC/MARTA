# MARTA - Examples

In order to illustrate the capabilities of MARTA, we have developed a set of
cases of study which answer different [research
questions](https://en.wikipedia.org/wiki/Research_question). For each case, we
provide the full experimental setup needed to reproduce these experiments.

## [Empirical throughput of FMA instructions](asm/)
RQ.- How many independent FMA instructions can be executed in just one cycle,
assuming hot cache, regardless of data type, vector size and ISA?

## [STREAM: influence of access pattern on memory bandwidth](sat_packing/)

RQ.- Consider a vector operation of the form: $c(f(i)) =
a(g(i)) ∗ b(h(i))$
How does the memory bandwidth vary with the access patterns, influenced by the
access functions _f_, _g_, and _h_?

## [Micro-benchmarking gather and scatter instructions](gather_scatter/)

RQ.- Can we build an analytical model of the performance of gather/scatter
based on number (and set it maps to?) of cache lines touched (_hot_ cache)?

## [Loop interchange/permutation cost model](loop_interchange)

RQ.- How to relate source code metrics (e.g., loop depth, nesting, trip count,
type of array access: affine vs. non-affine, reuse direction/distance, etc.)
with the application of loop interchange in GCC, when using the flag
`-floop-interchange`? In other words, can we reverse-engineer the cost model of
GCC to apply interchange?

## [Auto-vectorization of reductions](autovectorization)

RQ.- Does `-ffast-math` flag always enable vectorization of reductions of
floats in GCC, even for scalars?

----

We also provide other examples of the tool and the integration with other tools.

## [Sparse matrices vectorization with MACVETH](matrices/)

MACVETH is a novel compiler for auto-vectorizing irregular codes. MARTA
supports this compiler.

## [Multithread](multithread/)

Just a dummy benchmark for testing the multithreading support of the framework.