# For more information about using CMake with Android Studio, read the
# documentation: https://d.android.com/studio/projects/add-native-code.html

# Sets the minimum version of CMake required to build the native library.

cmake_minimum_required(VERSION 3.4.1)

# Creates and names a library, sets it as either STATIC
# or SHARED, and provides the relative paths to its source code.
# You can define multiple libraries, and CMake builds them for you.
# Gradle automatically packages shared libraries with your APK.

#C 的编译选项是 CMAKE_C_FLAGS



#添加子目录,将会调用子目录中的CMakeLists.txt
ADD_SUBDIRECTORY(src/main/cpp/Ncnn)
ADD_SUBDIRECTORY(src/main/cpp/Signal)
