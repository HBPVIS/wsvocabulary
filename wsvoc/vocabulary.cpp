/* Copyright (c) 2014-2015, Human Brain Project Workshop
 */

#include "vocabulary.h"

#include <wsvoc/vector3d_generated.h>
#include <zeq/event.h>
#include <zeq/vocabulary.h>

#include <lunchbox/debug.h>

namespace wsvoc
{

typedef std::vector< unsigned int > uints;

template< typename T, typename Builder >
void buildVectorOnlyBuffer(
    zeq::Event& event,
    void (Builder::*adder)( flatbuffers::Offset< flatbuffers::Vector< T >>),
    const std::vector< T >& vector)
{
    flatbuffers::FlatBufferBuilder& fbb = event.getFBB();
    Builder builder( fbb );
    (builder.*adder)( fbb.CreateVector( vector.data(), vector.size() ));
    fbb.Finish( builder.Finish( ));
}

template< typename T >
std::vector< T > deserializeVector( const flatbuffers::Vector< T >* in )
{
    std::vector< T > out( in->Length( ));
    for( flatbuffers::uoffset_t i = 0; i < in->Length(); ++i )
        out[i] = in->Get( i );
    return out;
}

template< typename T, typename U >
std::vector< T > deserializeVector(
    const zeq::Event& event,
    const flatbuffers::Vector< T >* (U::*getter)( ) const )
{
    auto data = flatbuffers::GetRoot< U >( event.getData( ));
    return deserializeVector(( data->*getter )( ));
}

#define BUILD_VECTOR_ONLY_BUFFER( event, type, vector ) \
  buildVectorOnlyBuffer( event, &type##Builder::add_##vector, vector);

ZEQ_API zeq::Event serializeVector3d( const data::Vector3d& vec )
{
    zeq::Event event( EVENT_VECTOR3D );
    flatbuffers::FlatBufferBuilder& fbb = event.getFBB();

    Vector3dBuilder builder( fbb );
    builder.add_x( vec.x );
    builder.add_y( vec.y );
    builder.add_z( vec.z );

    fbb.Finish( builder.Finish() );
    return event;
}

ZEQ_API data::Vector3d deserializeVector3d( const zeq::Event& event )
{
    auto data = GetVector3d( event.getData() );

    data::Vector3d vec;
    vec.x = data->x();
    vec.y = data->y();
    vec.z = data->z();
    return vec;
}

}
