cmake_minimum_required(VERSION 3.21)
project(SWEProject)

set(CMAKE_CXX_STANDARD 20)

add_executable(SWEProject testSWEProject/testSWEProject.cpp)

set(SFML_STATIC_LIBRARIES TRUE)
set(SFML_DIR C:/SFML/lib/cmake/SFML)
find_package(SFML COMPONENTS system window graphics audio network REQUIRED)

include_directories(c:/SFML/include)
target_link_libraries(SWEProject sfml-system sfml-window sfml-graphics sfml-audio)