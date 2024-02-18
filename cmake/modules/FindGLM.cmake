# Locate the GLM library
#
# This module defines the following variables:
#
# GLM_LIBRARY the name of the library;
# GLM_INCLUDE_DIR where to find GLM include files.
# GLM_FOUND true if both the GLM_LIBRARY and GLM_INCLUDE_DIR have been found.
#
# To help locate the library and include file, you can define a
# variable called GLM_ROOT which points to the root of the GLM library
# installation.
#
# default search dirs
# 

set( _GLM_HEADER_SEARCH_DIRS
"/usr/include"
"/usr/local/include"
"${CMAKE_SOURCE_DIR}/includes"
"D:/Program_Filesx86/glm/include" )

set( _GLM_LIB_SEARCH_DIRS
"/usr/lib"
"/usr/local/lib"
"${CMAKE_SOURCE_DIR}/lib"
"D:/Program_Filesx86/glm/lib" )

# Check environment for root search directory
set( _GLM_ENV_ROOT $ENV{GLM_ROOT} )
if( NOT GLM_ROOT AND _GLM_ENV_ROOT )
	set(GLM_ROOT ${_GLM_ENV_ROOT} )
endif()

# Put user specified location at beginning of search
if( GLM_ROOT )
	list( INSERT _GLM_HEADER_SEARCH_DIRS 0 "${GLM_ROOT}/include" )
	list( INSERT _GLM_LIB_SEARCH_DIRS 0 "${GLM_ROOT}/lib" )
endif()

# Search for the header
FIND_PATH(GLM_INCLUDE_DIR "glm/glm.hpp"
PATHS ${_GLM_HEADER_SEARCH_DIRS} )

# Search for the library
FIND_LIBRARY(GLM_LIBRARY NAMES glm
PATHS ${_GLM_LIB_SEARCH_DIRS} )
INCLUDE(FindPackageHandleStandardArgs)
FIND_PACKAGE_HANDLE_STANDARD_ARGS(glm DEFAULT_MSG
GLM_LIBRARY GLM_INCLUDE_DIR)