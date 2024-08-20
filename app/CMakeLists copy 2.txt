cmake_minimum_required(VERSION 3.16)

# Set the project name and language
project(app LANGUAGES CXX)

#=================== INCLUSION OF GLFW ====================#
add_subdirectory(lib/glfw)

#=================== INCLUSION OF FFmpeg ====================#
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

#=================== INCLUSION OF Qt ====================#
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)  # Enable this for resource files (*.qrc)

# Specify where to find Qt (ensure QTDIR is correctly set)
set(CMAKE_PREFIX_PATH "C:/Qt/6.7.2/msvc2019_64")
find_package(Qt6Core REQUIRED)
find_package(Qt6Widgets REQUIRED)

#=================== INCLUSION OF Project Files ====================#
set(FORMS_DIR "${CMAKE_SOURCE_DIR}/forms")
set(INCLUDE_DIR "${CMAKE_SOURCE_DIR}/include")
set(SOURCE_DIR "${CMAKE_SOURCE_DIR}/src")

# Include directories
include_directories(${FORMS_DIR})
include_directories(${INCLUDE_DIR})
include_directories(${SOURCE_DIR})

# Glob the source files
file(GLOB_RECURSE SOURCES
    "${FORMS_DIR}/*.ui"
    "${FORMS_DIR}/*.qrc"
    "${INCLUDE_DIR}/*.h"
    "${SOURCE_DIR}/*.cpp"
)

#=================== SETUP EXECUTABLE ====================#

# Add the forms directory to the AUTOUIC search paths
set(CMAKE_AUTOUIC_SEARCH_PATHS ${FORMS_DIR})

# Add the executable
add_executable(app WIN32 ${SOURCES})

#===================== LINKING LIBRARIES ====================#
# Link against the required Qt libraries
target_include_directories(app PRIVATE ${FORMS_DIR})
target_include_directories(app PRIVATE ${INCLUDE_DIR})
target_include_directories(app PRIVATE ${SOURCE_DIR})

# Link against Qt, GLFW, and FFmpeg libraries
target_link_libraries(app PRIVATE Qt6::Widgets)
target_link_libraries(app PRIVATE glfw)
target_link_libraries(app PRIVATE ffmpeg)
