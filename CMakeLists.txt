cmake_minimum_required (VERSION 3.8)

## CUSTOMISE

# Define the application name and version.
project (valik VERSION 1.0)

## BUILD

# Make Release default build type
if (NOT CMAKE_BUILD_TYPE)
    set (CMAKE_BUILD_TYPE Release CACHE STRING
         "Choose the type of build, options are: Debug Release Coverage RelWithDebInfo MinSizeRel."
         FORCE)
endif ()

# Specify the directories where to store the built archives, libraries and executables
set (CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib")
set (CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib")
set (CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin")

# Messages
string (ASCII 27 Esc)
set (FontBold "${Esc}[1m")
set (FontReset "${Esc}[m")

# Dependency: SeqAn3.
set (SEQAN3_CEREAL ON CACHE BOOL "Require cereal to be present.")
find_package (SeqAn3 QUIET REQUIRED HINTS lib/seqan3/build_system)

# Allow to include CMake scripts from seqan3.
list (APPEND CMAKE_MODULE_PATH "${SEQAN3_CLONE_DIR}/test/cmake/")

# Use ccache.
include (seqan3_require_ccache)
seqan3_require_ccache ()

# Add the application.
add_subdirectory (src)
message (STATUS "${FontBold}You can run `make` to build the application.${FontReset}")

## DOCUMENTATION

add_subdirectory (doc EXCLUDE_FROM_ALL)

## TEST

enable_testing ()
add_subdirectory (test EXCLUDE_FROM_ALL)
