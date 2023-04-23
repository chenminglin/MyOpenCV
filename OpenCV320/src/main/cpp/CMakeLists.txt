cmake_minimum_required(VERSION 3.4.1)

#set(OpenCV_DIR 配置在gradle和local.properties中的OpenCV路径)
find_package(OpenCV REQUIRED)

include_directories(${OpenCV_INCLUDE_DIRS})

add_library(native-lib SHARED native-lib.cpp)
target_link_libraries(native-lib ${OpenCV_LIBS} -ljnigraphics)


