# Specify the minimum version for CMake
cmake_minimum_required(VERSION 3.16)

# Define the project name
project(ffmpeg_integration)

# Set the library output path (optional, depends on your structure)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)

# Add the FFmpeg include directory
include_directories("C:/ffmpeg_prebuild/include")

# Find the FFmpeg libraries
find_library(AVCODEC_LIBRARY avcodec PATHS "C:/ffmpeg_prebuild/lib")
find_library(AVFORMAT_LIBRARY avformat PATHS "C:/ffmpeg_prebuild/lib")
find_library(AVUTIL_LIBRARY avutil PATHS "C:/ffmpeg_prebuild/lib")
find_library(SWSCALE_LIBRARY swscale PATHS "C:/ffmpeg_prebuild/lib")

# Create an INTERFACE library for FFmpeg
add_library(ffmpeg INTERFACE)

# Set the properties for the INTERFACE library
target_include_directories(ffmpeg INTERFACE "C:/ffmpeg_prebuild/include")
target_link_libraries(ffmpeg INTERFACE
    "${AVCODEC_LIBRARY}"
    "${AVFORMAT_LIBRARY}"
    "${AVUTIL_LIBRARY}"
    "${SWSCALE_LIBRARY}"
)

# The INTERFACE library can now be linked with the final target
# In the main CMakeLists.txt or where the final executable is defined, use:
# target_link_libraries(your_executable_target_name PRIVATE ffmpeg)