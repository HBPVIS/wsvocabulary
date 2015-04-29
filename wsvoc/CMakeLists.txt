# Copyright (c) HBP 2014-2015

# find_package( zeq REQUIRED )
# find_package( FlatBuffers REQUIRED )

flatbuffers_generate_c_headers(HBP_FBS
  detail/vector3d.fbs
)

set(WSVOC_PUBLIC_HEADERS vocabulary.h ${HBP_FBS_ZEQ_OUTPUTS})
set(WSVOC_SOURCES vocabulary.cpp)
set(WSVOC_LINK_LIBRARIES ${LUNCHBOX_LIBRARIES} ${LIBZMQ_LIBRARIES} ${ZEQ_LIBRARIES} )
if(MSVC)
  list(APPEND WSVOC_LINK_LIBRARIES Ws2_32)
endif()

list(APPEND CPPCHECK_EXTRA_ARGS
  --suppress=*:${CMAKE_CURRENT_BINARY_DIR}/*_generated.h)

set( PROJECT_INCLUDE_NAME wsvoc )
add_definitions(-DZEQ_SHARED)
common_library( wsvoc )
