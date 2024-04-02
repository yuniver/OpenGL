cmake_minimum_required(VERSION 3.12)

project(OpenGL)

set(CMAKE_CXX_STANDARD 17)


# 设置源目录和目标目录
set(ASSET_DIR "./Assets")
 
# 复制文件夹下所有文件到指定目录
file(COPY ${ASSET_DIR}
     DESTINATION ${CMAKE_BINARY_DIR}
     FILE_PERMISSIONS OWNER_EXECUTE OWNER_WRITE OWNER_READ
     GROUP_EXECUTE GROUP_READ
     WORLD_EXECUTE WORLD_READ)

include_directories(
	SYSTEM ${CMAKE_CURRENT_SOURCE_DIR}/Dependencies/include
)
link_directories(
	SYSTEM ${CMAKE_CURRENT_SOURCE_DIR}/Dependencies/lib
)

file(GLOB_RECURSE SRC_FILES "src/*.cpp")

add_executable(glShadow "Application.cpp" "glad.c" "stb_image.cpp" ${SRC_FILES})

target_link_libraries(glShadow glfw3.lib SOIL.lib assimp.lib freetype.lib)
