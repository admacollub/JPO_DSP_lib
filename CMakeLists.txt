cmake_minimum_required(VERSION 3.10)

project(DSP_FILTER_LIB)

include_directories(.)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

file(GLOB SOURCES "src/*.cpp")

add_executable(bandpass_demo_FIR src/bandpass_demo_FIR.cpp)
add_executable(bandstop_demo_FIR src/bandstop_demo_FIR.cpp)
add_executable(cascade_demo src/cascade_demo.cpp)
add_executable(cheb_highpass_demo src/cheb_highpass_demo.cpp)
add_executable(cheb_lowpass_demo src/cheb_lowpass_demo.cpp)
add_executable(highpass_demo_FIR src/highpass_demo_FIR.cpp)
add_executable(lowpass_demo_FIR src/lowpass_demo_FIR.cpp)
add_executable(main src/main.cpp)
