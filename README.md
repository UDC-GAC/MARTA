# MARTA - Micro ARchitectural Toolkit for Analysis

[![Python
package](https://github.com/markoshorro/MARTA/actions/workflows/python-package.yml/badge.svg)](https://github.com/markoshorro/MARTA/actions/workflows/python-package.yml)
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
and those variables or parameters, MARTA extracts information in form of decision tree
regarding performance. Decision tree categorizes the performance of the kernel
according to the dimensions of interest specified.

MARTA is also a very low intrusive profiler, even though it requires recompiling.
Just with a header and two directives indicating the start and end of the
region of interest (ROI), it can perform different compilations and executions,
for instance, using different flags and/or compilers, and generating a readable
table with performance metrics. This enables a fast comparison between
compilers for a vast set of different combinations of parameters and flags.

## Dependencies

- Python >=3.7
- Libraries specified in [`requirements.txt`](requirements.txt)
- PAPI >=5.7.0
- Linux environment with root access

## Getting started

This project has two large and independent components:

- `profiler`: in charge of compiling, executing and gathering performance
  metrics such as cycles, time and FLOPS/s for a concrete kernel with regard to
  a input file specifying all parameters.
- `analyzer`: given an input in table form (e.g. CSV) and some parameters,
  using [scikit-learn](https://scikit-learn.org/stable/index.html)
  generates a classification system in order to **categorize** performance,
  as well as detecting false positives/negatives. Typically, this system is
  either a decision tree or a random forest algorithm.

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

This will install a module named `marta`, and two console scripts:
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

### Examples: cases of study

Under the [examples](examples/) directory there are available examples to
better understand how the tool works.

## License, copyright and authors

See [LICENSE](LICENSE), [COPYRIGHT](COPYRIGHT) and [AUTHORS](AUTHORS) files, respectively, for further information.
