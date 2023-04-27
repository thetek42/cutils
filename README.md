# CUtils

CUtils is a set of miscellaneous utilities for the C programming language.

## Modules

The utilities are split up into multiple modules. The documentation for all
functions can be found in the header files (with a short description) as well
as in the source files (with a detailed description and explanation of
parameters and return values).

- `color`: Color conversion and manipulation functions
- `common`: Common utilities that are very common but did not fit in any other
  module, e.g. safe memory allocation or a few math functions
- `cstr`: Functions that expand C's `<string.h>` library for `char *` strings
- `debug`: Debug utilities, e.g. debug messages for memory allocations
- `enum-helper`: Helper macros for enums (header only)
- `fs`: File system handling
- `log`: Logging functionality with different log levels and support for
  printing source file and line information
- `str`: A custom string type that stores length and capacity and associated
  functions for interacting with it
- `test`: Simple unit testing library
- `vec`: Vectorized math operations

Note that some modules may depend on each other.
