cmake_minimum_required (VERSION 3.20)
set (CMAKE_CXX_STANDARD 17)

project (shading_example)

if(MSVC)
  add_definitions(/DNOMINMAX)
endif()

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/modules/")

find_package( glm REQUIRED )
include_directories(${GLM_INCLUDE_DIR})

find_package( glfw3 REQUIRED )
include_directories(${GLFW3_INCLUDE_DIR})

find_package( OpenGL REQUIRED )

include_directories( glad/include )

add_subdirectory( glad )
add_subdirectory( 001.ads_reflection )

# file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/media DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
