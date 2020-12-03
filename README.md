<h2 align="center">MARTA - Micro ARchiTectural Analyzer</h2>

<p align="center">
<a href="https://github.com/psf/black/blob/master/LICENSE"><img alt="License: MIT" src="https://black.readthedocs.io/en/stable/_static/license.svg"></a>
<a href="https://github.com/psf/black"><img alt="Code style: black" src="https://img.shields.io/badge/code%20style-black-000000.svg"></a>
</p>

MARTA is a toolkit for analyzing peformance in any architecture given any kind,
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
regarding performance. This decision tree can give hints regarding how data
should be distributed given a kernel.

## Getting started

This project has two big and independent components:

- `profiler`: in charge of compiling, executing and gathering performance
  metrics such as cycles, time and FLOPS/s for a concrete kernel with regard to
  a input file specifying all parameters.
- `analyzer`: given an input in table form (e.g. CSV) and some parameters,
  using [WEKA (framework for ML)](https://www.cs.waikato.ac.nz/ml/weka/)
  generates a decision tree in order to **categorize** performance,
  as well as detecting false positives/negatives.

What does **categorizing performance** means?

## Versioning

The version number of this compiler follows the Semantic Versioning
Specification (<https://semver.org/spec/v2.0.0.html>)

## Author

- Marcos Horro Varela: marcos.horro@udc.gal (maintainer)
- Dr. Louis-Noël Pouchet: pouchet@colostate.edu

## License

(c) Copyright 2019-2020 the Colorado State University.
(c) Copyright 2020- Universidade da Coruña.

MIT license.

No warranties. Under development, code disclosed under request.
