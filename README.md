# MyContainer - Custom C++ Container with Multiple Iterator Types

**Author:** Yarin Keshet

## Overview

MyContainer is a templated C++ container class that provides multiple specialized iterators for traversing elements in different orders. It demonstrates advanced C++ concepts including templates, nested classes, iterator design patterns, and operator overloading.

## Features

### Core Container Functionality
- **Template-based**: Supports any data type (int, string, double, custom classes)
- **Dynamic sizing**: Add and remove elements dynamically
- **Duplicate handling**: Supports duplicate elements, removes all occurrences
- **Exception safety**: Proper error handling with meaningful exceptions

### Six Specialized Iterator Types

1. **AscendingOrder**: Traverses elements from smallest to largest
2. **DescendingOrder**: Traverses elements from largest to smallest  
3. **SideCrossOrder**: Alternates between smallest and largest remaining elements
4. **ReverseOrder**: Traverses elements in reverse insertion order
5. **Order**: Traverses elements in original insertion order
6. **MiddleOutOrder**: Starts from middle, alternates left-right

## File Structure

```
CPP_EX4_25/
├── MyContainer.hpp          # Header-only template
├── MyContainer.cpp          # Implementation file
├── main.cpp                 # Demo program
├── tests.cpp                # Comprehensive test suite (doctest)
├── makefile                 # Build configuration
└── README.md                # This file
```

### Header-Only Design

This project uses a **header-only template library** approach:

- **`MyContainer.hpp`**: Contains all class declarations, method implementations, and template specializations
- **No separate `.cpp` file**: All template implementations are inline in the header
- **Benefits**: 
  - Simpler build process
  - Better compiler optimization opportunities
  - Works with any type without explicit instantiation
  - Easy to distribute as a single header file
- **Template instantiation**: Happens automatically when you include the header and use the container

## Building the Project

### Prerequisites
- C++11 compatible compiler (g++)
- Make utility
- Valgrind (optional, for memory checking)

### Build Commands

```bash
# Build everything
make all

# Build and run main demo
make MyContainer_exe
./MyContainer_exe

# Build and run tests
make test
./tests_exe

# Memory leak checking
make vg           # Main program with Valgrind
make vg-test      # Tests with Valgrind

# Clean build artifacts
make clean
```

**Note**: Since MyContainer is header-only, only `main.cpp` and `tests.cpp` are compiled. The template code is automatically included during compilation.

## Demo

The project includes a comprehensive demo program that showcases all features:

```bash
# Run the interactive demo
make MyContainer_exe
./MyContainer_exe
```

**Demo Features:**
- Basic container operations (add, size, isEmpty)
- All six iterator types with example data `[7, 15, 6, 1, 2]`
- String container demonstrations with alphabetical sorting
- Even-numbered container examples showing middle-out behavior
- Duplicate element handling across all iterator types
- Error handling demonstrations
- Real-time output showing each iterator's traversal pattern

**Sample Demo Output:**
```
=== MyContainer Demo ===
4. Testing ALL Iterator Types:
   Original container [7, 15, 6, 1, 2]:

   AscendingOrder (smallest to largest):
   1 2 6 7 15 

   DescendingOrder (largest to smallest):
   15 7 6 2 1 

   SideCrossOrder (alternating min/max):
   1 15 2 7 6 

   ReverseOrder (reverse insertion order):
   2 1 6 15 7 

   Order (original insertion order):
   7 15 6 1 2 

   MiddleOutOrder (middle, then alternating left-right):
   6 15 1 7 2 
```

## Testing

The project includes comprehensive test cases using the doctest framework:

```bash
./tests_exe
```

**Test Coverage:**
- Basic container operations (add, remove, size, isEmpty)
- All iterator types with various scenarios
- Edge cases (empty containers, single elements)
- Different data types (int, string, double)
- Error handling and bounds checking
- Iterator equality and inequality operators
- Memory safety (no modifications to original container)

## Memory Management

- **No memory leaks**: Verified with Valgrind
- **RAII compliance**: Automatic cleanup with destructors
- **Exception safety**: Strong exception safety guarantee
- **Template efficiency**: Explicit instantiations for common types(int,double,std::string)

## Technical Details

### Template Design
```cpp
// Header-only approach - no explicit instantiations needed
// Templates are instantiated automatically when used:
MyContainer<int> intContainer;        // Instantiates int version
MyContainer<char> charContainer;      // Instantiates char version  
MyContainer<string> stringContainer;  // Instantiates string version
```

### Compiler Integration
- **Header-only**: Include `MyContainer.hpp` and start using immediately
- **No linking required**: All code is in headers, compiled with your source
- **Template flexibility**: Works with any type that supports required operations (`<`, `==`, copy constructor)

### Iterator Design Pattern
- Each iterator is a nested class with standard iterator interface
- Implements `begin()`, `end()`, `operator++`, `operator*`, `operator==`, `operator!=`
- Follows C++ iterator conventions and STL compatibility

### Compiler Flags
- `-std=c++11`: C++11 standard compliance
- `-Wall -Wextra`: Comprehensive warnings
- Valgrind integration for memory checking

## Performance Characteristics

| Operation          | Time Complexity  | Space Complexity  |
|--------------------|------------------|-------------------|
| `add()`            | O(1) amortized   | O(1)              |
| `remove()`         | O(n)             | O(1)              |
| `size()`           | O(1)             | O(1)              |
| Iterator creation  | O(n log n)       | O(n)              |
| Iterator traversal | O(1) per element | O(1)              |

**Note**: Iterator creation involves sorting (except Order and ReverseOrder), hence O(n log n) complexity.

## License

This project is created for educational purposes as part of a C++ systems programming course.

## Contact

For questions or suggestions, contact: yarinkash1@gmail.com