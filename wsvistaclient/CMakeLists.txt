cmake_minimum_required( VERSION 2.8 )
project( ClientTestZEQ )

list( APPEND CMAKE_MODULE_PATH "$ENV{VISTA_CMAKE_COMMON}")

include( VistaCommon )

vista_use_package( VistaCoreLibs REQUIRED FIND_DEPENDENCIES )

find_package(ZEQ REQUIRED NO_CMAKE_BUILDS_PATH)
include_directories(${ZEQ_INCLUDE_DIRS})

find_package(wsvoc REQUIRED NO_CMAKE_BUILDS_PATH)
include_directories(${WSVOC_INCLUDE_DIRS})

# Including the source files of all source subfolders recursively
include( "source/_SourceFiles.cmake" )

add_executable( ClientTestZEQ ${ProjectSources} )
target_link_libraries( ClientTestZEQ
	${VISTA_USE_PACKAGE_LIBRARIES} # contains all libraries from vista_use_package() calls
	${WSVOC_LIBRARIES}
	${ZEQ_LIBRARIES}
)

vista_configure_app( ClientTestZEQ )
vista_create_default_info_file( ClientTestZEQ )

