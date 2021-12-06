# MARTA: Multi-configuration Assembly pRofiler Toolkit for performance Analysis

[![Python
package](https://github.com/markoshorro/MARTA/actions/workflows/python-package.yml/badge.svg)](https://github.com/markoshorro/MARTA/actions/workflows/python-package.yml)
[![Version](https://img.shields.io/badge/version-v0.0.1a0-008080)](https://github.com/markoshorro/MARTA)
[![Python versions](https://img.shields.io/badge/python-3.7%20%7C%203.8%20%7C%203.9-cf362b)](https://www.python.org/download/releases/3.0/)
[![Code Black](https://img.shields.io/badge/code%20style-black-000000.svg)](https://github.com/psf/black)
[![License](https://img.shields.io/badge/License-Apache%202.0-blue.svg)](https://opensource.org/licenses/Apache-2.0)


MARTA is a toolkit for analyzing performance in any architecture given any kind,
in form and shape, of C/C++ code and a set of features to take into account.

This toolkit performs in two stages: profiling and analysis. The first component
compiles, executes and collects information from hardware counters, and the second
component post-process that data offline given a set of parameters to consider,
applying ML techniques for classification in order to generate knowledge.
For instance, having a piece of code or kernel such as:

```
for (int i = INIT_VAL; i < UPPER_BOUND; i += STEP) {
    y[i] += A[i] * x[i];
}
```

It could be interesting to analyze the deviation in performance of same code
but varying `INIT_VAL`, `UPPER_BOUND` and `STEP`. Just given that little code
and those variables or parameters, MARTA extracts information in the form of a
decision tree regarding performance. Decision trees categorize the performance
of the kernel (or other target column of the domain) according to the dimensions of
interest specified.

MARTA is also a very low intrusive profiler, even though it requires recompiling.
Just with a header and two directives indicating the start and end of the
region of interest (RoI), it can perform different compilations and executions,
for instance, using different flags and/or compilers, and generating a readable
table with performance metrics. This enables a fast comparison between
compilers for a vast set of different combinations of parameters and flags.

## Dependencies

- Python >=3.7
- Libraries specified in [`requirements.txt`](requirements.txt)
- PAPI >=5.7.0
- Linux environment with root access. Recommended >=3.14 version to allow PAPI
  use `rdpmc` for reading hardware counters.

## Getting started

This project has two large and independent components:

- `profiler`: in charge of compiling, executing and gathering performance
  metrics such as cycles, time and FLOPS/s for a concrete kernel with regard to
  a input file specifying all parameters.
- `analyzer`: given an input in table form (e.g. CSV) and some parameters,
  using [scikit-learn](https://scikit-learn.org/stable/index.html) generates a
  classification system in order to **categorize** performance (or other
  dimension of interest), and reporting the accuracy of the system. Typically,
  this system is either a decision tree or a random forest classifier/regressor.

### Installation

MARTA supports out-of-tree execution. This method could be
preferred in order to avoid copying files, for instance, in an already
existent project.

#### Out-of-tree

Install a pre-built package (if any) or build the wheel and install it:

```
cd MARTA
python -m build
python -m pip install dist/<marta-wheel>
# or just
python -m pip install <marta-wheel>
```

This will install a module named `marta`, and two console scripts or CLI commands:
`marta_profiler` and `marta_analyzer`. **NOTE**: to run these commands it is needed
to specify in `PATH` variable the path where your Python version install
applications, e.g. `export PATH=$PATH:$HOME/.local/bin` if your Python
distribution install packages in `$HOME/.local/bin`.

#### Use from the sources

If you just want to use MARTA as a module this can be done easily by just:

```
cd MARTA/marta
python -m profiler ... 
# or
python -m analyzer ...
``` 

## Profiler

## Analyzer

### Examples: cases of study

Under the [examples](examples/) directory there are available examples to
better understand how the tool works.

### Testing

This library uses `pytest` for unit and integration tests. All tests are
located under [tests](tests/) directory. For more information refer to
[tests/README.md](tests/README.md).

## License, copyright and authors

See [LICENSE](LICENSE), [COPYRIGHT](COPYRIGHT) and [AUTHORS](AUTHORS) files, respectively, for further information.

## Citation

TBD.