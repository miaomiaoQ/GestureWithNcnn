cmake_minimum_required(VERSION 3.4.1)

SET(arguments "-DANDROID_TOOLCHAIN=gcc")
SET(cFlags "-fopenmp -O2 -fvisibility=hidden -fomit-frame-pointer -fstrict-aliasing -ffunction-sections -fdata-sections -ffast-math ")
SET(cppFlags "-fopenmp -O2 -fvisibility=hidden -fvisibility-inlines-hidden -fomit-frame-pointer -fstrict-aliasing -ffunction-sections -fdata-sections -ffast-math ")
SET(cppFlags "")
SET(cppFlags "-std=c++11")
SET(cppFlags "-frtti")
SET(cppFlags "-fexceptions")



#include头文件目录
include_directories(${CMAKE_SOURCE_DIR}/src/main/cpp/Ncnn/include
                    ${CMAKE_SOURCE_DIR}/src/main/cpp/Ncnn/)


#添加ncnn库
add_library(libncnn STATIC IMPORTED )
set_target_properties(libncnn
  PROPERTIES IMPORTED_LOCATION
  ${CMAKE_SOURCE_DIR}/src/main/jniLibs/${ANDROID_ABI}/libncnn.a)

#编译为动态库
add_library(gesturencnn SHARED ${CMAKE_SOURCE_DIR}/src/main/cpp/Ncnn/gesturencnn.cpp)
SET_TARGET_PROPERTIES(gesturencnn PROPERTIES LINKER_LANGUAGE C)

#添加工程所依赖的库
find_library(  log-lib log )
target_link_libraries(  gesturencnn
                       libncnn
                       ${log-lib} )