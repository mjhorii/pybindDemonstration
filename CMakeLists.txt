cmake_minimum_required(VERSION 3.8.2)
project(CropDisease)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED YES)

#Only search for python in the active virtual environment
set(Python_FIND_VIRTUALENV "ONLY")
find_package (Python COMPONENTS Interpreter Development)

# Explicitly use the Python from the local virtual environment
set(Python3_EXECUTABLE "${CMAKE_SOURCE_DIR}/pybindDemoEnv/bin/python")
message(STATUS "Using Python executable: ${Python3_EXECUTABLE}")

# Extract the Python version dynamically
execute_process(
    COMMAND ${Python3_EXECUTABLE} -c "import sys; print(f'{sys.version_info.major}.{sys.version_info.minor}')"
    OUTPUT_VARIABLE PYTHON_VERSION
    OUTPUT_STRIP_TRAILING_WHITESPACE
)
message(STATUS "Detected Python version: ${PYTHON_VERSION}")

# Construct the pybind11_DIR path using the detected Python version
set(pybind11_DIR "${CMAKE_SOURCE_DIR}/pybindDemoEnv/lib/python${PYTHON_VERSION}/site-packages/pybind11/share/cmake/pybind11")
find_package(pybind11 CONFIG)

# Compile pybind modules
pybind11_add_module(module_name addition.cpp)
pybind11_add_module(example example.cpp pyMatrix.h pyMatrix.cpp)