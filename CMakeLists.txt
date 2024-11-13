cmake_minimum_required(VERSION 3.20)

project(FullScreenExpansion)

add_executable(FullScreenExpansion main.cpp)
target_link_libraries(FullScreenExpansion user32)
