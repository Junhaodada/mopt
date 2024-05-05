cmake_minimum_required(VERSION 3.10)

# 项目名称和版本
project(mopt VERSION 1.0)

# 设置C++标准
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# 添加Eigen库的头文件路径
include_directories(third_party/eigen)
include_directories(include)

# 递归查找src目录下的所有cpp文件
file(GLOB_RECURSE SOURCES "src/*.cpp")

# 添加一个静态库
add_library(${PROJECT_NAME} STATIC ${SOURCES})

enable_testing()
add_subdirectory(test)
