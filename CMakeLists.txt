cmake_minimum_required(VERSION 3.20)

project(FullScreenExpansion)

# Add include directory to find header files
include_directories(${PROJECT_SOURCE_DIR}/nlohamnn)

add_executable(FullScreenExpansion main.cpp windowDisplay.cpp readConfig.cpp)
target_link_libraries(FullScreenExpansion user32)
