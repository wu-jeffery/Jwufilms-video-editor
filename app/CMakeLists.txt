cmake_minimum_required(VERSION 3.16)
project(app LANGUAGES CXX)
set(CAMEK_CXX_STANDARD 14)

add_subdirectory(lib/glfw)

if(APPLE)
    list(APPEND EXTRA_LIBS
        "-framework OpenGL"
    )
elseif(WIN32)
    # Use correct libraries for MSVC
    list(APPEND EXTRA_LIBS
        opengl32
        glu32
        gdi32
        user32
        shell32
    )
else()
    list(APPEND EXTRA_LIBS
        GL
        GLU
        X11
    )
endif()

add_executable(app src/main.cpp)
target_link_libraries(app glfw ${EXTRA_LIBS})