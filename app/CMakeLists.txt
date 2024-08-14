cmake_minimum_required(VERSION 3.16)

# Set the project name and language
project(app LANGUAGES CXX)


#======================= INCLUSION OF Qt =======================#
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

#===================== LINKING LIBRARIES =======================#
# Link against the required Qt libraries
target_include_directories(app PRIVATE ${FORMS_DIR})
target_include_directories(app PRIVATE ${INCLUDE_DIR})
target_include_directories(app PRIVATE ${SOURCE_DIR})

# Set the working directory to the build output for runtime
target_link_libraries(app Qt6::Widgets)
