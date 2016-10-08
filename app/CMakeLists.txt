cmake_minimum_required(VERSION 3.4.1)

add_library( # Sets the name of the library.
             NativeMain

             # Sets the library as a shared library.
             #STATIC
             SHARED

             # Provides a relative path to your source file(s).
             # Associated headers in the same location as their source
             # file are automatically included.
             src/main/cpp/native-lib.cpp )

add_subdirectory(../external/SDL2 SDL2)
target_include_directories(NativeMain PRIVATE ../external/SDL2/include)
target_link_libraries(NativeMain SDL2-static)

target_compile_options(NativeMain PRIVATE "-std=c++14")