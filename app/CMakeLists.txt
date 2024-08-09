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
find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets LinguistTools)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets LinguistTools)

# Manually set the SDL2 paths
set(SDL2_INCLUDE_DIRS "C:/SDL2/include")
set(SDL2_LIBRARIES "C:/SDL2/lib/x64/SDL2.lib")
set(SDL2_DLL "C:/SDL2/lib/x64/SDL2.dll")

# Include SDL2 directories
include_directories(${SDL2_INCLUDE_DIRS})

set(TS_FILES app_en_US.ts)

set(PROJECT_SOURCES
    main.cpp
    MyWidget.h
    MyWidget.cpp
    mainwindow.ui
    ${TS_FILES}
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(app
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
    )
    qt_create_translation(QM_FILES ${CMAKE_SOURCE_DIR} ${TS_FILES})
    qt_finalize_executable(app)
else()
    if(ANDROID)
        add_library(app SHARED
            ${PROJECT_SOURCES}
        )
    else()
        add_executable(app WIN32 ${PROJECT_SOURCES})
    endif()
    qt5_create_translation(QM_FILES ${CMAKE_SOURCE_DIR} ${TS_FILES})
endif()

# Link against the Qt Widgets library
target_link_libraries(app PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)

# Link against the SDL2 library
target_link_libraries(app PRIVATE ${SDL2_LIBRARIES})

# Set properties for macOS bundle and Windows executable
if(${QT_VERSION} VERSION_LESS 6.1.0)
  set(BUNDLE_ID_OPTION MACOSX_BUNDLE_GUI_IDENTIFIER com.example.app)
endif()
set_target_properties(app PROPERTIES
    ${BUNDLE_ID_OPTION}
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

# Installation setup
include(GNUInstallDirs)
install(TARGETS app
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

# Copy SDL2.dll to the output directory (Windows only)
if(WIN32)
    add_custom_command(TARGET app POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
        "${SDL2_DLL}"
        $<TARGET_FILE_DIR:app>
    )
endif()
