cmake_minimum_required(VERSION 3.4.1)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

#set(OpenCV_DIR 配置在gradle和local.properties中的OpenCV路径)
find_package(OpenCV REQUIRED)
message("OpenCV_INCLUDE_DIRS = ${OpenCV_INCLUDE_DIRS}")

include_directories(${OpenCV_INCLUDE_DIRS})
message("OpenCV_LIBS = ${OpenCV_LIBS}")

add_library(cvtool SHARED
        Native.cpp
        ContrastHelper.cpp
        Contrast.cpp
        bitmap_util.cpp
        )

target_link_libraries(cvtool ${OpenCV_LIBS} -ljnigraphics)
