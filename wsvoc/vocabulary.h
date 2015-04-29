
/* Copyright (c) 2014-2015, Human Brain Project Workshop
 */

#ifndef ZEQ_WS_VOCABULARY_H
#define ZEQ_WS_VOCABULARY_H

#include <zeq/types.h>
#include <zeq/api.h>

#include <wsvoc/vector3d_zeq_generated.h>

namespace wsvoc
{
namespace data
{

struct Vector3d
{
    float x;
    float y;
    float z;
};

}

  ZEQ_API zeq::Event serializeVector3d( const data::Vector3d& vector );
  ZEQ_API data::Vector3d deserializeVector3d( const zeq::Event& event );

}
#endif
