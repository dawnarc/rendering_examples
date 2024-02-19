cmake_minimum_required(VERSION 3.20)

set(target ads_reflection)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/../cmake/modules/")

# source files

file(GLOB CPP_FILES ./src/*.h ./src/*.cpp)
add_executable(${target} ${CPP_FILES})

# dependencies

find_package( OpenGL REQUIRED )
include_directories( ${OpenGL_INCLUDE_DIRS} )
target_link_libraries( ${target} ${OPENGL_gl_LIBRARY} )

find_package( glfw3 REQUIRED )
include_directories( ${GLFW3_INCLUDE_DIR} )
target_link_libraries( ${target} ${GLFW3_LIBRARY} )

find_package( glm REQUIRED )
include_directories( ${GLM_INCLUDE_DIR} )

target_link_libraries(${target} glad)

# define

add_compile_definitions(GLEW_STATIC)
add_compile_definitions(GLM_ENABLE_EXPERIMENTAL)
add_compile_definitions(APP_WORK_DIR="${CMAKE_CURRENT_SOURCE_DIR}")