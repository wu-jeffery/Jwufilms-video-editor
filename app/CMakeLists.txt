cmake_minimum_required(VERSION 3.16)
project(app LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 14)

# Add GLFW as a subdirectory
add_subdirectory(lib/glfw)

# Define the path to your FFmpeg include directory
include_directories("C:/ffmpeg_prebuild/include")

# Define the specific FFmpeg libraries
set(AVCODEC_LIBRARY "C:/ffmpeg_prebuild/lib/avcodec.lib")
set(AVFORMAT_LIBRARY "C:/ffmpeg_prebuild/lib/avformat.lib")
set(AVUTIL_LIBRARY "C:/ffmpeg_prebuild/lib/avutil.lib")
set(SWSCALE_LIBRARY "C:/ffmpeg_prebuild/lib/swscale.lib")
set(SWRESAMPLE_LIBRARY "C:/ffmpeg_prebuild/lib/swresample.lib")

# Platform-specific library settings
if(APPLE)
    list(APPEND EXTRA_LIBS
        "-framework OpenGL"
    )
elseif(WIN32)
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

# Add the executable target and source files
add_executable(app 
                src/main.cpp 
                src/load_frame.cpp
                src/video_reader.cpp
                src/video_reader.hpp
                )

# Link FFmpeg libraries explicitly
target_link_libraries(app
    glfw
    ${AVCODEC_LIBRARY}
    ${AVFORMAT_LIBRARY}
    ${AVUTIL_LIBRARY}
    ${SWSCALE_LIBRARY}
    ${SWRESAMPLE_LIBRARY}
    ${EXTRA_LIBS}
)