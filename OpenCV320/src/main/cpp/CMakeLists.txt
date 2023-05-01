cmake_minimum_required(VERSION 3.4.1)

# 设置 C++ 标准
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -stdlib=libc++")


#set(OpenCV_DIR 配置在gradle和local.properties中的OpenCV路径)
find_package(OpenCV REQUIRED)

include_directories(${OpenCV_INCLUDE_DIRS} include)

add_library(cvtool SHARED
        cvtool.cpp
        ContrastHelper.cpp
        Contrast.cpp
        )

target_link_libraries(cvtool ${OpenCV_LIBS} -ljnigraphics)


