# Rectangle Intersection Finder

A C++ program that finds intersections between rectangles defined in a JSON file.

## Prerequisites

- CMake 3.14 or higher
- C++17 compliant compiler
- Git

Following dependencies will be automatically fetched and built if not found:
- Google Test (for unit testing)
- nlohmann_json (for JSON parsing)

## Building the Project

```bash
# 1. Clone the repository
git clone <repository-url>
cd <repository-name>

# 2. Create a build directory
mkdir build
cd build

# 3. Configure and build
# On Linux:
cmake ..
make

# On Windows:
cmake ..
cmake --build . --config Relase
```

### Note
If you are on Linux use:
```bash
./setup.sh
```
after step 1 to save keystrokes.

## Execute Tests
From the build directory run:
```bash
ctest --verbose
```