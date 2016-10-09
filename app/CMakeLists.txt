cmake_minimum_required(VERSION 3.4.1)

add_library(
             NativeMain

             SHARED

             src/main/cpp/native-lib.cpp )

option(PULSEAUDIO "" OFF)
option(VIDEO_WAYLAND "" OFF)
set(SDL_SHARED FALSE CACHE BOOL "")
#set(PTHREAD_LDFLAGS "" CACHE STRING "" FORCE)
add_definitions(-DSDL_ATOMIC_DISABLED -DGL_GLEXT_PROTOTYPES)
set(EXTRA_LIBS GLESv1_CM GLESv2 GLESv3 log android EGL)

add_subdirectory(../external/SDL2 SDL2)
target_include_directories(NativeMain PRIVATE ../external/SDL2/include)
target_link_libraries(NativeMain PUBLIC SDL2-static)

target_compile_options(NativeMain PRIVATE "-std=c++14")