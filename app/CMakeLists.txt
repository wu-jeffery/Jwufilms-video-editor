cmake_minimum_required(VERSION 3.16)

project(app VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Set the CMAKE_PREFIX_PATH to include the Qt installation path
set(CMAKE_PREFIX_PATH "C:/Qt/6.7.2/msvc2019_64/lib/cmake")

# Find the Qt package
find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)

# Manually set the SDL2 paths
set(SDL2_INCLUDE_DIRS "C:/SDL2/include")
set(SDL2_LIBRARIES "C:/SDL2/lib/x64/SDL2.lib")
set(SDL2_DLL "C:/SDL2/lib/x64/SDL2.dll")

# Include SDL2 directories
include_directories(${SDL2_INCLUDE_DIRS})

# Set the FFmpeg paths
set(FFMPEG_INCLUDE_DIRS "C:/FFmpeg_1/build_msys/include")
set(FFMPEG_LIBRARIES 
    "C:/FFmpeg_1/build_msys/bin/avcodec.lib"
    "C:/FFmpeg_1/build_msys/bin/avformat.lib"
    "C:/FFmpeg_1/build_msys/bin/avutil.lib"
    "C:/FFmpeg_1/build_msys/bin/swscale.lib"
    "C:/FFmpeg_1/build_msys/bin/swresample.lib"
)

# Include FFmpeg directories
include_directories(${FFMPEG_INCLUDE_DIRS})

set(PROJECT_SOURCES
    main.cpp
    MyWidget.cpp
    MyWidget.h
)

# Set up the executable as a Windows GUI application
if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(app
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
    )
    qt_finalize_executable(app)
else()
    add_executable(app WIN32 ${PROJECT_SOURCES})  # WIN32 flag ensures GUI app
endif()

# Link against the Qt Widgets, SDL2, and FFmpeg libraries
target_link_libraries(app PRIVATE 
    Qt${QT_VERSION_MAJOR}::Widgets 
    ${SDL2_LIBRARIES} 
    ${FFMPEG_LIBRARIES}
)

# Copy SDL2.dll to the output directory (Windows only)
if(WIN32)
    add_custom_command(TARGET app POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
        "${SDL2_DLL}"
        $<TARGET_FILE_DIR:app>
    )

    # Copy FFmpeg DLLs
    add_custom_command(TARGET app POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
        "C:/FFmpeg_1/build_msys/bin/avcodec-61.dll"
        "C:/FFmpeg_1/build_msys/bin/avformat-61.dll"
        "C:/FFmpeg_1/build_msys/bin/avutil-59.dll"
        "C:/FFmpeg_1/build_msys/bin/swscale-8.dll"
        "C:/FFmpeg_1/build_msys/bin/swresample-5.dll"
        $<TARGET_FILE_DIR:app>
    )

    # Copy msys-2.0.dll and other MSYS2 dependencies
    add_custom_command(TARGET app POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
        "C:/msys64/usr/bin/msys-2.0.dll"
        $<TARGET_FILE_DIR:app>
    )
    add_custom_command(TARGET app POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
        "C:/msys64/usr/bin/msys-gcc_s-seh-1.dll"
        $<TARGET_FILE_DIR:app>
    )
endif()