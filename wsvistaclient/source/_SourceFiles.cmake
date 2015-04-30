# $Id:$

set( RelativeDir "source" )
set( RelativeSourceGroup "Source Files" )

set( DirFiles
	App.cpp
	App.h
	ActivationCallback.h
	EventHandler.cpp
	EventHandler.h
	main.cpp
	_SourceFiles.cmake
)
set( DirFiles_SourceGroup "${RelativeSourceGroup}" )

set( LocalSourceGroupFiles  )
foreach( File ${DirFiles} )
	list( APPEND LocalSourceGroupFiles "${RelativeDir}/${File}" )
	list( APPEND ProjectSources "${RelativeDir}/${File}" )
endforeach()
source_group( ${DirFiles_SourceGroup} FILES ${LocalSourceGroupFiles} )

