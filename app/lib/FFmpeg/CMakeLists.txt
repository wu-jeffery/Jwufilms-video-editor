# Specify the minimum version for CMake
cmake_minimum_required(VERSION 3.16)

# Define the project name
project(ffmpeg_integration)

# Set the C++ standard
set(CMAKE_CXX_STANDARD 14)

# Set the library output path (optional, depends on your structure)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)

# Add the FFmpeg include directory
include_directories("C:/ffmpeg_prebuild/include")

# Manually specify the full paths to the FFmpeg libraries
set(AVCODEC_LIBRARY "C:/ffmpeg_prebuild/lib/avcodec.lib")
set(AVFORMAT_LIBRARY "C:/ffmpeg_prebuild/lib/avformat.lib")
set(AVUTIL_LIBRARY "C:/ffmpeg_prebuild/lib/avutil.lib")
set(SWSCALE_LIBRARY "C:/ffmpeg_prebuild/lib/swscale.lib")
# Add any other FFmpeg libraries you need similarly
set(SWRESAMPLE_LIBRARY "C:/ffmpeg_prebuild/lib/swresample.lib")

# Create an INTERFACE library for FFmpeg
add_library(ffmpeg INTERFACE)

# Set the properties for the INTERFACE library
target_include_directories(ffmpeg INTERFACE "C:/ffmpeg_prebuild/include")
target_link_libraries(ffmpeg INTERFACE
    "${AVCODEC_LIBRARY}"
    "${AVFORMAT_LIBRARY}"
    "${AVUTIL_LIBRARY}"
    "${SWSCALE_LIBRARY}"
    "${SWRESAMPLE_LIBRARY}"
)

# The INTERFACE library can now be linked with the final target
# In the main CMakeLists.txt or where the final executable is defined, use:
# target_link_libraries(your_executable_target_name PRIVATE ffmpeg)