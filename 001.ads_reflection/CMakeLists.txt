cmake_minimum_required(VERSION 3.20)
project(ads_reflection)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/../cmake/modules/")

# source files
file(GLOB CPP_FILES ./src/*.h ./src/*.cpp)
add_executable(ads_reflection ${CPP_FILES})

# dependencies
find_package( OpenGL REQUIRED )
include_directories(${OpenGL_INCLUDE_DIRS})

find_package(glfw3 REQUIRED)
include_directories(${GLFW3_INCLUDE_DIR})
target_link_libraries(ads_reflection ${GLFW3_LIBRARY})
message(STATUS "glfw3 included at: ${GLFW3_INCLUDE_DIR}")
message(STATUS "glfw3 library dir: ${GLFW3_LIBRARY}")

find_package(GLEW REQUIRED)
include_directories(${GLEW_INCLUDE_DIRS})
target_link_libraries(ads_reflection ${GLEW_LIBRARY})
message(STATUS "GLEW included at: ${GLEW_INCLUDE_DIRS}")
message(STATUS "GLEW library dir: ${GLEW_LIBRARY}")

find_package(glm REQUIRED)
include_directories(${GLM_INCLUDE_DIR})
message(STATUS "GLM included at: ${GLM_INCLUDE_DIR}")

target_link_libraries(ads_reflection glad ${OPENGL_gl_LIBRARY} ${GLEW_LIBRARY} ${GLFW3_LIBRARY})

#enable C++17 features
target_compile_features(ads_reflection PRIVATE cxx_std_17)

# define
add_compile_definitions(GLEW_STATIC)
add_compile_definitions(GLM_ENABLE_EXPERIMENTAL)
add_compile_definitions(APP_WORK_DIR="${CMAKE_CURRENT_SOURCE_DIR}")