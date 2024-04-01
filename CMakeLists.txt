cmake_minimum_required(VERSION 3.12)

project(OpenGL)

set(CMAKE_CXX_STANDARD 17)

file(GLOB ASSETS "./assets")
file(COPY ${ASSETS} DESTINATION ${CMAKE_BINARY_DIR})

include_directories(
	SYSTEM ${CMAKE_CURRENT_SOURCE_DIR}/Dependencies/include
)
link_directories(
	SYSTEM ${CMAKE_CURRENT_SOURCE_DIR}/Dependencies/lib
)

file(GLOB_RECURSE SRC_FILES "src/*.cpp")

add_executable(glShadow "Application.cpp" "glad.c" ${SRC_FILES})

target_link_libraries(glShadow glfw3.lib)
