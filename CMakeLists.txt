cmake_minimum_required(VERSION 3.10)
project(u-ttl)

# Set C++ standard
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Include directories
include_directories(include)

# Source files
file(GLOB SOURCES "src/*.cpp")

# Add executable
add_executable(u-ttl ${SOURCES})

# Link libraries
target_link_libraries(u-ttl PUBLIC pthread)
