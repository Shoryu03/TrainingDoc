cmake_minimum_required(VERSION 3.15)

project(WorkoutDoc VERSION 1.0)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


add_executable(WorkoutDoc src/main.cpp)

target_include_directories(WorkoutDoc PUBLIC include)
