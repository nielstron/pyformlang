# cppformlang Documentation

This document provides an overview of the cppformlang library, a C++ translation of the Python library [pyformlang](https://github.com/Aunsiels/pyformlang).

## Table of Contents

1. [Introduction](#introduction)
2. [Context-Free Grammar (CFG)](#context-free-grammar-cfg)
3. [Finite Automaton](#finite-automaton)
4. [Regular Expression](#regular-expression)
5. [Efficiency Improvements](#efficiency-improvements)

## Introduction

cppformlang is a C++ library for formal language manipulation. It provides efficient implementations of formal language concepts such as context-free grammars, finite automata, and regular expressions.

## Context-Free Grammar (CFG)

The CFG module provides classes and functions for working with context-free grammars.

### Key Classes

- `CFGObject`: Base class for all CFG objects (variables and terminals)
- `Variable`: Represents a variable in a CFG
- `Terminal`: Represents a terminal in a CFG
- `Epsilon`: Represents the empty string (epsilon) in a CFG
- `Production`: Represents a production rule in a CFG
- `CFG`: Represents a context-free grammar

### Key Features

- Parsing with CYK algorithm
- Conversion to Chomsky Normal Form
- Removal of useless symbols, epsilon productions, and unit productions

### Example

```cpp
// Create variables
auto S = std::make_shared<Variable>("S");
auto A = std::make_shared<Variable>("A");
auto B = std::make_shared<Variable>("B");

// Create terminals
auto a = std::make_shared<Terminal>("a");
auto b = std::make_shared<Terminal>("b");

// Create productions
auto p1 = std::make_shared<Production>(S, std::vector<std::shared_ptr<CFGObject>>{A, B});
auto p2 = std::make_shared<Production>(A, std::vector<std::shared_ptr<CFGObject>>{a, A});
auto p3 = std::make_shared<Production>(A, std::vector<std::shared_ptr<CFGObject>>{a});
auto p4 = std::make_shared<Production>(B, std::vector<std::shared_ptr<CFGObject>>{b, B});
auto p5 = std::make_shared<Production>(B, std::vector<std::shared_ptr<CFGObject>>{b});

// Create CFG
CFG grammar({S, A, B}, {a, b}, S, {p1, p2, p3, p4, p5});

// Check if a word is in the language
bool result = grammar.contains({"a", "a", "b", "b"});
```

## Finite Automaton

The Finite Automaton module provides classes and functions for working with finite automata.

### Key Classes

- `FiniteAutomaton`: Base class for all finite automata
- `DeterministicFiniteAutomaton`: Represents a deterministic finite automaton (DFA)
- `NondeterministicFiniteAutomaton`: Represents a nondeterministic finite automaton (NFA)
- `EpsilonNFA`: Represents a nondeterministic finite automaton with epsilon transitions
- `State`: Represents a state in a finite automaton
- `Symbol`: Represents a symbol in a finite automaton
- `Epsilon`: Represents the empty string (epsilon) in a finite automaton
- `TransitionFunction`: Represents a transition function in a DFA
- `NondeterministicTransitionFunction`: Represents a transition function in an NFA

### Key Features

- Conversion between different types of automata (DFA, NFA, ε-NFA)
- Operations: union, intersection, complement, concatenation, Kleene star
- Minimization of DFAs using Hopcroft's algorithm

### Example

```cpp
// Create states
auto q0 = std::make_shared<State>("q0");
auto q1 = std::make_shared<State>("q1");
auto q2 = std::make_shared<State>("q2");

// Create symbols
auto a = std::make_shared<Symbol>("a");
auto b = std::make_shared<Symbol>("b");

// Create DFA
auto dfa = std::make_shared<DeterministicFiniteAutomaton>();

// Set start state
dfa->set_start_state(q0);

// Add final state
dfa->add_final_state(q2);

// Add transitions
dfa->add_transition(q0, a, q1);
dfa->add_transition(q0, b, q0);
dfa->add_transition(q1, a, q1);
dfa->add_transition(q1, b, q2);
dfa->add_transition(q2, a, q1);
dfa->add_transition(q2, b, q0);

// Check if a word is accepted
bool result = dfa->accepts({"a", "b"});
```

## Regular Expression

The Regular Expression module provides classes and functions for working with regular expressions.

### Key Classes

- `RegexObject`: Base class for all regex objects
- `Symbol`: Represents a symbol in a regex
- `Epsilon`: Represents the empty string (epsilon) in a regex
- `EmptyLanguage`: Represents the empty language in a regex
- `Concatenation`: Represents the concatenation of two regex objects
- `Union`: Represents the union (alternation) of two regex objects
- `KleeneStar`: Represents the Kleene star of a regex object
- `Regex`: Represents a regular expression

### Key Features

- Parsing and evaluation of regular expressions
- Conversion to/from finite automata
- Operations: union, concatenation, Kleene star

### Example

```cpp
// Create regex objects
auto a = std::make_shared<Symbol>("a");
auto b = std::make_shared<Symbol>("b");

// Create regex (a + b)*ab
auto a_or_b = std::make_shared<Union>(a, b);
auto star = std::make_shared<KleeneStar>(a_or_b);
auto ab = std::make_shared<Concatenation>(a, b);
auto regex_obj = std::make_shared<Concatenation>(star, ab);

Regex regex(regex_obj);

// Check if a word is accepted
bool result = regex.accepts({"a", "b", "a", "b"});
```

## Efficiency Improvements

The C++ implementation includes several efficiency improvements over the Python version:

1. **Static Typing**: C++'s static typing eliminates the need for runtime type checking.

2. **Memory Management**: Smart pointers (`std::shared_ptr`, `std::unique_ptr`) provide efficient memory management.

3. **Data Structures**: 
   - Hash-based containers (`std::unordered_set`, `std::unordered_map`) for faster lookups
   - Custom hash functions for complex objects

4. **Move Semantics**: Move semantics minimize unnecessary copying of objects.

5. **Inlining**: Small, frequently called functions are inlined for better performance.

6. **Algorithms**: Optimized implementations of key algorithms:
   - Hopcroft's algorithm for DFA minimization
   - CYK algorithm for CFG parsing
   - Subset construction for NFA to DFA conversion

7. **Memory Efficiency**: More compact data structures reduce memory usage.