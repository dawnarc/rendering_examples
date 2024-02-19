cmake_minimum_required (VERSION 3.20)

set (CMAKE_CXX_STANDARD 17)

project (rendering_examples)

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
add_subdirectory( 01.lighting/01.ads_reflection )
