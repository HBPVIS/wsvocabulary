cmake_minimum_required( VERSION 2.8 )
project( wsvoc )


list(APPEND CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/CMake
  ${CMAKE_SOURCE_DIR}/CMake/common)

set(LAST_RELEASE 0.0.0)
set(VERSION_MAJOR "0")
set(VERSION_MINOR "1")
set(VERSION_PATCH "0")
set(VERSION_ABI 1)

include(GitExternal)
include(Common)
include(FindPackages)

set(COMMON_PROJECT_DOMAIN eu.humanbrainproject)
set(WSVOC_DESCRIPTION "WSVOC - Vocabulary for Aachen WS")
set(WSVOC_DEPENDENT_LIBRARIES zeq FlatBuffers)


add_subdirectory( wsvoc )

include(CPackConfig)
