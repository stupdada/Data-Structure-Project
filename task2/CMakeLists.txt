#cmake_minimum_required(VERSION 3.28)
#project(task2)
#
#set(CMAKE_CXX_STANDARD 17)
#
#add_executable(task2 main.cpp)

cmake_minimum_required(VERSION 3.28)
project(task2)

set(CMAKE_CXX_STANDARD 17)

## 添加编译选项
add_compile_options(-fopenmp -O2 -march=native)

# 添加可执行目标
add_executable(task2 main.cpp)

find_package(OpenMP REQUIRED)

if(OpenMP_CXX_FOUND)
    target_link_libraries(task2 PUBLIC OpenMP::OpenMP_CXX)
endif()

