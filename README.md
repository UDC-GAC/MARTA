# MARTA - Micro ARchiTectural Analyzer

MARTA is a framework for reverse-engineering features of the
architecture. Some information regarding a concrete architecture may not be
fully disclosed by the manufacturer.

For this reason, we designed a tool which is able to extract information by
executing mini-kernels with different configurations in order to determine on
which conditions the performance varies. E.g. if a kernel with the same number
of floating point operations (FLOPs) for two different configurations (e.g.
two different strides, same compilation flags) delivers different performance,
the system will be able to disclose according to the input data, what are the
dominant parameters involved in this gap.

## Getting started

TODO

## Versioning

The version number of this compiler follows the Semantic Versioning
Specification (<https://semver.org/spec/v2.0.0.html>)

## Author

- Marcos Horro Varela: marcos.horro@udc.gal (mantainer)
- Dr.Louis-Noël Pouchet: pouchet@colostate.edu

## License

(c) Copyright 2019-2020 the Colorado State University.
(c) Copyright 2020 Universidade da Coruña.

MIT license.

No warranties. Under development, code disclosed under request.
