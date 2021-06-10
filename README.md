<h2 align="center">MARTA - Micro ARchitectural Toolkit for Analysis</h2>

<p align="center">
<a href="https://github.com/psf/black/blob/master/LICENSE"><img alt="License: MIT" src="https://black.readthedocs.io/en/stable/_static/license.svg"></a>
<a href="https://github.com/psf/black"><img alt="Code style: black" src="https://img.shields.io/badge/code%20style-black-000000.svg"></a>
</p>

MARTA is a toolkit for analyzing performance in any architecture given any kind,
in form and shape, of C/C++ code and a set of features to take into account.

This toolkit performs in two stages: profiling and analysis. The first component
compiles, executes and gathers information in a CSV file, and the second
component post-process that data offline given a set of parameters to consider.
For instance, having a piece of code or kernel such as:

```
for (int i = INIT_VAL; i < UPPER_BOUND; i += STEP) {
    y[i] += A[i] * x[i];
}
```

It could be interesting to analyze the deviation in performance of same code
but varying `INIT_VAL`, `UPPER_BOUND` and `STEP`. Just given that little code
and those variables or parameters, MARTA extracts information in form of decision tree
regarding performance. Decision tree informs how those variables affect to
kernel performance.

MARTA is also a very low intrusive profiler (even though requires recompiling).
Just with a header and two directives indicating the start and end of the
region of interest (ROI), it can perform different compilations and executions,
for instance, using different flags and/or compilers, and generating a readable
table with performance metrics.

It is recommended to check out testing configuration files for more clarity.

## Dependencies

- Python >=3.7

## Getting started

This project has two big and independent components:

- `profiler`: in charge of compiling, executing and gathering performance
  metrics such as cycles, time and FLOPS/s for a concrete kernel with regard to
  a input file specifying all parameters.
- `analyzer`: given an input in table form (e.g. CSV) and some parameters,
  using [scikit-learn](https://scikit-learn.org/stable/index.html)
  generates a classification system in order to **categorize** performance,
  as well as detecting false positives/negatives. Typically, this system is
  either a decision tree or a random forest algorithm.

TODO: What does **categorizing performance** means?

### Installation

MARTA supports out-of-tree building and execution. This method could be
preferred in order to avoid copying files, for instance, in an already
existent project.

#### Out-of-tree

#### From sources

## Micro-benchmarking

Micro-benchmarking is not an easy task, it requires fine-grained tuning in
order to measure properly very small and critical regions of interest. We could
debate what is realistic or not when it comes to measuring instructions, since
the chain of operations has an impact on the throughput. Nonetheless, this
toolkit integrates different macros and functions trying to avoid the set 

## License, copyright and authors

See [LICENSE](LICENSE), [COPYRIGHT](COPYRIGHT) and [AUTHORS](AUTHORS) files, respectively, for further information
