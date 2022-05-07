<img src="docs/marta_logo.png" width="300px" alt="MARTA logo" style="display: block; margin-left: auto; margin-right: auto; width: 50%;"/>

# MARTA: Multi-configuration Assembly pRofiler Toolkit for performance Analysis

[![Python
package](https://github.com/markoshorro/MARTA/actions/workflows/python-package.yml/badge.svg)](https://github.com/markoshorro/MARTA/actions/workflows/python-package.yml)
[![Documentation Status](https://readthedocs.org/projects/marta/badge/?version=latest)](https://marta.readthedocs.io/en/latest/?badge=latest)
[![Version](https://img.shields.io/badge/version-v0.1.0-008080)](https://github.com/markoshorro/MARTA)
[![Python versions](https://img.shields.io/badge/python-3.7%20%7C%203.8%20%7C%203.9-cf362b)](https://www.python.org/download/releases/3.0/)
[![Code Black](https://img.shields.io/badge/code%20style-black-000000.svg)](https://github.com/psf/black)
[![License](https://img.shields.io/badge/License-Apache%202.0-blue.svg)](https://opensource.org/licenses/Apache-2.0)

MARTA is a productivity-aware toolkit for profiling and performance
characterization. It is meant for executing

This toolkit performs in two stages: profiling and analysis. The first component
compiles, executes and collects information from hardware counters, and the second
component post-process that data offline given a set of parameters to consider,
applying data mining and ML techniques for classification in order to build
knowledge, e.g., in the form of decision trees, analyzing the influence of
dimensiones, etc. For instance, having a piece of code or kernel such as:

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

MARTA is also a very low intrusive profiler, even though it requires
recompiling. It is a header-based profiler, including directives for detailing
the start and end of the region of interest (RoI), it can perform different
compilations and executions, for instance, using different flags and/or
compilers, and generating a readable table with performance metrics. This
enables a fast comparison between compilers for a vast set of different
combinations of parameters and flags.

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

The Profiler module is designed for parsing the configuration files, compiling
all the binary versions specified in them, and running the generated binaries,
collecting execution data. The strength of this module lies in its ability to
generate as many different executable versions as necessary, as defined by the
Cartesian product of the sets of different options in the configuration, e.g.,
compile-time options (e.g., whether to enable or disable particular
optimizations), program inputs, or program features (e.g., -D flags
enabling different code paths). The generation of different program versions,
which is often a bottleneck in micro-architectural exploration, can be done in
parallel.

In order to achieve maximum reliability, the Profiler integrates with several
different tested-and-true software packages such as the PolyBench/C
library, using their low-level configuration and measuring
capabilities. The upper part of Figure~\ref{fig:martaarch} details the design
of this module.
The Profiler receives two inputs:

- Configuration file: a structured YAML file containing all parameters
  related to compilation (e.g. -D flags, compilers and their flags, etc.),
  execution (e.g. threads to launch and their affinity, number of
  repetitions, maximum deviation in measurements, etc.), and data collection
  (e.g. output format, dimensions to include, static code analysis
  parameters, etc.). For convenience, some of these parameters can be
  overwritten by using CLI arguments.
- Source code/application: typically a C/C++ program whose execution prints
  in standard output values collected from hardware counters, as well as the
  execution time and values reported by the Time Stamp Counter (TSC). The
  system helps produce this output format by including a set of functions and
  macros at runtime.

The output generated by all the executions in the experimental set is encoded
into a CSV file, which is passed as input to the Analyzer module.

## Analyzer

The Analyzer integrated in the tool is meant for processing raw data, typically
the output of the Profiler, and mining knowledge from these data, primarily
through the use of scikit-learn. It can also generate relational plots given a
set of dimensions of interest.

- Configuration file: a structured YAML file specifying data wrangling
  parameters (including filtering, normalization and categorization) as well
  as classification and plotting parameters. For classification
  customization, all parameters follow the same naming or API as in
  scikit-learn.

## Configuration

The configuration file for the profiler is structured in a YAML file.
Parameters available for the **profiler** kernel dictionary:

| Parameter       | Description                                                                                                  | Type   | Default |
| --------------- | ------------------------------------------------------------------------------------------------------------ | ------ | ------- |
| `name`          | Name of the kernel or program.                                                                               | `str`  | -       |
| `path`          | Folder containing the sources.                                                                               | `str`  | -       |
| `preamble`      | Commands to execute before compilation. Tuning CPUs, allocating huge pages, etc.                             | `str`  | ``''    |
| `finalize`      | Tasks to execute after the experiments.                                                                      | `dict` | -       |
| `configuration` | Cartesian product of the list of parameters. This includes the list Makefile options, `-D` definitions, etc. | `dict` | -       |
| `compilation`   | Compiler configurations (`compiler` table).                                                                  | `dict` | -       |
| `execution`     | Execution parameters (`execution` table).                                                                    | `dict` | -       |
| `output`        | Output options, such as name and format (`output` table).                                                    | `dict` | -       |

`finalize` parameters:

| Parameter         | Description                                                      | Type   | Default |
| ----------------- | ---------------------------------------------------------------- | ------ | ------- |
| `clean_tmp_files` | Clean temporal files.                                            | `bool` | `True`  |
| `clean_asm_files` | Clean assembly files generated.                                  | `bool` | `True`  |
| `clean_asm_files` | Clean binary files.                                              | `bool` | `False` |
| `command`         | Execute a command after the execution of the set of experiments. | `str`  | ``''    |

`configuration` parameters:

| Parameter    | Description                                                                                        | Type       | Default |
| ------------ | -------------------------------------------------------------------------------------------------- | ---------- | ------- |
| `kernel_cfg` | Options to Makefile.                                                                               | `str list` | [``'']  |
| `d_features` | \texttt{-D} flags. Each of them can be described as in table `d_features`.                         | `dict`     | -       |
| `flops`      | Expression for computing FLOPS count. This can be expressed dynamically using `d_features` values. | `str`      | -       |

`compiler` parameters:

| Parameter        | Description                                                                                                                                                         | Type            | Default  |
| ---------------- | ------------------------------------------------------------------------------------------------------------------------------------------------------------------- | --------------- | -------- |
| `enabled`        | Enable/disable compilation. Useful for pre-generated binaries.                                                                                                      | `bool`          | `True`   |
| `processes`      | Number of processes to use for compilation.                                                                                                                         | `int`           | 1        |
| `compiler_flags` | Dictionary of compilers with a list of specific flags each.                                                                                                         | `dict of lists` | -        |
| `main_src`       | Main source file to be compiled                                                                                                                                     | `str`           | `main.c` |
| `kernel_inlined` | If kernel not inlined, then it need to be compiled from a different source.                                                                                         | `bool`          | `False`  |
| `loop_type`      | "asm" or "C". Determines the language for MARTA instrumentation insertion.                                                                                          | `str`           | "asm"    |
| `asm_analysis`   | `syntax`: ASM syntax, `count_ins`: count the number and type of ASM instructions in the region of interest, `static_analysis`: perform code analysis using LLVM-MCA | `dict`          | {}       |

`d_features` parameters:

| Parameter  | Description                                                                                                | Type     | Default   |
| ---------- | ---------------------------------------------------------------------------------------------------------- | -------- | --------- |
| `type`     | Type of expression: static, dynamic. static for `list` arguments, `dynamic` for iterators, e.g. itertools. | `str`    | ``''      |
| `val_type` | Value of the expression: "numeric", "string".                                                              | `str`    | "numeric" |
| `value`    | Expression generating the list of values, e.g. `[0,1,2,3]`, `itertools.product([0,1], [10,20])`, etc.      | `Object` | -         |

`execution` parameters:

| Parameter            | Description                                                       | Type       | Default |
| -------------------- | ----------------------------------------------------------------- | ---------- | ------- |
| `enabled`            | Enable execution                                                  | `bool`     | `True`  |
| `papi_counter`       | List of PAPI counters to read.                                    | `str list` | -       |
| `time`               | Measure execution time with `gettimeofday`.                       | `bool`     | `False` |
| `tsc`                | Measure TSC cycles using `rdtsc`.                                 | `bool`     | `False` |
| `nexec`              | Repetitions per each configuration.                               | `int`      | 7       |
| `threshold_outliers` | Threshold for outlier detection.                                  | `int`      | .1      |
| `mean_and_discard`   | Compute average values after discarding outliers.                 | `bool`     | `False` |
| `nsteps`             | Number of iterations of the loop containing the ROI if specified. | `int`      | 1       |
| `intel_turbo`        | Enable or disable turbo boost on Intel processors via MSR.        | `bool`     | `False` |
| `max_freq`           | Set maximum CPU frequency via MSR.                                | `bool`     | `False` |
| `cpu_affinity`       | Logical CPU ID for pinning single-thread measurements.            | `int`      | 0       |
| `cache_flush`        | Cache flush enabled for architectures supporting `CLFSH`.         | `bool`     | `False` |

`output` parameters:

| Parameter | Description                                                                                                                           | Type   | Default |
| --------- | ------------------------------------------------------------------------------------------------------------------------------------- | ------ | ------- |
| `name`    | Name of output file.                                                                                                                  | `str`  | -       |
| `columns` | Output columns. If "all", then all dimensions used in the configuration: compiler, d_features, kernel_config, papi_counters, etc.     | `str`  | -       |
| `report`  | Generate a log file with all information related to the experiment: host machine, elapsed time, standard output, standard error, etc. | `bool` | -       |

The same scheme follows for the **analyzer**. Parameters available for this
component:

| Parameter         | Description                                                       | Type   | Default |
| ----------------- | ----------------------------------------------------------------- | ------ | ------- |
| `input`           | Input data in CSV format.                                         | `str`  | -       |
| `output_path`     | Output path.                                                      | `str`  | -       |
| `prepare_data`    | Preprocessing configuration.                                      | `dict` | -       |
| `plot`            | Plotting parameters.                                              | `dict` | -       |
| `classification`  | Parameters for classification analyses, e.g., decision trees.     | `dict` | -       |
| `feat_importance` | Parameters for feature importance analyses, e.g., random forests. | `dict` | -       |

`prepare_data` parameters:

| Parameter    | Description                                                                                                                                                                                                                                                                                       | Type   | Default |
| ------------ | ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- | ------ | ------- |
| `cols`       | Columns or dimensions to consider.                                                                                                                                                                                                                                                                | `list` | -       |
| `rows`       | Values of rows to filter.                                                                                                                                                                                                                                                                         | `dict` | -       |
| `target`     | Dimension of interest, e.g. FLOPS.                                                                                                                                                                                                                                                                | `str`  | -       |
| `norm`       | Normalization of values for the target dimension: `minmax` or `zscore`.                                                                                                                                                                                                                           | `str`  | -       |
| `categories` | Dictionary containing meta-information for the categories: `num` (number of categories to generate statically), `grid_search` (use KDE and perform grid searching for bandwidth and kernel parameters), `mode` (if `normal`, Silverman is used for KDE. If `multimodal`, Sheather-Jones is used). | `dict` | -       |

`plots` parameters:

| Parameter   | Description                                              | Type   | Default |
| ----------- | -------------------------------------------------------- | ------ | ------- |
| `sort`      | Dimension to use for sorting values.                     | `str`  | -       |
| `type`      | Type of plot: relplot, scatterplot, lineplot or kdeplot. | `str`  | -       |
| `format`    | Output format: png, pdf, eps, ps or svg.                 | `str`  | -       |
| `x_axis`    | Dimension for the X axis.                                | `str`  | -       |
| `y_axis`    | Dimension for the Y axis.                                | `str`  | -       |
| `hue`       | Dimension to group by color.                             | `str`  | -       |
| `size`      | Dimension to group by size.                              | `str`  | -       |
| `log_scale` | Apply logarithmic scale.                                 | `bool` | -       |

### Examples: cases of study

Under the [examples](examples/) directory there are available examples to
better understand how the tool works.

### Testing

This library uses `pytest` for unit and integration tests. All tests are
located under [tests](tests/) directory. For more information refer to
[tests/README.md](tests/README.md).

## Contributing

See the [CONTRIBUTING.md](CONTRIBUTING.md) file.

## License, copyright and authors

See [LICENSE](LICENSE), [COPYRIGHT](COPYRIGHT) and [AUTHORS](AUTHORS) files, respectively, for further information.

## Logo

Lili Kudrili/Shutterstock.com

## Citation

Regular citation:

```
Horro, M. Pouchet, L.-N. Rodríguez, G. and Touriño, J. MARTA: Multi-configuration Assembly pRofiler and Toolkit for performance Analysis in Proceedings of the EEE International Symposium on Performance Analysis of Systems and Software (ISPASS), Singapore, pp. 10:1-11. 2022.
```

Bibtex example:

```
@inproceedings{horro,
  author={Horro, Marcos and Pouchet, Louis-Noël and Rodríguez, Gabriel and Touriño, Juan},
  booktitle={2022 IEEE International Symposium on Performance Analysis of Systems and Software (ISPASS)},
  title={MARTA: Multi-configuration Assembly pRofiler and Toolkit for performance Analysis},
  year={2022},
  volume={},
  number={},
  pages={35-44},
}
```
