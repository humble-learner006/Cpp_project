cmake_minimum_required(VERSION 3.29)
project(CSC3002)

set(CMAKE_CXX_STANDARD 20)

set(SOURCE_FILES main.cpp)

# 声明一个变量为SDL2_DIR包含所有头文件的路径
set(SDL2_DIR
        D:/tool/sdl/SDL2-devel-2.30.8-mingw/SDL2-2.30.8/x86_64-w64-mingw32/include/SDL2
        D:/tool/sdl/SDL2_ttf-devel-2.22.0-mingw/SDL2_ttf-2.22.0/x86_64-w64-mingw32/include/SDL2
        D:/tool/sdl/SDL2_image-devel-2.8.2-mingw/SDL2_image-2.8.2/x86_64-w64-mingw32/include/SDL2)

# 声明一个变量为SDL2_LINK包含所有库的路径
set(SDL2_LINK
        D:/tool/sdl/SDL2-devel-2.30.8-mingw/SDL2-2.30.8/x86_64-w64-mingw32/lib
        D:/tool/sdl/SDL2_image-devel-2.8.2-mingw/SDL2_image-2.8.2/x86_64-w64-mingw32/lib
        D:/tool/sdl/SDL2_ttf-devel-2.22.0-mingw/SDL2_ttf-2.22.0/x86_64-w64-mingw32/lib)

# 关联所有的头文件
include_directories(${SDL2_DIR})
# 关联所有的库
link_directories(${SDL2_LINK})

add_executable(CSC3002 ${SOURCE_FILES})

# 配置关联库的名称，如果只使用到SDL2主体的库，那只需要添加mingw32 SDL2 SDL2main
target_link_libraries(CSC3002 mingw32 SDL2 SDL2main SDL2_ttf SDL2_image)