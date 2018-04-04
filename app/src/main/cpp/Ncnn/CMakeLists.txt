cmake_minimum_required(VERSION 3.4.1)

SET(ARGUMENTS "-DANDROID_TOOLCHAIN=gcc")
SET(CMAKE_C_FLAGS "-fopenmp -O2 -fvisibility=hidden -fomit-frame-pointer -fstrict-aliasing -ffunction-sections -fdata-sections -ffast-math ")
SET(CMAKE_CXX_FLAGS "-fopenmp -O2 -fvisibility=hidden -fvisibility-inlines-hidden -fomit-frame-pointer -fstrict-aliasing -ffunction-sections -fdata-sections -ffast-math ")
SET(CMAKE_CXX_FLAGS "")
SET(CMAKE_CXX_FLAGS "-std=c++11")
SET(CMAKE_CXX_FLAGS "-frtti")
SET(CMAKE_CXX_FLAGS "-fexceptions")
if(${ANDROID_ABI} STREQUAL "armeabi-v7a")
    include_directories(${ANDROID_SYSROOT}/usr/include/arm-linux-androideabi)
elseif(${ANDROID_ABI} STREQUAL "arm64-v8a")
    include_directories(${ANDROID_SYSROOT}/usr/include/aarch64-linux-android)
else()
    include_directories(${ANDROID_SYSROOT}/usr/include/arm-linux-androideabi)
endif()


if(CMAKE_TOOLCHAIN_FILE)
set(CMAKE_INSTALL_PREFIX "/home/dmrf/ncnn-master/build-android/install" CACHE PATH "Installation Directory")
endif()



#include头文件目录
include_directories(${CMAKE_SOURCE_DIR}/src/main/cpp/Ncnn/include
                    ${CMAKE_SOURCE_DIR}/src/main/cpp/Ncnn/)

 #source directory源文件目录
 file(GLOB GESTURENCNN_SRC ${CMAKE_SOURCE_DIR}/src/main/cpp/Ncnn/*.h
                     ${CMAKE_SOURCE_DIR}/src/main/cpp/Ncnn/*.cpp)
 set(GESTURENCNN_COMPILE_CODE ${GESTURENCNN_SRC})


#添加ncnn库
add_library(libncnn STATIC IMPORTED )
set_target_properties(libncnn
  PROPERTIES IMPORTED_LOCATION
  ${CMAKE_SOURCE_DIR}/src/main/jniLibs/${ANDROID_ABI}/libncnn.a)

#编译为动态库
#add_library(gesturencnn SHARED ${CMAKE_SOURCE_DIR}/src/main/cpp/Ncnn/gesturencnn.cpp)
#编译为动态库
add_library(gesturencnn SHARED ${GESTURENCNN_COMPILE_CODE})
#SET_TARGET_PROPERTIES(gesturencnn PROPERTIES LINKER_LANGUAGE C)

#添加工程所依赖的库
find_library(  log-lib log )
target_link_libraries(  gesturencnn
                       libncnn
                       ${log-lib} )