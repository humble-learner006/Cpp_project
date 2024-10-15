cmake_minimum_required(VERSION 3.10)
project(MySDLProject)

set(CMAKE_CXX_STANDARD 11)

# 设置 SDL2 的路径
set(CMAKE_PREFIX_PATH "D:/Desktop/3002pro/SDL2-2.30.8/x86_64-w64-mingw32/lib/cmake/SDL2")  # 替换为你的 SDL2 路径

# 查找 SDL2
find_package(SDL2 REQUIRED)

# 包含头文件目录
include_directories(${SDL2_INCLUDE_DIRS})
# 链接库目录
link_directories(${SDL2_LIBRARY_DIRS})

# 添加可执行文件
add_executable(1 main.cpp)
# 链接 SDL2 库
target_link_libraries(1 ${SDL2_LIBRARIES})

