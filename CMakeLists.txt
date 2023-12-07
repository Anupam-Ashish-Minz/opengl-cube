# what im looking for 
# set compiler to gcc
# set main file to main.c
# link glfw3 glew 
# build the project

cmake_minimum_required (VERSION 3.27)
project(cube)
set(SOURCES
	src/main.c
	src/shader.c
	src/input.c
	src/rotation.c
	src/transforms.c
)
set(HEADERS
	src/shader.h
	src/input.h
	src/rotation.h
	src/transforms.h
)
set(CMAKE_BUILD_TYPE Debug)
add_executable(cube ${SOURCES} ${HEADERS})
target_link_libraries(cube 
	glfw cglm GLEW EGL GL OpenGL m
)

