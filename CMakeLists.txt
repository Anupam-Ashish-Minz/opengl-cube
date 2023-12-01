# what im looking for 
# set compiler to gcc
# set main file to main.c
# link glfw3 glew 
# build the project

cmake_minimum_required (VERSION 3.27)
project(cube)
set(SOURCES
	src/main.c
	src/read_shader.c
	src/input.c
)
set(HEADERS
	src/read_shader.h
	src/input.h
)
set(CMAKE_BUILD_TYPE Debug)
add_executable(cube ${SOURCES} ${HEADERS})
target_link_libraries(cube 
	glfw GLEW EGL GL OpenGL
)

