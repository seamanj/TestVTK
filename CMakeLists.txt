cmake_minimum_required(VERSION 3.1)

project(TestVTK)
file(GLOB SOURCES
    "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp")
set(CMAKE_CXX_STANDARD 11)
find_package(VTK REQUIRED)
include(${VTK_USE_FILE})
add_executable(${PROJECT_NAME} ${SOURCES})
target_link_libraries(${PROJECT_NAME} ${VTK_LIBRARIES})
