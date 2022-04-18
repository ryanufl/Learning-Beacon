cmake_minimum_required(VERSION 3.20)
project(SWEProject)

set(CMAKE_CXX_STANDARD 20)

add_executable(SWEProject testSWEProject/testSWEProject.cpp testSWEProject/Screen.cpp testSWEProject/Screen.h testSWEProject/mathGame.h testSWEProject/mathGame.cpp)

set(SFML_STATIC_LIBRARIES TRUE)
set(SFML_DIR SFML-2.5.1/lib/cmake/SFML)
find_package(SFML COMPONENTS system window graphics audio network REQUIRED)

include_directories(SFML-2.5.1/include)
target_link_libraries(SWEProject sfml-system sfml-window sfml-graphics sfml-audio)