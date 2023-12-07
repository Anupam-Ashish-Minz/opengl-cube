cmake_minimum_required (VERSION 3.27)
project(cube)
set(SOURCES
	src/main.cpp
	src/shader.cpp
)
set(HEADERS
	src/shader.hpp
)
set(CMAKE_BUILD_TYPE Debug)
add_executable(cube ${SOURCES} ${HEADERS})
target_link_libraries(cube 
	glfw GLEW EGL GL OpenGL m 
)

