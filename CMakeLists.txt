cmake_minimum_required(VERSION 3.14)
project(TouchpadoC__)

set(CMAKE_CXX_STANDARD 14)

add_executable(TouchpadoC__ main.cpp EventBuster.cpp Func.cpp Fingers.cpp ThreeFingers.cpp VirtDevice.cpp TwoFingers.cpp FourFingers.cpp)