#!/bin/bash

# Create and cd to build/
mkdir -p build && cd build

# Configure and build
cmake .. && make