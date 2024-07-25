cmake_minimum_required(VERSION 3.10) 

# set the project name 
project(GoldDisplay) 

include_directories(src)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


# 查找 libxml2 包
find_package(PkgConfig REQUIRED)
pkg_check_modules(LIBXML2 REQUIRED libxml-2.0)

# 包含 libxml2 头文件路径
include_directories(${LIBXML2_INCLUDE_DIRS})


find_package(Qt6 COMPONENTS Core Widgets Gui Network DBus Xml REQUIRED)

qt6_add_resources(qrc_FILES image.qrc)

# 包含头文件目录
include_directories(src)


# 查找source目录下的所有*.cpp,*.c源文件,并将文件列表保存到 DIR_LIB_SRCS 变量
file(GLOB_RECURSE SRC_DIR_LIST "src/*.cpp" "src/*.c") #遍历获取source/路径下所有的*.cpp和*.c文件列表

add_executable(GoldDisplay
    ${SRC_DIR_LIST}
    ${qrc_FILES}
)

target_link_libraries(GoldDisplay
    PRIVATE Qt6::Core Qt6::Widgets Qt6::Gui Qt6::Network Qt6::DBus Qt6::Xml
    ${LIBXML2_LIBRARIES}
) 




