# cppformlang

A C++ library for formal language manipulation, translated from the Python library [pyformlang](https://github.com/Aunsiels/pyformlang).

## Overview

This library provides efficient C++ implementations of formal language concepts:

- Context-Free Grammars (CFG)
- Finite Automata (DFA, NFA, ε-NFA)
- Regular Expressions

## Features

- **Context-Free Grammars**:
  - Parsing with CYK algorithm
  - Conversion to Chomsky Normal Form
  - Operations: removal of useless symbols, epsilon productions, unit productions

- **Finite Automata**:
  - Deterministic Finite Automaton (DFA)
  - Nondeterministic Finite Automaton (NFA)
  - Epsilon-NFA
  - Operations: union, intersection, complement, minimization

- **Regular Expressions**:
  - Parsing and evaluation
  - Conversion to/from finite automata

## Efficiency Improvements

This C++ implementation focuses on efficiency:

- Uses STL containers with appropriate complexity guarantees
- Employs move semantics to minimize copying
- Uses hash-based containers for faster lookups
- Implements efficient algorithms for common operations
- Provides memory-efficient data structures

## Requirements

- C++17 compatible compiler
- CMake 3.14 or higher

## Installation

```bash
mkdir build && cd build
cmake ..
make
make install
```

## Usage

```cpp
#include <cppformlang/cfg/cfg.h>
#include <cppformlang/finite_automaton/dfa.h>
#include <cppformlang/regular_expression/regex.h>
#include <iostream>

int main() {
    // Example code will be provided
    return 0;
}
```

## License

MIT License