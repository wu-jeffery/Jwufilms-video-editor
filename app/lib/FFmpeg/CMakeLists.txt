cmake_minimum_required(VERSION 3.14)
project(FFmpeg)

# Set the path to the directory where the FFmpeg .lib files are located
set(FFMPEG_INSTALL_DIR "C:/FFMPEG_PREBUILT")

# Include directories and link libraries for FFmpeg
add_library(FFmpeg INTERFACE IMPORTED GLOBAL)
target_include_directories(FFmpeg INTERFACE ${FFMPEG_INSTALL_DIR}/include)
target_link_libraries(FFmpeg INTERFACE
    ${FFMPEG_INSTALL_DIR}/lib/avcodec.lib
    ${FFMPEG_INSTALL_DIR}/lib/avformat.lib
    ${FFMPEG_INSTALL_DIR}/lib/avfilter.lib
    ${FFMPEG_INSTALL_DIR}/lib/avdevice.lib
    ${FFMPEG_INSTALL_DIR}/lib/avutil.lib
    ${FFMPEG_INSTALL_DIR}/lib/swresample.lib
    ${FFMPEG_INSTALL_DIR}/lib/swscale.lib
)