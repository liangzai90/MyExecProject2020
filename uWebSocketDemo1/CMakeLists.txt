# CMake 最低版本号要求
cmake_minimum_required (VERSION 2.8)

# 项目信息
project (Demo1)

# 查找目录下的所有源文件
# 并将名称保存到 DIR_SRCS 变量
aux_source_directory(./src DIR_SRCS)

# 指定生成目标
add_executable(Demo1 ${DIR_SRCS})


target_include_directories(Demo1
    PUBLIC 
        ${PROJECT_SOURCE_DIR}/include
        ${PROJECT_SOURCE_DIR}/uSockets
        ${PROJECT_SOURCE_DIR}/uSockets/src
)

# 添加链接库
target_link_libraries(Demo1 uSockets.a)




