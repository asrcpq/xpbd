cmake_minimum_required(VERSION 3.10)

if(POLICY CMP0072)
	cmake_policy (SET CMP0072 NEW)
endif()

#if(NOT CMAKE_BUILD_TYPE)
#	set(CMAKE_BUILD_TYPE Release)
#endif()
set(CMAKE_C_COMPILER "/usr/bin/clang")
set(CMAKE_CXX_COMPILER "/usr/bin/clang++")
#set(CMAKE_CXX_CLANG_TIDY
#	clang-tidy
#	-checks=-*,cppcoreguidelines-*,-cppcoreguidelines-avoid-magic-numbers
#)
set(CMAKE_CXX_FLAGS "-Wall -Wextra -pedantic -Werror")
set(CMAKE_CXX_FLAGS_DEBUG "-g")
set(CMAKE_CXX_FLAGS_RELEASE "-O3")

project(xpbd)
find_package(OpenGL REQUIRED)
find_package(GLUT REQUIRED)
include_directories( ${OPENGL_INCLUDE_DIRS}  ${GLUT_INCLUDE_DIRS} )
add_executable(xpbd
	src/xpbd.cpp
	src/cloth.cpp
	src/ball.cpp
	src/application.cpp
	src/particle.cpp
	src/constraint.cpp
	src/emode.cpp
)

target_link_libraries(xpbd ${OPENGL_LIBRARIES} ${GLUT_LIBRARY} )
